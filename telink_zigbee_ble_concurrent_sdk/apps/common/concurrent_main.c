/********************************************************************************************************
 * @file     concurrent_main.c
 *
 * @brief	 Common main entry
 *
 * @author
 * @date     Dec. 1, 2017
 *
 * @par      Copyright (c) 2016, Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *
 *			 The information contained herein is confidential and proprietary property of Telink
 * 		     Semiconductor (Shanghai) Co., Ltd. and is available under the terms
 *			 of Commercial License Agreement between Telink Semiconductor (Shanghai)
 *			 Co., Ltd. and the licensee in separate contract or the terms described here-in.
 *           This heading MUST NOT be removed from this file.
 *
 * 			 Licensees are granted free, non-transferable use of the information in this
 *			 file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided.
 *
 *******************************************************************************************************/
#include "user_config.h"
#include "zb_common.h"
#include "../../ble/blt_config.h"

#if BLE_CONCURRENT_MODE

extern void user_init();

/* system clock configuration
 *
 * platform:
 * 		826x
 * 		8258
 * 		HAWK
 *
 *  */
#if defined(MCU_CORE_826x)
	#if(CLOCK_SYS_CLOCK_HZ == 32000000)
		SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_32M_PLL;
	#elif(CLOCK_SYS_CLOCK_HZ == 16000000)
		SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_16M_PLL;
	#else
		#error please config system clock
	#endif
#elif defined(MCU_CORE_8258)
	#if(CLOCK_SYS_CLOCK_HZ == 24000000)
		SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_24M_Crystal;
	#elif(CLOCK_SYS_CLOCK_HZ == 16000000)
		SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_16M_Crystal;
	#elif(CLOCK_SYS_CLOCK_HZ == 48000000)
		SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_48M_Crystal;
	#else
		#error please config system clock
	#endif
#elif defined(MCU_CORE_HAWK)
	#if(CLOCK_SYS_CLOCK_HZ == 16000000)
		SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_16M_PLL;
	#else
		#error please config system clock
	#endif
#endif

enum{
	SYSTEM_RETENTION_NONE,
	SYSTEM_RETENTION_EN,
};

/*
 * platform initiation:
 * 		clock_init: 	system clock selection
 * 		ZB_RADIO_INIT: 	RF module
 * 		gpio_init:		gpio configuration
 * 		ZB_TIMER_INIT:  enable a timer for zigbee mac cca-csma
 *
 * */
static u8 platform_init(void){
	u8 ret = SYSTEM_RETENTION_NONE;

#if defined(MCU_CORE_8258)
	extern void bss_section_clear(void);
	extern void data_section_load();
	if( (analog_read(0x7f) & 0x01) ){	  //recovery from deep sleep
		bss_section_clear();
		data_section_load();
	}else{
		ret = SYSTEM_RETENTION_EN;
	}
#endif

	cpu_wakeup_init();
//ble_rf_drv_init(RF_MODE_BLE_1M);
	//clock_init(g_sysClk);
	clock_init(/*SYS_CLK_16M_Crystal*/SYS_CLK_32M_Crystal);//BLE 16M

	gpio_init();

	ZB_RADIO_INIT();

	//ZB_TIMER_INIT();
	return ret;
}


volatile int zb_task_counter = 0;
void zb_task()
{
    zb_task_counter++;
    tl_zbTaskProcedure();

#if(MODULE_WATCHDOG_ENABLE)
		wd_clear();
#endif
		ev_main();
}

unsigned  long  g_process_thread_en = 0;
unsigned  long  g_process_clock_timeout;
unsigned  long  g_process_clock_start;
extern 	u8					blt_state ;
//_attribute_data_retention_  u8					ble_state;
extern  volatile u8			blt_busy;
int ble_stack_idle()
{
    if(g_process_thread_en&&(blt_busy == 0)&&((blt_state == 8)||(blt_state == 1)))
    {
        return 1;
    }else
    {
        return 0;
    }
}
u32 thr_reg_508 = 0;
static u32 thr_reg_520 = 0;
static u32 thr_reg_528 = 0;
static u32 thr_reg_640 = 0;
static u16 thr_reg_f1c = 0;
static u32 thr_reg_408 = 0;

