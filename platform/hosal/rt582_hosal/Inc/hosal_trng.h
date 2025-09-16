/**
 * \file            hosal_wdt.h
 * \brief           Hosal Watch Dog timer header file
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
 *
 * Author:          
 */

#ifndef HOSAL_TRNG_H
#define HOSAL_TRNG_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "mcu.h"
#include "trng.h"


/**
 * \brief           Hosal trng get random number
 * \param[in]       buffer: random data buffer
 * \param[in]       number: get random number times
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM, 
 *                  STATUS_INVALID_REQUEST
 */
int hosal_trng_get_random_number(uint32_t *buffer, uint32_t number);



#ifdef __cplusplus
}
#endif

#endif /* End of HOSAL_TRNG_H */
