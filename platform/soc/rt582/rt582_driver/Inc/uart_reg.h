/**
 * \file            uart_register.h
 * \brief           uart register header file
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
 *
 * Author:
 */
#ifndef UART_REG_H
#define UART_REG_H

#if defined(__CC_ARM)
#pragma anon_unions
#endif

typedef struct {
    __IO uint32_t RBR;
    __IO uint32_t IER;
    __IO uint32_t FCR;
    __IO uint32_t LCR;
    __IO uint32_t MCR;
    __I uint32_t LSR;
    __I uint32_t MSR;
    __IO uint32_t SPR;

    __IO uint32_t xDMA_RX_ADDR;    //0x20
    __IO uint32_t xDMA_RX_LEN;     //0x24
    __IO uint32_t xDMA_TX_ADDR;    //0x28
    __IO uint32_t xDMA_TX_LEN;     //0x2C
    __I uint32_t xDMA_RX_RLEN;     //0x30
    __I uint32_t xDMA_TX_RLEN;     //0x34
    __IO uint32_t xDMA_IER;        //0x38
    __IO uint32_t xDMA_INT_STATUS; //0x3C
    __IO uint32_t xDMA_RX_ENABLE;  //0x40
    __IO uint32_t xDMA_TX_ENABLE;  //0x44

} uart_t;

#define THR RBR
#define IIR FCR
#define DLL RBR
#define DLM IER

#define LCR_DLAB (1 << 7)

/*LCR bit[1~0]  is character length */
#define LCR_WLEN5 0x00 /* Wordlength: 5 bits */
#define LCR_WLEN6 0x01 /* Wordlength: 6 bits */
#define LCR_WLEN7 0x02 /* Wordlength: 7 bits */
#define LCR_WLEN8 0x03 /* Wordlength: 8 bits */

#define LCR_WLEN_MASK 0x03 /*  */

#define LCR_STOP 0x04 /* Stop bits: 0=1 bit, 1=2 bits */

#define LCR_SBC    0x40 /* Set break control */
#define LCR_SPAR   0x20 /* Stick parity (?) */
#define LCR_EPAR   0x10 /* Even parity select */
#define LCR_PARITY 0x08 /* Parity Enable */

#define LCR_PARITY_MASK (LCR_SPAR | LCR_EPAR | LCR_PARITY) /* Parity Mask */

/*
 * These are the definitions for the FIFO Control Register
 */
#define FCR_FIFO_EN    0x01 /* Fifo enable */
#define FCR_CLEAR_RCVR 0x02 /* Clear the RCVR FIFO */
#define FCR_CLEAR_XMIT 0x04 /* Clear the XMIT FIFO */
#define FCR_DMA_SELECT 0x08 /* For DMA applications */

#define FCR_TRIGGER_MASK 0xC0 /* Mask for the FIFO trigger range */
#define FCR_TRIGGER_1    0x00 /* Mask for trigger set at 1 */
#define FCR_TRIGGER_4    0x40 /* Mask for trigger set at 4 */
#define FCR_TRIGGER_8    0x80 /* Mask for trigger set at 8 */
#define FCR_TRIGGER_14   0xC0 /* Mask for trigger set at 14 */

/* Clear & enable FIFOs */
#define FCR_DEFVAL (FCR_CLEAR_RCVR | FCR_CLEAR_XMIT)

/*
 * These are the definitions for the Modem Control Register
 */
#define MCR_DTR       0x01 /* DTR   */
#define MCR_RTS       0x02 /* RTS   */
#define MCR_OUT1      0x04 /* Out 1 */
#define MCR_OUT2      0x08 /* Out 2 */
#define UART_MCR_LOOP 0x10 /* Enable loopback test mode */

#define MCR_ENABLE_CTS 0x20 /**Enable CTS to block transmit*/

#define LSR_THRE 0x20 /* Transmit-hold-register empty */

#define LSR_TEMP 0x40 /* Transmitter empty*/

#define IIR_INTSTATUS 0x01 /* IIR bit0 is 1 means No interrupt pending*/

#define IIR_INTID_MSK  0x0F
#define IIR_INTID_RDA  0x04 /* IIR: Received Data Available*/
#define IIR_INTID_CTI  0x0C /* IIR: Character Timeout      */
#define IIR_INTID_RLS  0x06 /* IIR: Receiver Line Status */
#define IIR_INTID_THRE 0x02 /* IIR: Transmitter Holding Register Empty*/
#define IIR_INTID_MS   0x00 /* IIR: Modem Status*/

/*
 * These are the definitions for the Interrupt Enable Register
 */
#define UART_IER_MSI  0x08 /* Enable Modem status interrupt */
#define UART_IER_RLSI 0x04 /* Enable receiver line status interrupt */
#define UART_IER_THRI 0x02 /* Enable Transmitter holding register int. */
#define UART_IER_RDI  0x01 /* Enable receiver data interrupt */
#define UART_IER_ALL                                                           \
    UART_IER_RDI | UART_IER_THRI | UART_IER_RLSI                               \
        | UART_IER_MSI /* Enable uart all interrupt */

#define UART_IER_DMA_RX    0x81
#define UART_IER_DMA_TX    0x82
#define UART_IER_DISABLE   0
#define UART_IER_MODE_MASK 0x03
#define UART_IER_MODE_CHK  0x80

#define UART_LSR_FIFOE 0x80 /* Fifo error */
#define UART_LSR_TEMT  0x40 /* Transmitter empty */
#define UART_LSR_THRE  0x20 /* Transmit-hold-register empty */
#define UART_LSR_BI    0x10 /* Break interrupt indicator */
#define UART_LSR_FE    0x08 /* Frame error indicator */
#define UART_LSR_PE    0x04 /* Parity error indicator */
#define UART_LSR_OE    0x02 /* Overrun error indicator */
#define UART_LSR_DR    0x01 /* Receiver data ready */

#define UART_LSR_BRK_ERROR_BITS 0x1E /* BI, FE, PE, OE bits */

#define UART_MSR_CTS  0x10 /*Modem Status Register CTS state*/
#define UART_MSR_DCTS 0x01 /*Modem Status : Delta Clear To Send */

#define xDMA_IER_RX 0x01 /*Interrrupt Enable for xDMA_RX*/
#define xDMA_IER_TX 0x02 /*Interrrupt Enable for xDMA_TX*/

#define xDMA_ISR_RX xDMA_IER_RX
#define xDMA_ISR_TX xDMA_IER_TX

#define xDMA_Enable 0x01 /*Enable xDMA*/
#define xDMA_Stop   0x00 /*Disable/Clear xDMA*/

#if defined(__CC_ARM)
#pragma no_anon_unions
#endif

#endif
