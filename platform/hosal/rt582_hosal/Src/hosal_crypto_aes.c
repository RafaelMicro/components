/**
 * \file            hosal_crytpo_aes.c
 * \brief           hosal_crytpo_aes file
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
#include "hosal_crypto_aes.h"
#include "hosal_status.h"
#include "mcu.h"
#include "rt_crypto.h"

int hosal_crypto_aes_init(void) {

    int status;

    status = HOSAL_STATUS_SUCCESS;

    aes_fw_init();

    return status;
}

int hosal_crypto_aes_operation(hosal_aes_dev_t* aes_dev) {

    uint8_t i, len = (aes_dev->len / AES_BLOCKLEN);
    uint8_t* in_buf;
    uint8_t* out_buf;
    static struct aes_ctx ctx;

    i = 0;
    in_buf = NULL;
    out_buf = NULL;

    aes_acquire(&ctx);

    aes_key_init(&ctx, aes_dev->key_ptr, aes_dev->bit);

    aes_load_round_key(&ctx);

    if (aes_dev->bit == HOSAL_AES_128_BIT) {

        in_buf = (uint8_t*)aes_dev->in_ptr;
        out_buf = aes_dev->out_ptr;

        if (aes_dev->crypto_operation == HOSAL_AES_CRYPTO_ENCRYPT) {
            aes_ecb_encrypt(&ctx, aes_dev->in_ptr, aes_dev->out_ptr);
        } else if (aes_dev->crypto_operation == HOSAL_AES_CRYPTO_DECRYPT) {
            aes_ecb_decrypt(&ctx, aes_dev->in_ptr, aes_dev->out_ptr);
        }

    } else if (aes_dev->bit == HOSAL_AES_256_BIT) {

        in_buf = (uint8_t*)aes_dev->in_ptr;
        out_buf = aes_dev->out_ptr;

        if (aes_dev->crypto_operation == HOSAL_AES_CRYPTO_ENCRYPT) {
            aes_ecb_encrypt(&ctx, aes_dev->in_ptr, aes_dev->out_ptr);
        } else if (aes_dev->crypto_operation == HOSAL_AES_CRYPTO_DECRYPT) {
            aes_ecb_decrypt(&ctx, aes_dev->in_ptr, aes_dev->out_ptr);
        }
    }

    aes_release(&ctx);

    return HOSAL_STATUS_SUCCESS;
}

static struct aes_ctx ctx_cbc;

int hosal_crypto_aes_cbc_operation(hosal_aes_dev_t* aes_dev) {

    uint8_t iv[16];

    memset(iv, 0, sizeof(iv));

    aes_acquire(&ctx_cbc);

    aes_key_init(&ctx_cbc, aes_dev->key_ptr, aes_dev->bit);

    aes_load_round_key(&ctx_cbc);

    aes_iv_set(&ctx_cbc, iv);

    if (aes_dev->bit == HOSAL_AES_128_BIT) {

        if (aes_dev->crypto_operation == HOSAL_AES_CRYPTO_ENCRYPT) {

            aes_cbc_buffer_encrypt(&ctx_cbc, aes_dev->in_ptr, aes_dev->out_ptr,
                                   aes_dev->cbc_length);
        } else if (aes_dev->crypto_operation == HOSAL_AES_CRYPTO_DECRYPT) {

            aes_cbc_buffer_decrypt(&ctx_cbc, aes_dev->in_ptr, aes_dev->out_ptr,
                                   aes_dev->cbc_length);
        }
    }

    aes_release(&ctx_cbc);

    return HOSAL_STATUS_SUCCESS;
}

int hosal_crypto_aes_ctr_operation(hosal_aes_dev_t* aes_dev) {

    struct aes_ctx ctx;
    uint32_t offset;
    uint8_t stream_block[16];
    offset = 0;

    aes_acquire(&ctx);

    aes_key_init(&ctx, aes_dev->key_ptr, aes_dev->bit);

    aes_load_round_key(&ctx);

    aes_iv_set(&ctx, aes_dev->iv);

    if (aes_dev->bit == HOSAL_AES_128_BIT) {

        if (aes_dev->crypto_operation == HOSAL_AES_CRYPTO_ENCRYPT) {

            /* this is sample to demo "streaming character" */
            aes_ctr_buffer_crypt(&ctx, aes_dev->in_ptr, aes_dev->out_ptr,
                                 stream_block, &offset, 15);

            aes_ctr_buffer_crypt(&ctx, aes_dev->in_ptr + 15,
                                 aes_dev->out_ptr + 15, stream_block, &offset,
                                 3);

            aes_ctr_buffer_crypt(&ctx, aes_dev->in_ptr + 18,
                                 aes_dev->out_ptr + 18, stream_block, &offset,
                                 18);

        } else if (aes_dev->crypto_operation == HOSAL_AES_CRYPTO_DECRYPT) {

            aes_ctr_buffer_crypt(&ctx, aes_dev->in_ptr, aes_dev->out_ptr,
                                 stream_block, &offset, 10);

            aes_ctr_buffer_crypt(&ctx, aes_dev->in_ptr + 10,
                                 aes_dev->out_ptr + 10, stream_block, &offset,
                                 7);

            aes_ctr_buffer_crypt(&ctx, aes_dev->in_ptr + 17,
                                 aes_dev->out_ptr + 17, stream_block, &offset,
                                 19);
        }
    }

    if (aes_dev->bit == HOSAL_AES_192_BIT) {

        if (aes_dev->crypto_operation == HOSAL_AES_CRYPTO_ENCRYPT) {

            aes_ctr_buffer_crypt(&ctx, aes_dev->in_ptr, aes_dev->out_ptr,
                                 stream_block, &offset, 5);

            aes_ctr_buffer_crypt(&ctx, aes_dev->in_ptr + 5,
                                 aes_dev->out_ptr + 5, stream_block, &offset,
                                 11);

            aes_ctr_buffer_crypt(&ctx, aes_dev->in_ptr + 16,
                                 aes_dev->out_ptr + 16, stream_block, &offset,
                                 20);

        } else if (aes_dev->crypto_operation == HOSAL_AES_CRYPTO_DECRYPT) {

            aes_ctr_buffer_crypt(&ctx, aes_dev->in_ptr, aes_dev->out_ptr,
                                 stream_block, &offset, 10);

            aes_ctr_buffer_crypt(&ctx, aes_dev->in_ptr + 10,
                                 aes_dev->out_ptr + 10, stream_block, &offset,
                                 7);

            aes_ctr_buffer_crypt(&ctx, aes_dev->in_ptr + 17,
                                 aes_dev->out_ptr + 17, stream_block, &offset,
                                 19);
        }
    }

    aes_release(&ctx);

    return HOSAL_STATUS_SUCCESS;
}

