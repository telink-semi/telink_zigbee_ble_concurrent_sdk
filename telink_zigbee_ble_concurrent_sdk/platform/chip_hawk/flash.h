/********************************************************************************************************
 * @file     flash.h
 *
 * @brief    This file provides set of driver functions to read and write the internal flash
 *
 * @author   jian.zhang@telink-semi.com
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
#ifndef _FLASH_H_
#define _FLASH_H_

#include "bsp.h"

/**
 *  @brief  Define command of flash operation 
 */
enum {
    FLASH_WRITE_STATUS_CMD  =   0x01,
    FLASH_WRITE_CMD         =   0x02,
    FLASH_READ_CMD          =   0x03,
    FLASH_WRITE_ENABLE_CMD  =   0x06,
    FLASH_WRITE_DISABLE_CMD =   0x04,
    FLASH_READ_STATUS_CMD   =   0x05,
    FLASH_SECT_ERASE_CMD    =   0x20,
    FLASH_BLK_ERASE_CMD     =   0xD8,
    FLASH_POWER_DOWN        =   0xB9,
    FLASH_GET_JEDEC_ID      =   0x9F,
};

/**
 * @brief      This function serves to erase a sector.
 * @param[in]  Addr - the start address of the sector needs to erase.
 * @return     none
 */
extern void flash_erase_sector(unsigned int Addr);

/**
 * @brief      This function writes the buffer's content to a page.
 * @param[in]  Addr - the start address of the page
 * @param[in]  Len  - the length(in byte) of content needs to write into the page
 * @param[in]  Buf  - the start address of the content needs to write into
 * @return     none
 */
extern void flash_write_page(unsigned int Addr, unsigned int Len, unsigned char *Buf);

/**
 * @brief      This function reads the content from a page to the buf.
 * @param[in]  Addr - the start address of the page
 * @param[in]  Len  - the length(in byte) of content needs to read out from the page
 * @param[out] Buf  - the start address of the buffer
 * @return     none
 */
extern void flash_read_page(unsigned int Addr, unsigned int Len, unsigned char *Buf);

/**
 * @brief     read flash ID
 * @param[in] FLASH_ID - the buffer address to store the flash ID.
 * @return    none.
 */
extern void FLASH_GetID(unsigned int* FLASH_ID);

#endif /* _FLASH_H_ */
