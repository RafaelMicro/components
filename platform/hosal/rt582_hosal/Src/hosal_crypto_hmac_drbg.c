/**
 * \file            hosal_crytpo_hmac_drbg.c
 * \brief           hosal_crytpo_hmac_drbg file
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
#include "hosal_crypto_hmac_drbg.h"
#include "hosal_status.h"


int hosal_crypto_hmac_drbg_init(void) {

    int status= HOSAL_STATUS_SUCCESS;

    sha256_vector_init();

    return status;
}

int hosal_crypto_hmac_drbg_operation(hosal_hmac_drbg_dev_t* hmac_drbg) {
    int status, i, index;
    uint8_t* dataptr;

    hmac_drbg_state hmac_drbg_ctx;
    status = HOSAL_STATUS_SUCCESS;
    index = 0;


    if (hmac_drbg->crypto_operation == HOSAL_HMAC_DRBG_HMAC) {
        //printf("1 %x %d \n",(uint8_t*)hmac_drbg->seed_material,hmac_drbg->seed_material_length);

        hmac_drbg_instantiate(&hmac_drbg_ctx, hmac_drbg->seed_material,
                              hmac_drbg->seed_material_length);

        //printf("2 %x %d \n",(uint8_t*)hmac_drbg->in_ptr,hmac_drbg->in_length);

        hmac_drbg_update(&hmac_drbg_ctx, hmac_drbg->in_ptr, hmac_drbg->in_length);

        if (hmac_drbg->data_len == 0) {
            for (i = 0; i < HOSAL_NUMBER_OF_GENERATES; i++) {
                hmac_drbg_generate(hmac_drbg->out_ptr, &hmac_drbg_ctx, hmac_drbg->out_len, NULL,
                                   hmac_drbg->data_len);
            }
        } else {



            //need to debug test case fail
            for (i = 0; i < HOSAL_NUMBER_OF_GENERATES; i++) {
                dataptr = (uint8_t*)(&hmac_drbg->data_ptr);

                //printf("3 %x %d \n", (uint8_t*)(hmac_drbg->data_ptr+index),hmac_drbg->data_len);

                //printf(" %x ", *(uint32_t*)(&hmac_drbg->data_ptr + index));
                //hmac_drbg_generate(hmac_drbg->out_ptr, &hmac_drbg_ctx, hmac_drbg->out_len,(uint8_t*)(hmac_drbg->data_ptr[i]), hmac_drbg->data_len);

                hmac_drbg_generate(hmac_drbg->out_ptr, &hmac_drbg_ctx, hmac_drbg->out_len,
                                   (uint8_t*)(hmac_drbg->data_ptr + index), hmac_drbg->data_len);

                index =  hmac_drbg->data_len;
            }
        }

    } else {
        return -1;
    }

    return status;
}

int hosal_hmac_drbg_generate_k(hosal_hmac_drbg_dev_t* hmac_drbg) {

    hmac_drbg_state    hmac_drbg_ctx;
    uint32_t           i;
    uint8_t*            ptr_k, *ptr_order;

    hmac_drbg_instantiate(&hmac_drbg_ctx, hmac_drbg->seed_material,
                          hmac_drbg->seed_material_length);       /*RFC6979 section 3.2 step d~ step g*/

    while (1) {

        hmac_drbg_generate(hmac_drbg->out_ptr, &hmac_drbg_ctx, hmac_drbg->out_len, NULL,
                           0);
        /*we need 32 bytes random k*/
        //be_print_hex_bytes("random_k:", k, ECDSA_P256_LENGTH);

        /* we should compare random value k with order of NIST-P256 "q"
         * if k must be within [1, q-1]
         * remember: k and order is big endian.
         */

        ptr_order = (uint8_t*) hmac_drbg->in_ptr;
        ptr_k = hmac_drbg->out_ptr;

        for (i = 0; i < 32; i++) {
            if (*hmac_drbg->out_ptr < *ptr_order) {
                return -1;    /*ok we find k now*/
            } else {
                ptr_k++;
                ptr_order++;
            }
        }

        /*if code goto here.. it means k > q, we should regenerate k... should we call this??
          it seems that hmac_drbg_generate alreday update it...???? */
        hmac_drbg_update(&hmac_drbg_ctx, NULL, 0);

    }
}


uint32_t hosal_hmac_drbg_instantiate(hmac_drbg_state* state,
                                     uint8_t* seed_material, 
                                     uint32_t seed_material_length) {
    int status = HOSAL_STATUS_SUCCESS;

    status = hosal_hmac_drbg_instantiate(state, seed_material,
                                         seed_material_length);

    return status;
}

void  hosal_hmac_drbg_update(hmac_drbg_state* state, uint8_t* data,
                             uint32_t  data_length) {
    hosal_hmac_drbg_update(state, data, data_length);
}

void  hosal_hmac_drbg_generate(uint8_t* out_result, hmac_drbg_state* state,
                               uint32_t request_bytes, uint8_t* data, 
                               uint32_t data_length) {
    hmac_drbg_generate(out_result, state, request_bytes, data, data_length);
}
