/**
 * \file            hosal_crytpo_ecjpake.c
 * \brief           hosal_crytpo_ecjpake file
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
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "hosal_crypto_ecjpake.h"
#include "hosal_status.h"
#include "mcu.h"

int hosal_crypto_ecjpake_init(void) {
    int status = HOSAL_STATUS_SUCCESS;

    sha256_vector_init();

    return status;
}

int hosal_crypto_ecjpake_operation(hosal_ecjpake_dev_t* ecjpake_dev) {
    int status;

    status = HOSAL_STATUS_SUCCESS;
    if (ecjpake_dev->crypto_operation == HOSAL_ECJPAKE_GENERATE_ZKP) {

        ecjpake_generate_zkp(ecjpake_dev->ctx, ecjpake_dev->key,
                             ecjpake_dev->gen, ecjpake_dev->private_key);

    } else if (ecjpake_dev->crypto_operation == HOSAL_ECJPAKE_GENERATE_VERIFY) {

        status = ecjpake_verify_zkp(ecjpake_dev->ctx, ecjpake_dev->gen,
                                    ecjpake_dev->key);
    } else if (ecjpake_dev->crypto_operation == HOSAL_ECJPAKE_GENERATE_ZKP_2) {
        status = ecjpake_generate_step2_zkp(ecjpake_dev->ctx, ecjpake_dev->key);

    } else if (ecjpake_dev->crypto_operation
               == HOSAL_ECJPAKE_GENERATE_VERIFY_2) {

        status = ecjpake_verify_step2_zkp(ecjpake_dev->ctx, ecjpake_dev->key);

    } else if (ecjpake_dev->crypto_operation == HOSAL_ECJPAKE_COMPUTE_KEY) {
        status = ecjpake_compute_key(ecjpake_dev->ctx, ecjpake_dev->key,
                                     ecjpake_dev->pms);
    }

    /*server ecjpake ctx*/

    return status;
}
