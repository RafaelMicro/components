/**
 * \file            hosal_crytpo_aes_ccm.h
 * \brief           hosal_crytpo_aes_ccm. include file
 */

/*
 * Copyright (c) 2024 Rafael Micro
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of library_name.
 *
 * Author:
 */

#ifndef HOSAL_CRYPTO_AES_CCM_H
#define HOSAL_CRYPTO_AES_CCM_H

#include "mcu.h"
#include "rt_crypto.h"
#include "rt_sha256.h"
#include "rt_aes.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * \brief           Crypto AES Key bit define
 */
#define HOSAL_AES_KEY128BIT        AES_KEY128           /*!< AES 128 bit const define   */
#define HOSAL_AES_KEY192BIT        AES_KEY192           /*!< AES 192 bit const define   */
#define HOSAL_AES_KEY256BIT        AES_KEY256           /*!< AES 256 bit const define   */
#define HOSAL_AES_BLOCKLEN         AES_BLOCKLEN         /*!< Block length in bytes, AES is 128bits per block  */
#define HOSAL_NUMBER_OF_GENERATES  2
/**
 * \brief           Crypto AES ccm decrypt and encrypt enum defined.
 */
typedef  enum {
    HOSAL_AES_CCM_DECRYPT = 0,
    HOSAL_AES_CCM_ENCRYPT = 1,
} hosal_crypto_operation_t;
/**
 * \brief           Crypto AES Key bit defin enum defined.
 */
typedef  enum
{
    HOSAL_AES_128_BIT = 128,     /*!< AES crypto 128 bit   */
    HOSAL_AES_192_BIT = 192,     /*!< AES crypto 192 bit   */
	HOSAL_AES_256_BIT = 256,     /*!< AES crypto 256 bit   */   
} hosal_crypto_key_bit_t;
/**
 * \brief           hosal aes crypto struct define.
 */
typedef struct {
    uint8_t*   key_ptr;
    uint32_t   bit;
    uint8_t*   payload_buf;
    uint32_t   payload_length;
    uint8_t*   nonce;
    uint8_t*   hdr;
    uint32_t   hdr_len;
    uint8_t*   data;
    uint32_t   data_len;
    uint32_t   mlen;
    uint8_t*    out_buf;
    uint32_t*   out_buf_len;
    hosal_crypto_operation_t    crypto_operation;
} hosal_aes_ccm_dev_t;

/**
 * \brief           hosal_crypto_aes_ccm_init
 * \return          return function status
 */
int hosal_crypto_aes_ccm_init(void);
/**
 * \brief           hosal_crypto_aes_ccm_operation
 * \param[in]       aes_ccm_dev  aes ccm strct 
 * \return          return function status
 */
int hosal_crypto_aes_ccm_operation(hosal_aes_ccm_dev_t* aes_ccm_dev);

#ifdef __cplusplus
}
#endif

#endif
