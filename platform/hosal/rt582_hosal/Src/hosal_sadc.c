/**
 * \file            hosal_sadc.c
 * \brief           Hosal SADC driver file
 *          
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
#include "mcu.h"

#include "hosal_sadc.h"
#include "stdio.h"

static hosal_sadc_cb_fn hosal_sadc_reg_handler = NULL;

void hosal_sadc_register_int_callback(
    hosal_sadc_cb_fn hosal_sadc_int_callback) {
    hosal_sadc_reg_handler = hosal_sadc_int_callback;
    return;
}

void hosal_sadc_cb_handler(sadc_cb_t* p_cb) {
    hosal_sadc_cb_t hosal_cb = {
        .type = p_cb->type,
        .raw.calibration_value = p_cb->raw.calibration_value,
        .raw.compensation_value = p_cb->raw.compensation_value,
        .raw.conversion_value = p_cb->raw.conversion_value,
        .data.done.p_buffer = p_cb->data.done.p_buffer,
        .data.done.size = p_cb->data.done.size,
        .data.sample.channel = p_cb->data.sample.channel,
        .data.sample.value = p_cb->data.sample.value,
    };
    if (hosal_sadc_reg_handler != NULL)
        hosal_sadc_reg_handler(&hosal_cb);
}

void hosal_sadc_config_enable(hosal_sadc_config_t sadc_cfg,
                              void* sadc_usr_callback) {
    uint32_t resolution = sadc_cfg.resolution;
    uint32_t oversample = sadc_cfg.oversample;
    if (sadc_usr_callback != NULL)
        hosal_sadc_register_int_callback(sadc_usr_callback);
    sadc_config_enable(resolution, oversample, hosal_sadc_cb_handler);
}

uint32_t hosal_sadc_channel_read(hosal_sadc_channel_config_t ch) {
    sadc_input_ch_t read_ch = (sadc_input_ch_t)ch.channel;
    return sadc_channel_read(read_ch);
}

void hosal_sadc_compensation_init(uint32_t xPeriodicTimeInSec) {
    sadc_compensation_init(xPeriodicTimeInSec);
}
