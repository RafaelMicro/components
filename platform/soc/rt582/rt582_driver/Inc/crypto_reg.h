/**
 * \file            crypto_reg.h
 * \brief           crypto_reg.h header file
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
 * Author: ives.lee
 */
#ifndef CRYPTO_REG_H
#define CRYPTO_REG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           Crypto control register
 */
typedef union crypto_ctrl_struct {

    struct crypto_ctrl_b {
        __IO uint32_t vlw_op_num     : 8;       /*!< Crypto control parameter */
        __IO uint32_t vlw_sb_num     : 5;       /*!< Crypto control parameter */
        __IO uint32_t reserved1      : 3;       /*!< Reserved bits */
        __IO uint32_t en_crypto      : 1;       /*!< Crypto control parameter */
        __IO uint32_t enable_sha     : 1;       /*!< Crypto control parameter */
        __IO uint32_t reserved2      : 6;       /*!< Reserved bits */
        __IO uint32_t crypto_done    : 1;       /*!< Crypto control parameter */
        __IO uint32_t sha_done       : 1;       /*!< Crypto control parameter */
        __IO uint32_t crypto_busy    : 1;       /*!< Crypto control parameter */
        __IO uint32_t sha_busy       : 1;       /*!< Crypto control parameter */
        __IO uint32_t reserved3      : 3;       /*!< Reserved bits */
        __IO uint32_t clr_crypto_int : 1;       /*!< Crypto control parameter */
    } bit;

    uint32_t reg;

} crypto_ctrl_t;

/**
 * \brief           Crypto total register
 */
typedef struct {
    __IO crypto_ctrl_t crypto_cfg;              /*!< 0x00 Crypto control register */

} CRYPTO_T;

#ifdef __cplusplus
}
#endif

#endif /* End of CRYPTO_REG_H */
