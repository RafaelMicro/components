/**
 * \file            hosal_crytpo_sha256.c
 * \brief           hosal_crytpo_sha256 file
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
#include "hosal_crypto_sha256.h"
#include "hosal_status.h"
#include "mcu.h"

int hosal_crypto_sha256_init(void) {

    int status = HOSAL_STATUS_SUCCESS;

    sha256_vector_init();

    return status;
}

int hosal_crypto_sha256_operation(hosal_sha256_dev_t* sha256_dev) {
    int status;
    status = HOSAL_STATUS_SUCCESS;

    if (sha256_dev->crypto_operation == HOSAL_SHA256_HMAC) {
        hmac_sha256(sha256_dev->key_ptr, sha256_dev->key_length,
                    sha256_dev->in_ptr, sha256_dev->in_length,
                    sha256_dev->out_ptr);
    } else if (sha256_dev->crypto_operation == HOSAL_SHA256_HKDF) {
        status = hkdf_sha256(sha256_dev->out_ptr, sha256_dev->out_len,
                             sha256_dev->in_ptr, sha256_dev->in_length,
                             sha256_dev->salt, sha256_dev->salt_len,
                             sha256_dev->info, sha256_dev->info_len);
    } else if (sha256_dev->crypto_operation == HOSAL_SHA256_DIGEST) {
        sha256_init(&sha256_dev->sha_cnxt);	
        sha256_update(&sha256_dev->sha_cnxt, sha256_dev->in_ptr,
                      sha256_dev->in_length); //test sha256("abc")
        sha256_finish(&sha256_dev->sha_cnxt, sha256_dev->out_ptr);                           
    } else if (sha256_dev->crypto_operation == HOSAL_SHA256_DIGEST_INIT) {
        sha256_init(&sha256_dev->sha_cnxt);
    } else if (sha256_dev->crypto_operation == HOSAL_SHA256_DIGEST_UPDATE) {
        sha256_update(&sha256_dev->sha_cnxt, sha256_dev->in_ptr,
                      sha256_dev->in_length); //test sha256("abc")
    } else if (sha256_dev->crypto_operation == HOSAL_SHA256_DIGEST_FINISH) {
        sha256_finish(&sha256_dev->sha_cnxt, sha256_dev->out_ptr);
    } else if (sha256_dev->crypto_operation == HOSAL_SHA256_PBKDF2_HMAC) {
        status = pbkdf2_hmac(sha256_dev->pbkdf2);
    } else {
        return -1;
    }

    return status;
}
