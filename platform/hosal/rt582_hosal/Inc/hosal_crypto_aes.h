/**
 * \file            hosal_crytpo_aes.h
 * \brief           hosal_crytpo_aes include file
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

#ifndef HOSAL_CRYPTO_AES_H
#define HOSAL_CRYPTO_AES_H

#include "mcu.h"
#include "rt_crypto.h"
#include "rt_sha256.h"
#include "rt_aes.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * \brief           hosal crypto aes const defined
 */
#define HOSLA_CRYPTO_AES_INI          	1            /**< crypto aes intinal const defined */
#define HOSAL_AES_KEY128BIT     AES_KEY128           /*!< AES operation 128 bit            */
#define HOSAL_AES_KEY192BIT     AES_KEY192           /*!< AES operation 192 bit            */
#define	HOSAL_AES_KEY256BIT 	AES_KEY256           /*!< AES operation 256 bit            */
#define HOSAL_AES_BLOCKLEN		AES_BLOCKLEN         /*!< Block length in bytes, AES is 128bits per block  */
#define HOSAL_NUMBER_OF_GENERATES   2                /*!< crypto generates */
/**
 * \brief           hosal crypto operation defined
 */
typedef  enum
{
	HOSAL_AES_CRYPTO_NULL	= 0,
    HOSAL_AES_CRYPTO_DECRYPT = 1,     /*!< AES operation for decryption   */
    HOSAL_AES_CRYPTO_ENCRYPT = 2,     /*!< AES operation for encryption   */
	HOSAL_AES_CMAC_LOAD_MAC_KEY = 3,
	HOSAL_AES_CMAC_CBC = 4,
} hosal_crypto_operation_t;
/**
 * \brief           hosal crypto key const defined
 */
typedef  enum
{
    HOSAL_AES_128_BIT = 128,           /*!< AES operation 128 bit            */
    HOSAL_AES_192_BIT = 192,           /*!< AES operation 192 bit            */
	HOSAL_AES_256_BIT = 256,           /*!< AES operation 256 bit            */
} hosal_crypto_key_bit_t;

/**
 * \brief           hosal crypto aes struct defined
 */
typedef struct {
	uint8_t* 					in_ptr;
	uint8_t*  					out_ptr; 
	uint8_t* 					key_ptr;
	uint8_t* 					iv;
	uint32_t					cbc_length;
	uint32_t					len;
	hosal_crypto_key_bit_t 		bit;
	hosal_crypto_operation_t	crypto_operation;
}hosal_aes_dev_t;


/**
 * \brief           hosal_crypto_aes_init
 * \param[in]       NONE 
 * \return          return function status
 */
int hosal_crypto_aes_init(void);
/**
 * \brief           hosal_crypto_aes_operation
 * \param[in]       ase_dev aes input value struct 
 * \return          return function status
 */
int hosal_crypto_aes_operation(hosal_aes_dev_t* ase_dev);
/**
 * \brief           hosal_crypto_aes_operation
 * \param[in]       ase_dev aes cbc input value struct 
 * \return          return function status
 */
int hosal_crypto_aes_cbc_operation(hosal_aes_dev_t* ase_dev);
/**
 * \brief           hosal_crypto_aes_operation
 * \param[in]       ase_dev aes ctr input value struct 
 * \return          return function status
 */
int hosal_crypto_aes_ctr_operation(hosal_aes_dev_t* aes_dev);
/**
 * \brief           hosal_crypto_aes_operation
 * \param[in]       ase_dev aes cmac input value struct 
 * \return          return function status
 */
int hosal_crypto_aes_cmac_operation(hosal_aes_dev_t* aes_dev);
					  
#ifdef __cplusplus
}
#endif

#endif
