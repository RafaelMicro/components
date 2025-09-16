/**
 * \file            hosal_gpio.c
 * \brief           Hosal GPIO driver file
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
#include "stdio.h"

#include "mcu.h"
#include "hosal_gpio.h"

uint32_t hosal_gpio_cfg_output(uint32_t pin_number) {
    uint32_t rval;

    rval =  gpio_cfg(pin_number, GPIO_PIN_DIR_OUTPUT, GPIO_PIN_NOINT);

    return rval;
}

uint32_t hosal_gpio_cfg_input(uint32_t pin_number,
                          hosal_gpio_input_config_t input_cfg) {
    uint32_t rval;

    rval = gpio_cfg(pin_number, GPIO_PIN_DIR_INPUT,
             (gpio_pin_int_mode_t)input_cfg.pin_int_mode);

    if (rval == STATUS_SUCCESS) {
        if (input_cfg.usr_cb != NULL) {
            rval = gpio_callback_register(pin_number, input_cfg.usr_cb, input_cfg.param);
        }
    }

    return rval;
}

uint32_t hosal_gpio_pin_set(uint32_t pin_number) { 
    uint32_t rval;

    rval = gpio_pin_set(pin_number);

    return rval;
}

uint32_t hosal_gpio_pin_clear(uint32_t pin_number) { 
    uint32_t rval;

    rval = gpio_pin_clear(pin_number); 

    return rval;
}

uint32_t hosal_gpio_pin_write(uint32_t pin_number, uint32_t value) {
    uint32_t rval;

    rval = gpio_pin_write(pin_number, value);

    return rval;
}

uint32_t hosal_gpio_pin_toggle(uint32_t pin_number) { 
    uint32_t rval;

    rval = gpio_pin_toggle(pin_number); 

    return rval;
}

uint32_t hosal_gpio_pin_get(uint32_t pin_number, uint32_t* value) {
    uint32_t rval;

    rval = gpio_pin_get(pin_number, value);

    return rval;
}

uint32_t hosal_gpio_int_enable(uint32_t pin_number) { 
    uint32_t rval;

    rval = gpio_int_enable(pin_number);

    return rval;
}

uint32_t hosal_gpio_int_disable(uint32_t pin_number) { 
    uint32_t rval;

    rval = gpio_int_disable(pin_number);

    return rval;
}

uint32_t hosal_gpio_debounce_enable(uint32_t pin_number) { 
    uint32_t rval;

    rval = gpio_debounce_enable(pin_number);

    return rval;
}

uint32_t hosal_gpio_debounce_disable(uint32_t pin_number) { 
    uint32_t rval;

    rval = gpio_debounce_disable(pin_number);

    return rval;
}

uint32_t hosal_gpio_set_debounce_time(uint32_t mode) {
    uint32_t rval;

    rval = gpio_set_debounce_time(mode);

    return rval;
}
