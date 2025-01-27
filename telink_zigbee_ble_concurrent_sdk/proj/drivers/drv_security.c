/********************************************************************************************************
 * @file    drv_security.c
 *
 * @brief   This is the source file for drv_security
 *
 * @author  Zigbee Group
 * @date    2023
 *
 * @par     Copyright (c) 2023, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
#include "../tl_common.h"
extern void bls_set_enc_dec_busy(int flag);
void drv_aes_encrypt(u8 *key, u8 *plain, u8 *result)
{
    bls_set_enc_dec_busy(1);
#if defined(MCU_CORE_8258) || defined(MCU_CORE_B91)
    aes_encrypt(key, plain, result);
#elif defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL721X)
    //ske_lp_crypto(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_ENCRYPT, key, 0, NULL, plain, result, 16);
    ske_lp_aes128_ecb_one_block(SKE_CRYPTO_ENCRYPT, (unsigned int *)key, (unsigned int *)plain, (unsigned int *)result);
#endif
    bls_set_enc_dec_busy(0);
}


void drv_aes_decrypt(u8 *key, u8 *cipher, u8 *result)
{
    bls_set_enc_dec_busy(1);
#if defined(MCU_CORE_8258) || defined(MCU_CORE_B91)
    aes_decrypt(key, cipher, result);
#elif defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL721X)
    //ske_lp_crypto(SKE_ALG_AES_128, SKE_MODE_ECB, SKE_CRYPTO_DECRYPT, key, 0, NULL, cipher, result, 16)
    ske_lp_aes128_ecb_one_block(SKE_CRYPTO_DECRYPT, (unsigned int *)key, (unsigned int *)cipher, (unsigned int *)result);
#endif
    bls_set_enc_dec_busy(0);
}
