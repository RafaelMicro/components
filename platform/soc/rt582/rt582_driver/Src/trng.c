/**
 * \file            trng.c
 * \brief           trng driver file
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
 * Author:          ives.lee
 */


#include "trng.h"
#include "sysctrl.h"

int get_random_number(uint32_t* p_buffer, uint32_t number) {
    /*
     * Please note this function is block mode. it will block about 4 ms ~ 6 ms
     * If you don't want the code block here, use interrupt mode.
     */
    uint32_t temp,i;
    volatile uint32_t *ptr;

    for(i=0;i<number;i++)
    {
        SYSCTRL->trng1 = 0x0; /*select von Neumann */

        /*TRNG*/
        SYSCTRL->trng0 = 1;

        while (SYSCTRL->trng2 & 0x1)
            ;

        /*Clear interrut pending*/
        SYSCTRL->trng0 = 0x2;
        /*Get random number */
        ptr = (volatile uint32_t *) p_buffer;

        *ptr++ = SYSCTRL->trng3;
    }

    return STATUS_SUCCESS;
}

