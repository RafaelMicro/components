/**
 * \file            hosal_uart.c
 * \brief           Hosal uart driver file
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
 * Author:          Kc.tseng
 */

#include <stdint.h>
#include "hosal_uart.h"
#include "lpm.h"
#include "mcu.h"
#include "stdio.h"

#define MAX_NUMBER_OF_UART 3
#define UART0_BASE_CLK     16

#define UART_ReadLineStatus(pReg) ((pReg)->LSR)

typedef struct {
    uart_t* uart;      /*based hardware address*/
    IRQn_Type irq_num; // UART IRQ Number
    hosal_uart_callback_t rx_cb;
    void* rx_cb_arg;
    hosal_uart_callback_t tx_cb;
    void* tx_cb_arg;
    hosal_uart_callback_t rxdma_cb;
    void* rxdma_cb_arg;
    hosal_uart_callback_t txdma_cb;
    void* txdma_cb_arg;
    hosal_uart_callback_t rx_line_status_cb;
    void* rx_line_status_cb_arg;
    hosal_uart_callback_t mode_cb;
    void* mode_cb_arg;   
} uart_handle_t;

static uart_handle_t g_uart_handle[MAX_NUMBER_OF_UART] = {
    {.uart = UART0, .irq_num = Uart0_IRQn},
    {.uart = UART1, .irq_num = Uart1_IRQn},
    {.uart = UART2, .irq_num = Uart2_IRQn},
};

int hosal_uart_finalize(hosal_uart_dev_t* uart_dev) {
    int rval = 0;
    hosal_uart_config_t* cfg = &uart_dev->config;
    uart_t* uart;
    uart = g_uart_handle[cfg->uart_id].uart;

    NVIC_DisableIRQ(g_uart_handle[cfg->uart_id].irq_num);

    uart->xDMA_IER = 0; /*disable xDMA interrupt*/

    uart->xDMA_RX_ENABLE = xDMA_Stop;
    uart->xDMA_TX_ENABLE = xDMA_Stop;

    uart->xDMA_INT_STATUS = xDMA_ISR_RX | xDMA_ISR_TX; /*write 1 to clear*/

    /*reset uart FIFO*/
    uart->FCR = 0;
    uart->FCR = FCR_CLEAR_XMIT | FCR_CLEAR_RCVR;

    // Disable UART peripheral clock
    disable_perclk((UART0_BASE_CLK + cfg->uart_id));

    // Clear pending UART interrupts in NVIC
    NVIC_ClearPendingIRQ(g_uart_handle[cfg->uart_id].irq_num);
    return rval;
}

int hosal_uart_init(hosal_uart_dev_t* uart_dev) {
    hosal_uart_config_t* cfg = &uart_dev->config;
    uart_t* uart;
    uint32_t cval;

    uart = g_uart_handle[cfg->uart_id].uart;
    pin_set_mode(cfg->rx_pin, MODE_UART); /*GPIO16 as UART0 RX*/
    pin_set_mode(cfg->tx_pin, MODE_UART); /*GPIO17 as UART0 TX*/

    if((cfg->flow_control==UART_HWFC_ENABLED) && (cfg->uart_id==HOSAL_UART1_ID))
    {
      pin_set_mode(cfg->rts_pin, MODE_UART); /*GPIO20/GPIO20 as UART1 RTS*/
      pin_set_mode(cfg->cts_pin, MODE_UART); /*GPIO21/GPIO21 as UART1 CTS*/  
    }


    NVIC_DisableIRQ(g_uart_handle[cfg->uart_id].irq_num);
    NVIC_SetPriority(g_uart_handle[cfg->uart_id].irq_num, 4);
    // Clear UART IRQ
    NVIC_ClearPendingIRQ(g_uart_handle[cfg->uart_id].irq_num);

    // Enable UART peripheral clock
    enable_perclk((UART0_BASE_CLK + cfg->uart_id));

    /*clear FIFO, REMAKR: FCR is write-only*/
    uart->FCR = 0;
    uart->FCR = FCR_DEFVAL; /*reset FIFO*/
    // Disable interrupts
    uart->IER = 0;
    /*bits mode only use two bits.*/
    cval = cfg->data_width & 0x03;
    /*set baudrate*/
    uart->LCR = (LCR_DLAB | cval);
    /*set baudrate*/
    uart->DLL = cfg->baud_rate & 0xFF;
    uart->DLM = cfg->baud_rate >> 8;
    uart->LCR = (cval);

    /*set stop bits*/
    if (cfg->stop_bits == UART_STOPBIT_TWO)
        cval |= LCR_STOP;
    /*set parity*/
    if (cfg->parity & PARENB)
        cval |= LCR_PARITY;
    if (!(cfg->parity & PARODD))
        cval |= LCR_EPAR;
    if (cfg->parity & CMSPAR)
        cval |= LCR_SPAR;

    uart->LCR = cval;

    uart->MCR = 0; /*Initial default modem control register.*/
    uart->FCR = (FCR_TRIGGER_8 | FCR_CLEAR_RCVR | FCR_CLEAR_XMIT | FCR_FIFO_EN);
    /*init native DMA architecture setting*/
    uart->xDMA_IER = 0; /*disable xDMA interrupt*/
    uart->xDMA_RX_ENABLE = xDMA_Stop;
    uart->xDMA_TX_ENABLE = xDMA_Stop;
    uart->xDMA_TX_LEN = 0;
    uart->xDMA_RX_LEN = 0;
    uart->xDMA_INT_STATUS = xDMA_ISR_RX | xDMA_ISR_TX; /*write 1 to clear*/
    delay_us(50);
    uart->FCR = (FCR_TRIGGER_8 | FCR_CLEAR_RCVR | FCR_CLEAR_XMIT | FCR_FIFO_EN);
    return (uart->RBR & 0xFF);
}

