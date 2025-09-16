/**
 * \file            uart_retarget.c
 * \brief           uart retarget driver file
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
#include "stdio.h"

#include "mcu.h"

#include "uart_drv.h"
#include "uart_retarget.h"

#define UART_ReadLineStatus(pReg) ((pReg)->LSR)


typedef struct {
    uart_t* uart; /*based hardware address*/
} uart_handle_t;

static uint32_t sUartId;
static cb_stdin_str_t pf_stdin_str;

static uart_handle_t sUartHandle[3] = {{UART0}, {UART1}, {UART2}};


int uart_retarget_init(uart_retarget_desc_t* pt_retarget_desc) {
    int ret = 0;
    do {
        sUartId = pt_retarget_desc->uart_id;
        pf_stdin_str = pt_retarget_desc->pf_stdin_str;

    } while (0);
    return ret;
}

int retarget_stdout_string(char* str, int length, uart_t* p_csr) {
    while (length) {
        while ((UART_ReadLineStatus(p_csr) & UART_LSR_THRE) == 0)
            ;

        p_csr->THR = *str++;
        length--;
    }
    return length;
}

int retarget_stdout_char(int ch, uart_t* p_csr) {
    while ((UART_ReadLineStatus(p_csr) & UART_LSR_THRE) == 0)
        ;

    p_csr->THR = ch;

    return ch;
}

int uart_retarget_stdout_string(char* str, int length) {
    return retarget_stdout_string(str, length, sUartHandle[sUartId].uart);
}

int uart_retarget_stdout_char(int ch) {
    return retarget_stdout_char(ch, sUartHandle[sUartId].uart);
}
#if defined(__CC_ARM) || defined(__CLANG_ARM)
int fputc(int ch, FILE* p_file) {
    if (ch == 0x0a) {
        uart_retarget_stdout_char(0x0d);
    }
    uart_retarget_stdout_char(ch);
    return ch;
}

int fgetc(FILE* p_file) {
    char pBuf;

    if (pf_stdin_str) {
        pf_stdin_str((char*)&pBuf, 1);
    }

    return pBuf;
}
#elif defined(__GNUC__)

int _write(int fd, char* ptr, int len) {
    int i;
    for (i = 0; i < len; i++) {
        if (ptr[i] == 0x0a) {
            uart_retarget_stdout_char(0x0d);
        }
        uart_retarget_stdout_char(ptr[i]);
    }

    return len;
}

int _read(int fd, char* ptr, int len) {
    char pBuf;

    if (pf_stdin_str) {
        pf_stdin_str((char*)&pBuf, 1);
    }

    return 1;
}

#endif
