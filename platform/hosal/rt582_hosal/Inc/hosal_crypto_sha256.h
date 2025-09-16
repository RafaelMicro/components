/**
 * \file            hosal_crytpo_sha256.h
 * \brief           hosal_crytpo_sha256 include file
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
#ifndef HOSAL_CRYPTO_SHA256_H
#define HOSAL_CRYPTO_SHA256_H

#include "mcu.h"
#include "rt_crypto.h"
#include "rt_sha256.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
* \brief           HOSAL SHA256 const define
*/
#define HOSLA_CRYPTO_SHA256_INI   2
#define HOSAL_SHA256_DIGEST_SIZE  SHA256_DIGEST_SIZE
#define HOSAL_SHA256_BLOCK_SIZE   SHA256_BLOCK_SIZE
#define HOSAL_NUMBER_OF_GENERATES 2

/**
* \brief           HOSAL SHA256 operation enum type
*
*/
typedef  enum {
    HOSAL_SHA256_DIGEST_INIT = 0,
    HOSAL_SHA256_DIGEST_STARTS = 1,
    HOSAL_SHA256_DIGEST_UPDATE = 2,
    HOSAL_SHA256_DIGEST_FINISH = 3,
    HOSAL_SHA256_DIGEST = 4,
    HOSAL_SHA256_HMAC = 5,
    HOSAL_SHA256_HKDF = 6,
    HOSAL_SHA256_PBKDF2_HMAC = 7,
} hosal_crypto_sha256_operation_t;

/**
* \brief           HOSAL SHA256 operation struct defined
*
*/
typedef struct {
    uint8_t* key_ptr;
    uint8_t* in_ptr;
    uint8_t* out_ptr;
    uint8_t* secret;
    uint8_t* salt;
    uint8_t* info;
    uint32_t key_length;
    uint32_t in_length;
    uint32_t out_len;
    uint32_t secret_len;
    uint32_t salt_len;
    uint32_t info_len;
    pbkdf2_st* pbkdf2;
    hosal_crypto_sha256_operation_t crypto_operation;
    sha256_context sha_cnxt;
} hosal_sha256_dev_t;

/**
 * \brief           hosal_crypto_sha256_init
 * \param[in]       NONE
 * \return          return function status
 */
int hosal_crypto_sha256_init(void);
/**
 * \brief           hosal_crypto_sha256_operation
 * \param[in]       sha256_dev sha256  operation struct
 * \return          return function status
 */
int hosal_crypto_sha256_operation(hosal_sha256_dev_t* sha256_dev);

#ifdef __cplusplus
}
#endif

#endif
