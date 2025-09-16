/**
 * \file            hosal_crytpo_ecc.c
 * \brief           hosal_crytpo_ecc file
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
#include "rt_ecc.h"
#include "hosal_crypto_ecc.h"
#include "hosal_crypto_sha256.h"
#include "hosal_status.h"

int hosal_crypto_ecc_init(int ctl) {

    int status = STATUS_SUCCESS;

    switch (ctl) {
        case HOSAL_ECC_CURVE_P256_INIT:

            gfp_ecc_curve_p256_init();

            break;

        case HOSAL_ECDA_CURVE_P256_VERIFY_INIT:

            gfp_ecdsa_p256_verify_init();

            break;

        case HOSAL_ECC_CURVE_P192_INIT:

            gfp_ecc_curve_p192_init();

            break;

        case HOSAL_ECC_CURVE_B163_INIT:

            gf2m_ecc_curve_b163_init();

            break;

    }
    return status;
}


int hosal_crypto_ecc_p256(hosal_crypto_ecc_p256_t* ecc_p256) {

    int status = HOSAL_STATUS_SUCCESS;

    if (ecc_p256->crypto_operation == HOSAL_ECDA_P256_SIGNATURE) {
        status = gfp_ecdsa_p256_signature(ecc_p256->signatrue, ecc_p256->p_hash,
                                          ecc_p256->p_key, ecc_p256->p_k);
    } else if (ecc_p256->crypto_operation == HOSAL_ECDA_P256_VERIFY) {
        status = gfp_ecdsa_p256_verify(ecc_p256->signatrue, ecc_p256->p_hash,
                                       ecc_p256->base);
    } else if (ecc_p256->crypto_operation == HOSAL_GFP_P256_VAILD_VERIFY) {
        status = gfp_valid_point_p256_verify( ecc_p256->result);
    } else if (ecc_p256->crypto_operation == HOSAL_GFP_P256_MULTI) {
        status = gfp_point_p256_mult(ecc_p256->result, ecc_p256->base, ecc_p256->p_key);
    } else if (ecc_p256->crypto_operation == HOSAL_GFP_P256_ADD) {
        status = gfp_point_p256_add(ecc_p256->p_point_result, ecc_p256->p_point_x1,
                                    ecc_p256->p_point_x2);
    } else if (ecc_p256->crypto_operation == HOSAL_GFP_P256_MOD_MULTI) {
        gfp_scalar_modmult_p256(ecc_p256->p_result, ecc_p256->p_x, ecc_p256->p_y);
    } else {
        return HOSAL_STATUS_INVALID_PARAM;
    }

    return status;
}

int hosal_crypto_ecc_gf_operation(hosal_crypto_ecc_gf_t* ecc_gf) {

    int status = HOSAL_STATUS_SUCCESS;

    if (ecc_gf->crypto_operation == HOSAL_GFP_P192_MULTI) {
        status = gfp_point_p192_mult(ecc_gf->p_result_x, ecc_gf->p_result_y,
                                     ecc_gf->target_x, ecc_gf->target_y, ecc_gf->target_k);
    } else if (ecc_gf->crypto_operation == HOSAL_GFP_B163_MULTI) {
        gf2m_point_b163_mult(ecc_gf->p_result_x, ecc_gf->p_result_y, ecc_gf->target_x,
                             ecc_gf->target_y, ecc_gf->target_k);
    }

    return status;
}