int hosal_crypto_aes_cmac_operation(hosal_aes_dev_t* aes_dev) {

    struct aes_ctx ctx;

    aes_acquire(&ctx);

    aes_key_init(&ctx, aes_dev->key_ptr, aes_dev->bit);

    aes_load_round_key(&ctx);

    if (aes_dev->bit == HOSAL_AES_128_BIT) {

        if (aes_dev->crypto_operation == HOSAL_AES_CMAC_LOAD_MAC_KEY) {

            aes_ecb_encrypt(&ctx, aes_dev->in_ptr, aes_dev->out_ptr);
        } else {

            /*load key to secure engine*/
            aes_load_round_key(&ctx);

            aes_iv_set(&ctx, aes_dev->iv);

            /*RFC4493: step 5. for i:=1 to n-1 do... so if n=1 it will NOT do the cbc mode */
            //n--;
            aes_dev->len--;
            if (aes_dev->len > 0) {
                /*  CBC only count block1 ~ block (n-1), (block1 is the first block)
                 *  REMARK: because we use the same buffer for in_buf/out_buf
                 *  IMPORTANT: So original data will lose here.
                 *  Or you can allocate a "temp" buffer to save cbc data...
                 */
                aes_cbc_buffer_encrypt(&ctx, aes_dev->in_ptr, aes_dev->in_ptr,
                                       (aes_dev->len << 4));
            }

            aes_iv_get(&ctx, aes_dev->iv); /*get IV*/

            aes_xorwith((uint32_t*)aes_dev->iv, (uint32_t*)aes_dev->iv,
                        (uint32_t*)aes_dev->out_ptr);

            aes_ecb_encrypt(
                &ctx, aes_dev->iv,
                aes_dev->out_ptr); /*temp_buf is the finial mac message */
        }
    }
    aes_release(&ctx);

    return HOSAL_STATUS_SUCCESS;
}