int hosal_uart_send(hosal_uart_dev_t* uart_dev, const void* data,
                    uint32_t size) {
    uint32_t i = 0;
    hosal_uart_config_t* cfg = &uart_dev->config;
    uart_t* uart;
    uart = g_uart_handle[cfg->uart_id].uart;
    while (i < size) {
        while ((UART_ReadLineStatus(uart) & UART_LSR_THRE) == 0) {}
        uart->THR = ((uint8_t*)data)[i];
        i++;
    }

    return i;
}

void hosal_uart_send_complete(hosal_uart_dev_t* uart_dev) {
    hosal_uart_config_t* cfg = &uart_dev->config;
    uart_t* uart;
    uart = g_uart_handle[cfg->uart_id].uart;

    while ((UART_ReadLineStatus(uart) & UART_LSR_TEMT) == 0) {}
}

inline int hosal_uart_receive(hosal_uart_dev_t* uart_dev, void* data,
                              uint32_t expect_size) {
    uint32_t counter = 0;
    hosal_uart_config_t* cfg = &uart_dev->config;

    uart_t* uart;
    uart = g_uart_handle[cfg->uart_id].uart;

    while (counter < expect_size) {
        if (uart->LSR & UART_LSR_DR)
            ((uint8_t*)data)[counter] = uart->RBR & 0xFF;
        else
            break;
        counter++;
    }

    return counter;
}

static inline void set_config_value(void* config_field, void* p_arg) {
    *(uint32_t*)config_field = (uint32_t)p_arg;
}

static inline void get_config_value(void* config_field, void* p_arg) {
    if (p_arg)
        *(uint32_t*)p_arg = *(uint32_t*)config_field;
}

inline uint32_t hosal_uart_get_lsr(hosal_uart_dev_t* uart_dev) {
    uint32_t status = 0;
    uart_t* uart = g_uart_handle[uart_dev->config.uart_id].uart;

    status = uart->LSR;
    return status;
}

uint32_t hosal_uart_get_dma_int_status(hosal_uart_dev_t* uart_dev) {
    uint32_t status = 0;
    uart_t* uart = g_uart_handle[uart_dev->config.uart_id].uart;

    status = uart->xDMA_INT_STATUS;
    return status;
}

