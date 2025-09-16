/**
 * \file            hosal_sysctrl.h
 * \brief           Hosal system control driver header file
 *          
 */
/*
 * Copyright (c) year FirstName LASTNAME
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

#ifndef HOSAL_SYSCTRL_H
#define HOSAL_SYSCTRL_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           Output pin mode 
 */
#define HOSAL_MODE_GPIO               MODE_GPIO
#define HOSAL_MODE_UART0_TX           MODE_UART
#define HOSAL_MODE_UART0_RX           MODE_UART
#define HOSAL_MODE_UART1_TX           MODE_UART
#define HOSAL_MODE_UART1_RX           MODE_UART
#define HOSAL_MODE_UART1_RTSN         MODE_UART
#define HOSAL_MODE_UART1_CTSN         MODE_UART
#define HOSAL_MODE_UART2_TX           MODE_UART
#define HOSAL_MODE_UART2_RX           MODE_UART
#define HOSAL_MODE_UART2_RTSN         MODE_UART
#define HOSAL_MODE_UART2_CTSN         MODE_UART
#define HOSAL_MODE_PWM0               MODE_PWM0
#define HOSAL_MODE_PWM1               MODE_PWM1
#define HOSAL_MODE_PWM2               MODE_PWM2
#define HOSAL_MODE_PWM3               MODE_PWM3
#define HOSAL_MODE_PWM4               MODE_PWM4
#define HOSAL_MODE_I2CM0_SCL          MODE_I2C
#define HOSAL_MODE_I2CM0_SDA          MODE_I2C
#define HOSAL_MODE_SPI1_MASTER_SCLK   MODE_QSPI0
#define HOSAL_MODE_SPI1_MASTER_CSN0   MODE_QSPI0
#define HOSAL_MODE_SPI1_MASTER_MOSI   MODE_QSPI0
#define HOSAL_MODE_SPI1_MASTER_MISO   MODE_QSPI0
#define HOSAL_MODE_SPI1_SLAVE_SCLK    MODE_QSPI0
#define HOSAL_MODE_SPI1_SLAVE_CSN0    MODE_QSPI0
#define HOSAL_MODE_SPI1_SLAVE_MOSI    MODE_QSPI0
#define HOSAL_MODE_SPI1_SLAVE_MISO    MODE_QSPI0
#define HOSAL_MODE_SPI0_MASTER_SDATA0 MODE_QSPI0
#define HOSAL_MODE_SPI0_MASTER_SDATA1 MODE_QSPI0
#define HOSAL_MODE_SPI0_MASTER_SDATA2 MODE_QSPI0
#define HOSAL_MODE_SPI0_MASTER_SDATA3 MODE_QSPI0
#define HOSAL_MODE_SPI1_MASTER_SDATA0 MODE_QSPI0
#define HOSAL_MODE_SPI1_MASTER_SDATA1 MODE_QSPI0
#define HOSAL_MODE_SPI1_MASTER_SDATA2 MODE_QSPI0
#define HOSAL_MODE_SPI1_MASTER_SDATA3 MODE_QSPI0
#define HOSAL_MODE_SPI0_MASTER_CSN1   MODE_QSPI0_CSN1
#define HOSAL_MODE_SPI0_MASTER_CSN2   MODE_QSPI0_CSN2
#define HOSAL_MODE_SPI0_MASTER_CSN3   MODE_QSPI0_CSN3
#define HOSAL_MODE_SPI0_SLAVE_CSN1    MODE_QSPI0_CSN1
#define HOSAL_MODE_SPI0_SLAVE_CSN2    MODE_QSPI0_CSN2
#define HOSAL_MODE_SPI0_SLAVE_CSN3    MODE_QSPI0_CSN3
#define HOSAL_MODE_SPI1_MASTER_CSN1   MODE_QSPI0_CSN1
#define HOSAL_MODE_SPI1_MASTER_CSN2   MODE_QSPI0_CSN2
#define HOSAL_MODE_SPI1_MASTER_CSN3   MODE_QSPI0_CSN3
#define HOSAL_MODE_SPI1_SLAVE_CSN1    MODE_QSPI0_CSN1
#define HOSAL_MODE_SPI1_SLAVE_CSN2    MODE_QSPI0_CSN2
#define HOSAL_MODE_SPI1_SLAVE_CSN3    MODE_QSPI0_CSN3
#define HOSAL_MODE_I2S_BCK            MODE_I2S
#define HOSAL_MODE_I2S_WCK            MODE_I2S
#define HOSAL_MODE_I2S_SDO            MODE_I2S
#define HOSAL_MODE_I2S_SDI            MODE_I2S
#define HOSAL_MODE_I2S_MCLK           MODE_I2S

/**
 * \brief           Gpio pull up define
 */
#define HOSAL_PULL_NONE      PULL_NONE
#define HOSAL_PULL_DOWN_10K  PULLDOWN_10K
#define HOSAL_PULL_DOWN_100K PULLDOWN_100K
#define HOSAL_PULL_DOWN_1M   PULLDOWN_1M
#define HOSAL_PULL_UP_10K    PULLUP_10K
#define HOSAL_PULL_UP_100K   PULLUP_100K
#define HOSAL_PULL_UP_1M     PULLUP_1M

/**
 * \brief           hosal_delay_us
 * \param[in]       us: delay times    
 */
void hosal_delay_us(unsigned int us);
/**
 * \brief           hosal_delay_ms
 * \param[in]       ms: delay times      
 */
void hosal_delay_ms(unsigned int ms);
/**
 * \brief           Get pin function mode
 * \param[in]       pin_number: Specifies the pin number
 * \return          The pin function mode
 */
uint32_t hosal_pin_get_mode(uint32_t pin_number);

/**
 * \brief           Set pin function mode
 * \param[in]       pin_number: Specifies the pin number
 * \param[in]       mode: The specail function mode for the pin_number
 *                        Config GPIO To --> UART/I2S/PWM/SADC/I2C/SPI
 */
void hosal_pin_set_mode(uint32_t pin_number, uint32_t mode);

/**
 * \brief           Set pin pull option
 * \param[in]       pin_number: Specifies the pin number
 * \param[in]       mode: The specail pull option for the pin_number
 *                        PULL_NONE        0
 *                        PULL_DOWN_10K    1
 *                        PULL_DOWN_100K   2
 *                        PULL_DOWN_1M     3
 *                        PULL_UP_10K      5
 *                        PULL_UP_100K     6
 *                        PULL_UP_1M       7
 */
void hosal_pin_set_pullopt(uint32_t pin_number, uint32_t mode);

/**
 * \brief           Set pin to opendrain option
 * \param[in]       pin_number: Specifies the pin number
 */
void hosal_enable_pin_opendrain(uint32_t pin_number);

/**
 * \brief           Disable pin to opendrain option
 * \param[in]       pin_number: Specifies the pin number
 */
void hosal_disable_pin_opendrain(uint32_t pin_number);

/**
 * \brief           hosal_config_peripherl_clock
 * \param[in]       per_clk: Specifies peripheral clock
 * \param[in]       cfg_para: disable/enable peripheral clock
 */
void hosal_config_peripherl_clock(uint32_t per_clk, void* cfg_para);

/**
 * \brief           hosal_get_rco_clock_tick
 * \param[in]       
 * \param[in]       
 */
int hosal_get_rco_clock_tick(uint32_t* rco_tick);
#ifdef __cplusplus
}
#endif

#endif /* End of HOSAL_SYSCTRL_H */
