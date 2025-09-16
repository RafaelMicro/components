/**
 * \file            wdt.c
 * \brief           Watch Dog timer file
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

#include "wdt.h"
#include "mcu.h"


static wdt_cb_fn user_wdt_isr = NULL;

uint32_t wdt_callback_register(wdt_cb_fn wdt_cb) {
    user_wdt_isr = wdt_cb;

    return STATUS_SUCCESS;
}

uint32_t wdt_start(wdt_config_mode_t wdt_mode, wdt_config_tick_t wdt_cfg_ticks,
                   wdt_cb_fn wdt_handler) {
    wdt_ctrl_t controller;
    controller.reg = 0;

    controller.bit.wdt_en = 1;

    if (WDT->control.bit.lockout) {
        return STATUS_INVALID_REQUEST; /*Lockmode can Not change anymore.*/
    }

    if (wdt_mode.int_enable) {
        /*interrupt mode should has interrupt ISR*/
        if (wdt_handler == NULL) {
            return STATUS_INVALID_PARAM;
        }

        if (wdt_cfg_ticks.int_ticks >= wdt_cfg_ticks.wdt_ticks) {
            return STATUS_INVALID_PARAM; /*the setting is nonsense.*/
        }

        WDT->clear = 1; /*clear interrupt REQ?*/

        wdt_callback_register(wdt_handler);
        controller.bit.int_en = 1;

        WDT->int_value = wdt_cfg_ticks.int_ticks;
    } else {
        /*No interrupt mode.*/
        user_wdt_isr = NULL;
    }

    if (wdt_mode.reset_enable) {
        controller.bit.reset_en = 1; /*Lock*/
    }

    if (wdt_mode.lock_enable) {
        controller.bit.lockout = 1;
    }

    controller.bit.prescale = wdt_mode.prescale;

    WDT->window_min = wdt_cfg_ticks.wdt_min_ticks;
    WDT->load = wdt_cfg_ticks.wdt_ticks;
    WDT->control = controller;

    return STATUS_SUCCESS;
}

uint32_t wdt_stop(void) {
    if (WDT->control.bit.lockout) {
        return STATUS_INVALID_REQUEST; /*Lockmode can Not change anymore.*/
    }

    WDT->control.bit.wdt_en = 0;

    return STATUS_SUCCESS;
}

/**
 * \brief           Watch dog Interrupt Handler
 */
void wdt_handler(void) {
    WDT->clear = 1;
    if (user_wdt_isr) {
        user_wdt_isr();
    }
}