int hosal_uart_ioctl(hosal_uart_dev_t* uart_dev, int ctl, void* p_arg) {
    hosal_uart_dma_cfg_t* dma_cfg;
    uart_t* uart = g_uart_handle[uart_dev->config.uart_id].uart;
    uint32_t tmp = 0;

    switch (ctl) {
        case HOSAL_UART_BAUD_SET:
            set_config_value(&uart_dev->config.baud_rate, p_arg);
            break;
        case HOSAL_UART_BAUD_GET:
            get_config_value(&uart_dev->config.baud_rate, p_arg);
            break;
        case HOSAL_UART_DATA_WIDTH_SET:
            set_config_value(&uart_dev->config.data_width, p_arg);
            break;
        case HOSAL_UART_DATA_WIDTH_GET:
            get_config_value(&uart_dev->config.data_width, p_arg);
            break;
        case HOSAL_UART_STOP_BITS_SET:
            set_config_value(&uart_dev->config.stop_bits, p_arg);
            break;
        case HOSAL_UART_STOP_BITS_GET:
            get_config_value(&uart_dev->config.stop_bits, p_arg);
            break;
        case HOSAL_UART_FLOWMODE_SET:
            set_config_value(&uart_dev->config.flow_control, p_arg);
            if (p_arg) {
                uart->MCR = MCR_ENABLE_CTS;
                uart->IER |= UART_IER_MSI;
            } else {
                uart->MCR = 0;
                uart->IER &= ~(UART_IER_MSI);
            }
            break;
        case HOSAL_UART_FLOWSTAT_GET:
            get_config_value(&uart_dev->config.flow_control, p_arg);
            break;
        case HOSAL_UART_PARITY_SET:
            set_config_value(&uart_dev->config.parity, p_arg);
            break;
        case HOSAL_UART_PARITY_GET:
            get_config_value(&uart_dev->config.parity, p_arg);
            break;
        case HOSAL_UART_RECEIVE_LINE_STATUS_ENABLE:
            NVIC_DisableIRQ(g_uart_handle[uart_dev->config.uart_id].irq_num);
            NVIC_ClearPendingIRQ(
                g_uart_handle[uart_dev->config.uart_id].irq_num);
            uart->IER |= UART_IER_RLSI;
            NVIC_EnableIRQ(g_uart_handle[uart_dev->config.uart_id].irq_num);
            break;
        case HOSAL_UART_MODE_SET:
            uart->IER = 0;
            NVIC_ClearPendingIRQ(
                g_uart_handle[uart_dev->config.uart_id].irq_num);
            uart_dev->config.mode = (hosal_uart_mode_t)p_arg;

            switch (uart_dev->config.mode) {
                case HOSAL_UART_MODE_POLL: uart->IER = 0; uart->xDMA_IER=0; break;
                case HOSAL_UART_MODE_INT_TX:
                    uart->IER |= UART_IER_THRI;
                    NVIC_EnableIRQ(
                        g_uart_handle[uart_dev->config.uart_id].irq_num);
                    break;
                case HOSAL_UART_MODE_INT_RX:
                    uart->IER |= UART_IER_RDI;
                    NVIC_EnableIRQ(
                        g_uart_handle[uart_dev->config.uart_id].irq_num);
                    break;
                case HOSAL_UART_MODE_INT:
                    uart->IER |= (UART_IER_RDI | UART_IER_THRI);
                    NVIC_EnableIRQ(
                        g_uart_handle[uart_dev->config.uart_id].irq_num);
                    break;
                case HOSAL_UART_DMA_MODE_INT_TX:
                    uart->xDMA_IER |= (xDMA_IER_TX );
                    NVIC_EnableIRQ(
                        g_uart_handle[uart_dev->config.uart_id].irq_num);
                    break;
                case HOSAL_UART_DMA_MODE_INT_RX:
                   uart->xDMA_IER |= (xDMA_IER_RX);
                    NVIC_EnableIRQ(
                        g_uart_handle[uart_dev->config.uart_id].irq_num);
                    break;

                case HOSAL_UART_DMA_MODE_INT:
                    uart->xDMA_IER |= (xDMA_IER_TX | xDMA_IER_RX);
                    NVIC_EnableIRQ(
                        g_uart_handle[uart_dev->config.uart_id].irq_num);
                    break; 
                case HOSAL_UART_DMA_MODE_POLL:
                    uart->xDMA_IER = (xDMA_IER_TX | xDMA_IER_RX);
                     NVIC_DisableIRQ(
                        g_uart_handle[uart_dev->config.uart_id].irq_num);   
                    break;               
            }
            break;
        case HOSAL_UART_MODE_GET:
            get_config_value(&uart_dev->config.mode, p_arg);
            break;
        case HOSAL_UART_TX_TRIGGER_ON:
        case HOSAL_UART_TX_TRIGGER_OFF: break;
        case HOSAL_UART_DMA_TX_START:
            dma_cfg = (hosal_uart_dma_cfg_t*)p_arg;
            uart->xDMA_TX_ADDR = (uint32_t)dma_cfg->dma_buf;
            uart->xDMA_TX_LEN = dma_cfg->dma_buf_size;
            uart->xDMA_IER |= xDMA_IER_TX;
            uart->xDMA_TX_ENABLE = xDMA_Enable;
            break;
        case HOSAL_UART_DMA_RX_START: 
            dma_cfg = (hosal_uart_dma_cfg_t*)p_arg;
            uart->xDMA_RX_ADDR = (uint32_t)dma_cfg->dma_buf;
            uart->xDMA_RX_LEN = dma_cfg->dma_buf_size;
            uart->xDMA_IER |= xDMA_IER_RX;
            uart->xDMA_RX_ENABLE = xDMA_Enable;        
            break;
        case HOSAL_UART_DMA_POL_TX_START:
            uart->xDMA_TX_ENABLE = xDMA_Stop;
            dma_cfg = (hosal_uart_dma_cfg_t*)p_arg;
            uart->xDMA_TX_ADDR = (uint32_t)dma_cfg->dma_buf;
            uart->xDMA_TX_LEN = dma_cfg->dma_buf_size;
            uart->xDMA_TX_ENABLE = xDMA_Enable;
            break;
        case HOSAL_UART_DMA_POL_RX_START: 
            uart->xDMA_RX_ENABLE = xDMA_Stop; 
            dma_cfg = (hosal_uart_dma_cfg_t*)p_arg;
            uart->xDMA_RX_ADDR = (uint32_t)dma_cfg->dma_buf;
            uart->xDMA_RX_LEN = dma_cfg->dma_buf_size;
            uart->xDMA_RX_ENABLE = xDMA_Enable;        
            break;            
        case HOSAL_UART_DISABLE_INTERRUPT:
            NVIC_DisableIRQ(g_uart_handle[uart_dev->config.uart_id].irq_num);
            break;
        case HOSAL_UART_ENABLE_INTERRUPT:
            NVIC_EnableIRQ(g_uart_handle[uart_dev->config.uart_id].irq_num);
            break;
        case HOSAL_UART_CLEAR_FIFO:
            tmp = uart->IER;
            uart->IER = 0;
            uart->FCR = 0;
            uart->FCR = FCR_DEFVAL; /*reset FIFO*/
            uart->IER = tmp;
            break;
        case HOSAL_UART_MODEM_RTS_SET:
           if (p_arg) {
                uart->MCR |= MCR_RTS;
            }else {
                uart->MCR &= ~MCR_RTS;    
            }
            break;  
        case HOSAL_UART_CLEAR_DMA_STATUS:
             uart->xDMA_INT_STATUS = (uint32_t)p_arg; 
             break;
        case HOSAL_UART_SET_BREAK:

           if (p_arg) {
                uart->LCR |= LCR_SBC;
            } else {
               uart->LCR &=~ LCR_SBC;
            }
            break;
        default: break;
    }
    return 0;
}