static u32 thr_reg_f00 = 0;
static u8  thr_reg_f04 = 0;
static u8  thr_reg_f16 = 0;
static u8  thr_reg_f18 = 0;
static u8  thr_reg_f28 = 0;
static u8  thr_reg_428 = 0;
static u8  thr_reg_44c = 0;

void backup_thread_rf_context(void){
    thr_reg_508 = read_reg32(0xc08);
    thr_reg_520 = read_reg32(0xc20);
    thr_reg_528 = read_reg32(0xc28);
    //thr_reg_640 = read_reg32(0x640);
    //thr_reg_f1c = read_reg16(0xf1c);
    //thr_reg_408 = read_reg32(0x408);

    //thr_reg_f00 = read_reg32(0xf00);
    //thr_reg_f04 = read_reg8(0xf04);
    //thr_reg_f16 = read_reg8(0xf16);
    //thr_reg_f18 = read_reg8(0xf18);
    //thr_reg_f28 = read_reg8(0xf28);
    //thr_reg_428 = read_reg8(0x428);//note
    //thr_reg_44c = read_reg8(0x44c);
}
extern u8*        rf_rxBuf;
void restore_thread_rf_context(void){
    //write_reg32(0xc08, thr_reg_508);
    ZB_RADIO_RX_BUF_SET((u16)(u32)(rf_rxBuf));
    write_reg32(0xc20, thr_reg_520);
    write_reg32(0xc28, thr_reg_528);
    //write_reg32(0x640, thr_reg_640);
    //write_reg16(0xf1c, thr_reg_f1c);
   // write_reg32(0x408, thr_reg_408);

    //write_reg32(0xf00,thr_reg_f00);
    //write_reg8(0xf04,thr_reg_f04);
    //write_reg8(0xf16,thr_reg_f16);
    //write_reg8(0xf18,thr_reg_f18);
    //write_reg8(0xf28,thr_reg_f28);
    //write_reg8(0x428,thr_reg_428);
    //write_reg8(0x44c,thr_reg_44c);
}
static u32 ble_reg_508 = 0;
static u32 ble_reg_520 = 0;
static u32 ble_reg_528 = 0;
u32 ble_reg_640 = 0;
static u16 ble_reg_f1c = 0;
static u32 ble_reg_408 = 0;

static u32 ble_reg_f00 = 0;
static u8  ble_reg_f04 = 0;
static u8  ble_reg_f16 = 0;
static u8  ble_reg_f18 = 0;
static u8  ble_reg_f28 = 0;
static u8  ble_reg_428 = 0;
static u8  ble_reg_44c = 0;
void backup_ble_rf_context(void){
    ble_reg_508 = read_reg32(0xc08);
    ble_reg_520 = read_reg32(0xc20);
    ble_reg_528 = read_reg32(0xc28);
   // ble_reg_640 = read_reg32(0x640);
  //  ble_reg_f1c = read_reg16(0xf1c);
  //  ble_reg_408 = read_reg32(0x408);

   // ble_reg_f00 = read_reg32(0xf00);
   // ble_reg_f04 = read_reg8(0xf04);
    //ble_reg_f16 = read_reg8(0xf16);
    //ble_reg_f18 = read_reg8(0xf18);
    //ble_reg_f28 = read_reg8(0xf28);
    //ble_reg_428 = read_reg8(0x428);
   // ble_reg_44c = read_reg8(0x44c);
}

void restore_ble_rf_context(void){
    write_reg32(0xc08, ble_reg_508);
    write_reg32(0xc20, ble_reg_520);
    write_reg32(0xc28, ble_reg_528);
    //write_reg32(0x640, ble_reg_640);
    //write_reg16(0xf1c, ble_reg_f1c);
    //write_reg32(0x408, ble_reg_408);

   // write_reg32(0xf00,ble_reg_f00);
   // write_reg8(0xf04,ble_reg_f04);
   // write_reg8(0xf16,ble_reg_f16);
   // write_reg8(0xf18,ble_reg_f18);
   // write_reg8(0xf28,ble_reg_f28);
   // write_reg8(0x428,ble_reg_428);
   // write_reg8(0x44c,ble_reg_44c);
}
signed char ble_channel = 0;
extern signed char ble_current_channel;

