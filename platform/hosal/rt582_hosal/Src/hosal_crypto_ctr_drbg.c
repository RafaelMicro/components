/**
 * \file            hosal_crytpo_ctr_drbg.c
 * \brief           hosal_crytpo_ctr_drbg file
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
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "mcu.h"
#include "rt_crypto.h"
#include "hosal_crypto_ctr_drbg.h"
#include "hosal_status.h"


int hosal_crypto_curve_c25519_init(void) {

    int status = HOSAL_STATUS_SUCCESS;

    curve_c25519_init();

    return status;
}

int hosal_crypto_curve_c25519_release(void) {

    int status = HOSAL_STATUS_SUCCESS;

    curve25519_release();

    return status;
}

int hosal_crypto_curve25519_operation(hosal_crypto_curve25519_t* curve25519) {

    int status = HOSAL_STATUS_SUCCESS;

    if (curve25519->crypto_operation == HOSAL_CURVE_C25519_MUL) {
        curve25519_point_mul(curve25519->blind_zr, curve25519->public_key,
                             curve25519->secret_key, curve25519->base_point);
    } else {
        status = HOSAL_STATUS_INVALID_PARAM;
    }

    return status;
}