static inline void set_callback(hosal_uart_callback_t* dev_cb, void** dev_arg,
                                hosal_uart_callback_t pfn_callback, void* arg,
                                hosal_uart_callback_t* handle_cb,
                                void** handle_arg) {
    *dev_cb = pfn_callback;
    *dev_arg = arg;
    *handle_cb = pfn_callback;
    *handle_arg = arg;
}

int hosal_uart_callback_set(hosal_uart_dev_t* uart_dev, int callback_type,
                            hosal_uart_callback_t pfn_callback, void* arg) {
    hosal_uart_config_t* cfg = &uart_dev->config;

    switch (callback_type) {
        case HOSAL_UART_TX_CALLBACK:
            set_callback(&uart_dev->tx_cb, &uart_dev->p_tx_arg, pfn_callback,
                         arg, &g_uart_handle[cfg->uart_id].tx_cb,
                         &g_uart_handle[cfg->uart_id].tx_cb_arg);
            break;
        case HOSAL_UART_RX_CALLBACK:
            set_callback(&uart_dev->rx_cb, &uart_dev->p_rx_arg, pfn_callback,
                         arg, &g_uart_handle[cfg->uart_id].rx_cb,
                         &g_uart_handle[cfg->uart_id].rx_cb_arg);
            break;
        case HOSAL_UART_TX_DMA_CALLBACK:
            set_callback(&uart_dev->txdma_cb, &uart_dev->p_txdma_arg,
                         pfn_callback, arg,
                         &g_uart_handle[cfg->uart_id].txdma_cb,
                         &g_uart_handle[cfg->uart_id].txdma_cb_arg);
            break;
        case HOSAL_UART_RX_DMA_CALLBACK:
            set_callback(&uart_dev->rxdma_cb, &uart_dev->p_rxdma_arg,
                         pfn_callback, arg,
                         &g_uart_handle[cfg->uart_id].rxdma_cb,
                         &g_uart_handle[cfg->uart_id].rxdma_cb_arg);
            break;
        case HOSAL_UART_RECEIVE_LINE_STATUS_CALLBACK:
            set_callback(&uart_dev->rx_line_status_cb,
                         &uart_dev->p_rx_line_status_arg, pfn_callback, arg,
                         &g_uart_handle[cfg->uart_id].rx_line_status_cb,
                         &g_uart_handle[cfg->uart_id].rx_line_status_cb_arg);
            break;
        case HOSAL_UART_MODE_CALLBACK:
            set_callback(&uart_dev->mode_cb,
                         &uart_dev->p_mode_arg, pfn_callback, arg,
                         &g_uart_handle[cfg->uart_id].mode_cb,
                         &g_uart_handle[cfg->uart_id].mode_cb_arg);
            break;            
        default: return -1;
    }
    return 0;
}

