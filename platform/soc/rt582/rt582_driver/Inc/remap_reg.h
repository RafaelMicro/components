/**
 * \file            remap_reg.h
 * \brief           Remap register definition header file
 */
/*
 * Copyright (c) 2024 Rafal Micro
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
#ifndef REMAP_REG_H
#define REMAP_REG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct {
    __IO uint32_t RESERVED1;                    /*!< 0x00 */
    __IO uint32_t RESERVED2;                    /*!< 0x04 */
    __IO uint32_t RESERVED3;                    /*!< 0x08 */
    __IO uint32_t RESERVED4;                    /*!< 0x0C */
    __IO uint32_t sw_irq_set;                   /*!< 0x10 */
    __IO uint32_t sw_irq_clr;                   /*!< 0x14 */
    __IO uint32_t sw_irq_en_set;                /*!< 0x18 */
    __IO uint32_t sw_irq_en_clr;                /*!< 0x1C */
} remap_t;

#ifdef __cplusplus
}
#endif

#endif /* End of GPIO_H */
