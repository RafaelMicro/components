/**
 * \file            hosal_swi.c
 * \brief           hosal software interrupt driver file
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
 * Author:
 */

#include <stdint.h>
#include "hosal_lpm.h"
#include "lpm.h"
#include "mcu.h"
#include "stdio.h"
#include "hosal_status.h"
#include "comm_subsystem_drv.h"

int hosal_lpm_init(void) {
    lpm_init();
    return HOSAL_STATUS_SUCCESS;
}

int hosal_get_lpm_ioctrl(int ctl, uint32_t* para) {

    int status = HOSAL_STATUS_SUCCESS;

    switch (ctl) {
        case HOSAL_LPM_GET_MASK:
            para[0] = lpm_get_low_power_mask_status();
            break;
        case HOSAL_LPM_GET_POWER_LEVEL:
             para[0] = lpm_get_low_power_level();
             break;
        default: return -1;
    }

    return HOSAL_STATUS_SUCCESS;
}

int hosal_lpm_ioctrl(int ctl, uint32_t para) {

    int status = HOSAL_STATUS_SUCCESS;

    switch (ctl) {

        case HOSAL_LPM_MASK: lpm_low_power_mask((uint32_t)para); break;

        case HOSAL_LPM_SUBSYSTEM_MASK:
            lpm_comm_subsystem_wakeup_mask((uint32_t)para);
            break;

        case HOSAL_LPM_UNMASK: lpm_low_power_unmask((uint32_t)para); break;

        case HOSAL_LPM_SUBSYSTEM_UNMASK:
            lpm_comm_subsystem_wakeup_unmask((uint32_t)para);
            break;

        case HOSAL_LPM_SRAM0_RETAIN:
            lpm_set_sram_sleep_deepsleep_shutdown((uint32_t)para);
            break;

        case HOSAL_LPM_SET_POWER_LEVEL: lpm_set_low_power_level((uint32_t)para); break;
        case HOSAL_LPM_ENABLE_WAKE_UP_SOURCE:
            lpm_enable_low_power_wakeup((uint32_t)para);
            break;

        case HOSAL_LPM_DISABLE_WAKE_UP_SOURCE:
            lpm_disable_low_power_wakeup((uint32_t)para);
            break;

        case HOSAL_LPM_ENTER_LOW_POWER: lpm_enter_low_power_mode(); break;

        case HOSAL_LPM_SUBSYSTEM_SRAM_DEEP_SLEEP_INIT:
            lpm_comm_subsystem_sram_deep_sleep_init();
            break;  

        case HOSAL_LPM_SUBSYSTEM_ENTER_LOW_POWER:
            lpm_sub_system_low_power_mode( (commumication_subsystem_pwr_mode_cfg_t) para);
            break;   

        case HOSAL_LPM_SUBSYSTEM_DISABLE_LDO_MODE:
            lpm_comm_subsystem_disable_ldo_mode();
            break;
        default: return -1;
    }

    return HOSAL_STATUS_SUCCESS;
}
