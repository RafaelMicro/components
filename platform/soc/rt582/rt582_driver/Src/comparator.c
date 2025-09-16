/**
 * \file            comparator.c
 * \brief           Comparator driver 
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
 * Author: ives.lee
 */


#include "mcu.h"


static comp_isr_handler_t   comp_reg_handler = NULL;
static int32_t comp_int_callback_enable;


/**
 * \brief           Comparator interrupt handler
 */
void comp_handler(void) {

    if (comp_int_callback_enable == 0)
    {
        if (COMP_INT_POL_GET() == COMP_CONFIG_INT_POL_BOTH)
        {
            if (COMP_INT_STATUS_GET())
            {
                comp_reg_handler();
            }
        }
        else if (COMP_INT_POL_GET() == COMP_CONFIG_INT_POL_RISING)
        {
            if (COMP_OUT_GET() == 1 && COMP_INT_STATUS_GET())
            {
                comp_reg_handler();
            }
        }
        else if (COMP_INT_POL_GET() == COMP_CONFIG_INT_POL_FALLING)
        {
            if (COMP_OUT_GET() == 0 && COMP_INT_STATUS_GET())
            {
                comp_reg_handler();
            }
        }
    }
    else
    {
        comp_int_callback_enable -= 1;

        if (comp_int_callback_enable < 0)
        {
            comp_int_callback_enable = 0;
        }
    }

    COMP_INT_CLEAR();
    return;
}

uint32_t comp_register_int_callback(comp_isr_handler_t comp_int_callback) {
    comp_reg_handler = comp_int_callback;

    return STATUS_SUCCESS;
}

uint32_t comp_int_enable(void) {
    COMP_INT_CLEAR();
    COMP_INT_ENABLE();
    NVIC_EnableIRQ((IRQn_Type)(Comp_IRQn));

    return STATUS_SUCCESS;
}

uint32_t comp_int_disable(void) {
    NVIC_DisableIRQ((IRQn_Type)(Comp_IRQn));
    COMP_INT_DISABLE();
    COMP_INT_CLEAR();

    return STATUS_SUCCESS;
}

uint32_t comp_int_callback_counter(uint32_t counter) {
     comp_int_callback_enable = counter;
    return STATUS_SUCCESS;
}

uint32_t comp_init(comp_config_t* p_config,
                   comp_isr_handler_t comp_int_callback) {
    if (p_config == NULL) {
        return STATUS_INVALID_PARAM;
    }
    
    COMP_SELREF_SEL(p_config->comp_selref);     /* Select the Comparator input N source */
    COMP_INT_POL(p_config->comp_int_pol);       /* Set the Comparator interrupt polarity */
    COMP_SELINPUT_SEL( p_config->comp_selinput);/* Select the Comparator input P source */
    COMP_V_SEL(p_config->comp_v_sel);           /* Select the Comparator internal vdd div voltage */
    COMP_REF_SEL(p_config->comp_ref_sel);       /* Select the Comparator N input for comparision */
    COMP_CH_SEL(p_config->comp_ch_sel);         /* Select the Comparator P input for comparision */
    COMP_PW_SEL(p_config->comp_pw);             /* Select the Comparator current */
    COMP_HYS_SEL(p_config->comp_hys_sel);       /* Select the Comparator hys window */
    COMP_SWDIV_SEL(p_config->comp_swdiv);       /* Switch the Comparator vdd div type */
    COMP_DS_WAKEUP(p_config->comp_ds_wakeup);   /* Select the Comparator wakeup in DeepSleep */
    COMP_DS_INV(p_config->comp_ds_inv);         /* Select the invert of the Comparator
                                                 output for waking up from DeepSleep */

    if (comp_int_callback != NULL)
    {
        if (p_config->comp_int_pol == COMP_CONFIG_INT_POL_FALLING)
        {
            comp_int_callback_counter(1);
        }
        else if (p_config->comp_int_pol == COMP_CONFIG_INT_POL_RISING)
        {
            comp_int_callback_counter(2);
        }
        else
        {
            comp_int_callback_counter(3);
        }

        comp_register_int_callback(comp_int_callback);
        comp_int_enable();
    }

    return STATUS_SUCCESS;
}

uint32_t comp_enable(void) {
    COMP_ENABLE();                              /* Enable Comparator */

    return STATUS_SUCCESS;
}

uint32_t comp_enable_at_sleep(void) {
    COMP_ENABLE_SP();                           /* Enable Comparator at Sleep */

    return STATUS_SUCCESS;
}

uint32_t comp_enable_at_deepsleep(void) {
    COMP_ENABLE_DS();                           /* Enable Comparator at DeepSleep */

    return STATUS_SUCCESS;
}