static inline void rf_baseband_reset(void)
{
	REG_ADDR8(0x61) = BIT(0);		//reset_baseband
	REG_ADDR8(0x61) = 0;			//release reset signal
}
void switch_to_zb_context()
{
    rf_baseband_reset();
    backup_ble_rf_context();
        restore_thread_rf_context();
		//rf_drv_250k();
		write_reg8(0x401, 0);
		ZB_RADIO_INIT();
        ZB_RADIO_TRX_CFG((RF_PKT_BUFF_LEN));
        ble_channel = ble_current_channel;
        rf_setChannel(rf_getChannel());
        rf_setTrxState(RF_STATE_RX);
        sleep_us(150);//delete
        reg_rf_irq_status = 0xffff;
		reg_irq_mask |= FLD_IRQ_ZB_RT_EN;
        reg_rf_irq_mask |= (FLD_RF_IRQ_TX | FLD_RF_IRQ_RX);
        //Rf_BaseBandReset ();

}
#define  THREAD_PRE_TIME      (16 * 2 * 1000)
#define  THREAD_AFTER_TIME    (16*4*1000)
int is_switch_to_ble()
{
    if((g_process_clock_timeout - clock_time()) < THREAD_AFTER_TIME)
    {
        return 1;
    }else{
    return 0;}
}
extern unsigned  long  g_process_thread_en;
void switch_to_ble_context()
{
    // do some rf init, set to ble mode
						// ble_rf_init()  // maybe 1~2 ms
						 backup_thread_rf_context();
						rf_baseband_reset();
                        //write_reg32(0x640, ble_reg_640);

                        restore_ble_rf_context();
                        reg_irq_mask &= ~FLD_IRQ_ZB_RT_EN;
    	                reg_rf_irq_status = 0xffff;
    	                reg_irq_mask |= FLD_IRQ_ZB_RT_EN;
		                //rf_drv_1m ();
		                ble_rf_drv_init(RF_MODE_BLE_1M);
                        rf_set_ble_channel (ble_channel);

						g_process_thread_en = 0;
}

volatile int zb_test_cnt = 0;
extern _attribute_data_retention_	my_fifo_t	blt_rxfifo;


void zb_process()
{
     static u8 zigbee_process = 0;
     static int zb_task_number = 0;
    if(ble_stack_idle()&& (blt_rxfifo.rptr == blt_rxfifo.wptr))
    {
        irq_disable();
        ZB_RADIO_RX_DISABLE;
        switch_to_zb_context();
        ZB_RADIO_RX_ENABLE;
        irq_enable();

        extern u8 rf_busyFlag;
        while(1)
        {
            if(is_switch_to_ble()&&!rf_busyFlag )
            {
                irq_disable();
                switch_to_ble_context();
                irq_enable();
                g_process_thread_en = 0;
                zigbee_process = 0;
                gpio_write(GPIO_PB3, 0);
                break;
            }else
            {
                if(zigbee_process==0)
            	{
            		zigbee_process = 1;
            		gpio_write(GPIO_PB3, 1);
            	}

                //if(!zb_isDeviceJoinedNwk()){

                zb_task();
                //}


            }
        }
    }
}

void concurrent_mode_main_loop (void)
{
	//tick_loop ++;

	////////////////////////////////////// BLE entry /////////////////////////////////

	blt_sdk_main_loop();

	////////////////////////////////////// UI entry /////////////////////////////////
	//if(ui_mic_enable){
	//	task_audio();
	//}

	//proc_keyboard (0,0, 0);

	//device_led_process();

	zb_process();

	//blt_pm_proc();
	//led_process();
}

volatile int T_ble_irq_counter = 0;
volatile int T_zb_irq_counter = 0;
volatile unsigned int tx_state=0;
volatile unsigned int rx_state=0;
volatile unsigned int timeout_state=0;



//extern int zb_tx_irq_cnt;
//begin : new irq handler
extern u8 rf_busyFlag;

//end





int main (void) {
	if(platform_init() == SYSTEM_RETENTION_NONE){
		os_init(0);
	}
   // ble_rf_drv_init(RF_MODE_BLE_1M);

	user_init();
//backup the registers
backup_thread_rf_context();
test_init();
//while(1);
    //ble init
    //rf_baseband_reset();
    ble_rf_drv_init(RF_MODE_BLE_1M);
    blc_app_loadCustomizedParameters();  //load customized freq_offset cap value


		user_init_normal ();

    //end

    irq_enable();



	while (1) {
    	concurrent_mode_main_loop ();
	}
}

#endif
