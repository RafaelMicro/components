/**
 * \file            hosal_sysctrl.c
 * \brief           Hosal system control driver file
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
#include <stdio.h>
#include <stdint.h>
#include "mcu.h"
#include "sysctrl.h"
#include "hosal_sysctrl.h"
#include "hosal_status.h"

void hosal_delay_us(unsigned int us) { 
    delay_us (us);
}

void hosal_delay_ms(unsigned int ms) {
    delay_ms(ms);
}

uint32_t hosal_pin_get_mode(uint32_t pin_number) {
    return pin_get_mode(pin_number);
}

void hosal_pin_set_mode(uint32_t pin_number, uint32_t mode) {
    pin_set_mode(pin_number, mode);
}

void hosal_pin_set_pullopt(uint32_t pin_number, uint32_t mode) {
    pin_set_pullopt(pin_number, mode);
}

void hosal_enable_pin_opendrain(uint32_t pin_number) {
    enable_pin_opendrain(pin_number);
}

void hosal_disable_pin_opendrain(uint32_t pin_number) {
    disable_pin_opendrain(pin_number);
}

void hosal_config_peripherl_clock(uint32_t per_clk, void* cfg_para) {

     if(cfg_para) {
        
        enable_perclk(per_clk);
     }
     else  {

        disable_perclk(per_clk);
     }
}


int hosal_get_rco_clock_tick(uint32_t* rco_tick)
{
    if(rco_tick == NULL){
        
        return HOSAL_STATUS_INVALID_PARAM;
    }

    *rco_tick = 40;

    return HOSAL_STATUS_SUCCESS;
}