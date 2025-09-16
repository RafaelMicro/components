/**
 * \file            hosal_crytpo_ecjpake.h
 * \brief           hosal_crytpo_ecjpake include file
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
#ifndef HOSAL_CRYPTO_ECJPAKE_H
#define HOSAL_CRYPTO_ECJPAKE_H

#include "mcu.h"
#include "rt_crypto.h"
#include "rt_ecjpake.h"
#include "rt_sha256.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * \brief           hosal_crypto_ecjpack const defined
 */
#define HOSLA_CRYPTO_ECJPAKE_INI  1
#define HOSAL_NUMBER_OF_GENERATES 2

/**
 * \brief           hosal crypto ecjpack operation struct dfeindd
 */
typedef enum {
    HOSAL_ECJPAKE_NULL = 0,
    HOSAL_ECJPAKE_GENERATE_ZKP = 1,
    HOSAL_ECJPAKE_GENERATE_VERIFY = 2,
    HOSAL_ECJPAKE_GENERATE_ZKP_2 = 3,
    HOSAL_ECJPAKE_GENERATE_VERIFY_2 = 4,
    HOSAL_ECJPAKE_COMPUTE_KEY = 5,
} hosal_crypto_ecjpake_operation_t;

/**
 * \brief           hosal crypto ecjpack struct dfeindd
 */
typedef struct {
    ECJPAKE_CTX* ctx;
    ECJPAKEKeyKP* key;
    ECPoint_P256* gen;
    uint8_t* private_key;
    uint8_t* pms;
    hosal_crypto_ecjpake_operation_t crypto_operation;
} hosal_ecjpake_dev_t;

/**
 * \brief           hosal_crypto_ecjpake_init
 * \param[in]       NONE
 * \return          return function status
 */
int hosal_crypto_ecjpake_init(void);
/**
 * \brief           hosal_crypto_ecjpake_operation
 * \param[in]       ecjpake_dev ecjpake operation struct
 * \return          return function status
 */
int hosal_crypto_ecjpake_operation(hosal_ecjpake_dev_t* ecjpake_dev);

#ifdef __cplusplus
}
#endif

#endif
