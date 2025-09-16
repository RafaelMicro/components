/**
 * \file            hosal_gpio.h
 * \brief           Hosal GPIO driver header file
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
 * Author:          Kc.tseng
 */

#ifndef HOSAL_GPIO_H
#define HOSAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           Selecting the pin to sense high or low level, edge for pin input.
 */
/*!< GPIO Interrupt mode disable */
#define HOSAL_GPIO_PIN_NOINT            GPIO_PIN_NOINT
/*!< GPIO Interrupt enable for Level-Low */
#define HOSAL_GPIO_PIN_INT_LEVEL_LOW    GPIO_PIN_INT_LEVEL_LOW
/*!< GPIO Interrupt enable for Level-High */
#define HOSAL_GPIO_PIN_INT_LEVEL_HIGH   GPIO_PIN_INT_LEVEL_HIGH
/*!< GPIO Interrupt enable for Rising Edge */
#define HOSAL_GPIO_PIN_INT_EDGE_RISING  GPIO_PIN_INT_EDGE_RISING
/*!< GPIO Interrupt enable for Falling Edge */
#define HOSAL_GPIO_PIN_INT_EDGE_FALLING GPIO_PIN_INT_EDGE_FALLING
/*!< GPIO Interrupt enable for both Rising and Falling Edge */
#define HOSAL_GPIO_PIN_INT_BOTH_EDGE    GPIO_PIN_INT_BOTH_EDGE

/**
 * \brief           Input configuration structure
 */
typedef struct {
    void* usr_cb;
    void* param;
    uint32_t pin_int_mode;
} hosal_gpio_input_config_t;

/**
 * \brief           Set gpio pin to output mode
 * \param[in]       pin_number: specifies the pin number
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM
 */
uint32_t hosal_gpio_cfg_output(uint32_t pin_number);

/**
 * \brief           Set gpio pin to input mode
 * \param[in]       pin_number: specifies the pin number
 * \param[in]       int_mode: specifies the pin number interrupt if this pin
 *                            need to be gpio interrupt source
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM
 */
uint32_t hosal_gpio_cfg_input(uint32_t pin_number,
                          hosal_gpio_input_config_t input_cfg);

/**
 * \brief           Set gpio pin output high
 * \param[in]       pin_number: specifies the pin number
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM
 */
uint32_t hosal_gpio_pin_set(uint32_t pin_number);

/**
 * \brief           Set gpio pin output low
 * \param[in]       pin_number: specifies the pin number
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM
 */
uint32_t hosal_gpio_pin_clear(uint32_t pin_number);

/**
 * \brief           Set gpio pin output value
 * \param[in]       pin_number: specifies the pin number
 * \param[in]       value: value 0 for output low, value 1 for output high
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM
 */
uint32_t hosal_gpio_pin_write(uint32_t pin_number, uint32_t value);

/**
 * \brief           Toggle gpio pin output value
 * \param[in]       pin_number: specifies the pin number
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM
 */
uint32_t hosal_gpio_pin_toggle(uint32_t pin_number);

/**
 * \brief           Get gpio pin input value
 * \param[in]       pin_number: specifies the pin number
 * \param[out]      value: the pointer to get gpio input value
 *                  pin input value,0 is low level, 1 is high level
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM
 */
uint32_t hosal_gpio_pin_get(uint32_t pin_number, uint32_t* value);

/**
 * \brief           Enable gpio pin interrupt
 * \param[in]       pin_number: specifies the pin number that enable interrupt
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM
 */
uint32_t hosal_gpio_int_enable(uint32_t pin_number);

/**
 * \brief           Disable gpio pin interrupt
 * \param[in]       pin_number: specifies the pin number that disable interrupt
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM
 */
uint32_t hosal_gpio_int_disable(uint32_t pin_number);

/**
 * \brief           Enable gpio pin debounce function
 * \param[in]       pin_number: specifies the pin number that enable debounce
 *                              when interrupt happened
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM
 */
uint32_t hosal_gpio_debounce_enable(uint32_t pin_number);

/**
 * \brief           Disable gpio pin debounce function
 * \param[in]       pin_number: specifies the pin number that disable debounce
 *                              when interrupt happened
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM
 */
uint32_t hosal_gpio_debounce_disable(uint32_t pin_number);

/**
 * \brief           Set GPIO debounce time
 * \param[in]       mode: Specifies the sampling clock of debounce function
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM
 */
uint32_t hosal_gpio_set_debounce_time(uint32_t mode);

#ifdef __cplusplus
}
#endif

#endif /* End of HOSAL_GPIO_H */
