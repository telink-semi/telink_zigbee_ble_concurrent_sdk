/********************************************************************************************************
 * @file     timer.c
 *
 * @brief    Interface of hardware timer
 *
 * @author
 * @date     Oct. 8, 2016
 *
 * @par      Copyright (c) 2016, Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *
 *           The information contained herein is confidential property of Telink
 *           Semiconductor (Shanghai) Co., Ltd. and is available under the terms
 *           of Commercial License Agreement between Telink Semiconductor (Shanghai)
 *           Co., Ltd. and the licensee or the terms described here-in. This heading
 *           MUST NOT be removed from this file.
 *
 *           Licensees are granted free, non-transferable use of the information in this
 *           file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided.
 *
 *******************************************************************************************************/
#include "platform_includes.h"
#include "../common/string.h"
#include "timer.h"


#define TIMER_SAFE_BOUNDARY_IN_US(v)		(10*v)
#define TIMER_OVERFLOW_VALUE        0xFFFFFFFE

typedef struct {
    /* Expire time and callback parameters */
    ext_clk_t expireInfo;
    timerCb_t cb;
    void*     arg;

    /* Flags for useful information */
    union {
        struct {
            u32 status:2;
            u32 reserved:30;
        }bf;
        u32 byteVal;
    } flags; 
} hwTmr_info_t;



typedef struct {
    hwTmr_info_t timerInfo[TIMER_NUM];
} hwTmr_ctrl_t;


hwTmr_ctrl_t hwTmr_vars;




void hwTmr_reset(u8 tmrIdx){
    memset((u8*)&hwTmr_vars.timerInfo[tmrIdx], 0x00, sizeof(hwTmr_info_t));
}

void hwTmr_init(u8 tmrIdx, u8 mode){
    hwTmr_reset(tmrIdx);
    TIMER_INIT(tmrIdx, mode);
}


void hwTmr_cancel(u8 tmrIdx)
{
    u8 r = irq_disable();

    /* Write 1 to clear, even if the timer is already set, cancel */
    TIMER_STATE_CLEAR(tmrIdx);
    TIMER_STOP(tmrIdx);

    hwTmr_info_t *pTimer = &hwTmr_vars.timerInfo[tmrIdx];
    memset(pTimer, 0, sizeof(hwTmr_info_t));

    irq_restore(r);
}

hw_timer_sts_t hwTmr_setAbs(u8 tmrIdx, ext_clk_t* absTimer, timerCb_t func, void* arg)
{
    u8 r;
	if ( tmrIdx >= TIMER_NUM ) {
		return HW_TIMER_IS_RUNNING;
	}
    hwTmr_info_t *pTimer = &hwTmr_vars.timerInfo[tmrIdx];

    /* Validation */
    if (TIMER_IDLE != pTimer->flags.bf.status) {
        return HW_TIMER_IS_RUNNING;
    }

    r = irq_disable();

    /* Set expire information */
    pTimer->expireInfo.high = absTimer->high;
    pTimer->expireInfo.low  = absTimer->low;
    pTimer->cb = func;
    pTimer->arg = arg;

    pTimer->flags.bf.status = pTimer->expireInfo.high ? TIMER_WOF : TIMER_WTO;

    /* Safety Check - If time is already past, set timer as Expired */
    if (!pTimer->expireInfo.high && pTimer->expireInfo.low < TIMER_SAFE_BOUNDARY_IN_US(MASTER_CLK_FREQ)) {
        irq_restore(r);
        memset(pTimer, 0, sizeof(hwTmr_info_t));
		if ( func ) {
            func(arg);
		}
        return (hw_timer_sts_t)SUCCESS;
    } else {
        /* Set compare value */
        TIMER_TICK_CLEAR(tmrIdx);
        TIMER_INTERVAL_SET(tmrIdx, pTimer->expireInfo.high ? TIMER_OVERFLOW_VALUE : pTimer->expireInfo.low);

        /* Enable Timer */
        TIMER_START(tmrIdx);
    }

    irq_restore(r);

    return (hw_timer_sts_t)SUCCESS;
}




hw_timer_sts_t hwTmr_set(u8 tmrIdx, u32 t_us, timerCb_t func, void* arg){
    ext_clk_t t;
    t.high = 0;
    t.low = t_us * MASTER_CLK_FREQ;
    return hwTmr_setAbs(tmrIdx, &t, func, arg);
}


void timer_irq_handler(u8 tmrIdx)
{
    hwTmr_info_t *pTimer = &hwTmr_vars.timerInfo[tmrIdx];

    /* Write 1 to clear */
    TIMER_STATE_CLEAR(tmrIdx);
    TIMER_STOP(tmrIdx);
    TIMER_TICK_CLEAR(tmrIdx);

    if (TIMER_WTO == pTimer->flags.bf.status) {
        /* Expired, callback */
        if (pTimer->cb) {
        	int t;

        	t = pTimer->cb(pTimer->arg);

        	if(t < 0){
        		memset(pTimer, 0, sizeof(hwTmr_info_t));
        	}else if(t == 0){
                TIMER_INTERVAL_SET(tmrIdx, pTimer->expireInfo.high ? TIMER_OVERFLOW_VALUE : pTimer->expireInfo.low);

                /* Enable Timer */
                TIMER_START(tmrIdx);
        	}else{
        		pTimer->expireInfo.low = t * MASTER_CLK_FREQ;

                TIMER_INTERVAL_SET(tmrIdx, pTimer->expireInfo.high ? TIMER_OVERFLOW_VALUE : pTimer->expireInfo.low);

                /* Enable Timer */
                TIMER_START(tmrIdx);
        	}
        }
    } else{
        if (--pTimer->expireInfo.high) {
        	TIMER_INTERVAL_SET(tmrIdx, TIMER_OVERFLOW_VALUE);
        } else {
        	TIMER_INTERVAL_SET(tmrIdx, pTimer->expireInfo.low);
            pTimer->flags.bf.status = TIMER_WTO;
        }

        /* Enable Timer again */
        TIMER_START(tmrIdx);
    }
}

void timer_irq0_handler(void)
{
    timer_irq_handler(TIMER_IDX_0);
}

void timer_irq1_handler(void)
{
    timer_irq_handler(TIMER_IDX_1);
}

void timer_irq2_handler(void)
{
    timer_irq_handler(TIMER_IDX_2);
}

