/********************************************************************************************************
 * @file     aes128.h
 *
 * @brief    This file provides set of functions to manage the AES128
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
#ifndef _AES_128_H_
#define _AES_128_H_

int AES_Encrypt(unsigned char *Key, unsigned char *Data, unsigned char *Result);

int AES_Decrypt(unsigned char *Key, unsigned char *Data, unsigned char *Result);


#endif /* _AES_128_H_ */