typedef int (*hosal_uart_callback_t)(void*);

static inline void handle_callback(hosal_uart_callback_t cb, void* cb_arg) {
    if (cb != NULL)
        cb(cb_arg);
}

static inline void __uart_generic_notify_handler(uint8_t id) {
    uart_t* uart = g_uart_handle[id].uart;
    uint32_t iir = uart->IIR & IIR_INTID_MSK;
    uint32_t value;

    if (iir == IIR_INTID_RLS) {
        handle_callback(g_uart_handle[id].rx_line_status_cb,
                        g_uart_handle[id].rx_line_status_cb_arg);
    }

    if ((iir == IIR_INTID_RDA || iir == IIR_INTID_CTI)
        && (uart->LSR & UART_LSR_DR))
        handle_callback(g_uart_handle[id].rx_cb, g_uart_handle[id].rx_cb_arg);

    if (iir == IIR_INTID_THRE && (uart->LSR & UART_LSR_THRE))
        handle_callback(g_uart_handle[id].tx_cb, g_uart_handle[id].tx_cb_arg);

    if ((uart->xDMA_INT_STATUS & xDMA_ISR_TX) == xDMA_ISR_TX) {
        uart->xDMA_INT_STATUS = xDMA_ISR_TX;
        uart->xDMA_TX_ENABLE = xDMA_Stop;
        handle_callback(g_uart_handle[id].txdma_cb,
                        g_uart_handle[id].txdma_cb_arg);
    }

    if ((uart->xDMA_INT_STATUS & xDMA_ISR_RX) == xDMA_ISR_RX) {
        uart->xDMA_INT_STATUS = xDMA_ISR_RX;
        uart->xDMA_RX_ENABLE = xDMA_Stop;
        handle_callback(g_uart_handle[id].rxdma_cb,
                        g_uart_handle[id].rxdma_cb_arg);
    }

    if (iir == IIR_INTID_MS) {

            value = uart->MSR;

          if((value & UART_MSR_DCTS)) {

            handle_callback(g_uart_handle[id].mode_cb, g_uart_handle[id].mode_cb_arg);

          }
    }

}

__WEAK void uart0_handler(void) {
    __uart_generic_notify_handler(0);
    NVIC_ClearPendingIRQ(Uart0_IRQn);
}

__WEAK void uart1_handler(void) {
    __uart_generic_notify_handler(1);
    NVIC_ClearPendingIRQ(Uart1_IRQn);
}

__WEAK void uart2_handler(void) {
    __uart_generic_notify_handler(2);
    NVIC_ClearPendingIRQ(Uart2_IRQn);
}
