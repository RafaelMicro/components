/**
 * \file            hosal_crytpo_ctr_drbg.h
 * \brief           hosal_crytpo_ctr_drbg include file
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
#ifndef HOSAL_CRYPTO_CTR_DRBG_H
#define HOSAL_CRYPTO_CTR_DRBG_H

#include "mcu.h"
#include "rt_crypto.h"
#include "rt_sha256.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief           hosal crypto curve c25519 const defined
 */
#define HOSAL_CURVE_C25519_INIT             1
/**
 * \brief           hosal crypto aes struct defined
 */
typedef  enum {
    HOSAL_CURVE_NULL = 0,         /*!< CURVE operation value defineds   */
    HOSAL_CURVE_C25519_MUL = 1,   /*!< CURVE operation value defineds   */
} hosal_crypto_operation_t;


/**
 * \brief           hosal crypto curve 25519 operation struct defined
 */
typedef struct {

    uint32_t* blind_zr;
    uint32_t* public_key;
    uint32_t* secret_key;
    uint32_t* base_point;
    hosal_crypto_operation_t crypto_operation;
} hosal_crypto_curve25519_t;

/**
 * \brief           hosal_crypto_curve_c25519_init
 * \param[in]       NONE
 * \return          return function status
 */
int hosal_crypto_curve_c25519_init(void);
/**
 * \brief           hosal_crypto_curve25519_operation
 * \param[in]       curve25519 cureve 25519 intput value;
 * \return          return function status
 */
int hosal_crypto_curve25519_operation(hosal_crypto_curve25519_t* curve25519);
/**
 * \brief           hosal_crypto_curve_c25519_release
 * \param[in]       NONE
 * \return          return function status
 */
int hosal_crypto_curve_c25519_release(void) ;

#ifdef __cplusplus
}
#endif

#endif
