/**
 * \file            retarget.h
 * \brief           retarget retarget driver header file
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
#ifndef ___RETARGET_H__
#define ___RETARGET_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "uart_drv.h"

/**
 *  \brief Initialize debug console
 *  This function configures and enable the debug console (UART0)
 *  So user appplication can call some stdout function like, printf(...) or getchar()
 *  for uart0
 *
 *  The uart0  will be configured as 8bit mode, NONE parity, and baudrate is set by
 *  the first parameter of this function.
 *
 *  Please Note: baudrate is defined in uart_drv.h!
 *  (If you want to set the baudrate to 115200, baudrate should be use the define "UART_BAUDRATE_115200", not 115200)
 *
 *  \param[in] baudrate       identifier for uart0 baudrate
 *
 *  \return
 *  \retval   STATUS_SUCCESS on success, or  error.
*/
uint32_t console_drv_init(uart_baudrate_t baudrate);

/**
 *  \brief check uart0 rx buffer is empty or not
 *  Call this function to check if there is any data in rx buffer
 *
 *  Please notice this function is designed to check uart0 RX buffer.
 *  If only reflects "the current data" in uart0 rx buffer when called this function.
 *  But if there are multiple tasks reading the RX buffer "at the same time", it is
 *  possible that when task to read RX buffer, there is empty in RX buffer.
 *
 *  \param     NONE
 *
 *  \retval   return the number character in uart0 rx buffer.
*/

uint32_t check_uart0_rx_buffer_data_num(void);

/**
 *  \brief terminate console output message if system want to enter sleep mode
 *
 *  Call this function to terminate the output message if there are data in output queue.
 *  Any message in output queue will be clear.
 *  Please call this function before system to enter sleep mode or waiting all message outputed.
 *
 *  \param      NONE
 *
 *  \retval     NONE.
*/

void console_sleep(void);


#ifdef __cplusplus
}
#endif

#endif
