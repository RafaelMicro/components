/**
 * \file           trng.h
 * \brief          true random number generator definition header file
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

#ifndef _RT584_TRNG_H_
#define _RT584_TRNG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "mcu.h"

/**
 * \brief           Generate a true 32-bits random number.
 * \return          A 32-bits random number
 * \details
 *                  Generate a true 32bits random number.
 *                  Please notice: this function is block mode, it will block about 4ms ~ 6ms.
 *                  If you want to use non-block mode, maybe you should use interrupt mode.
 *
 */
int get_random_number(uint32_t* p_buffer, uint32_t number);

#ifdef __cplusplus
}
#endif

#endif


