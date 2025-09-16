/**
 * \file            wdt.h
 * \brief           Watch Dog timer header file
 */
/*
 * Copyright (c) 2024 Rafale Micro
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

#ifndef WDT_H
#define WDT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "mcu.h"

/**
 * \brief           Wdt prescale definitions.
 */
#define WDT_PRESCALE_1                  0
#define WDT_PRESCALE_16                 1
#define WDT_PRESCALE_32                 3
#define WDT_PRESCALE_128                4
#define WDT_PRESCALE_256                2
#define WDT_PRESCALE_1024               5
#define WDT_PRESCALE_4096               6

/**
 * \brief           Wdt Kick value definitions.
 */
#define WDT_KICK_VALUE         0xA5A5

/**
 * \brief           Wdt interrupt service routine callback for user application.
 */
typedef void (*wdt_cb_fn)(void);


/**
 * \brief           Wdt config structure .
 */
typedef struct {
    uint8_t int_enable   : 1;                   /*!< config of interrupt enable */
    uint8_t reset_enable : 1;                   /*!< config of reset enable */
    uint8_t lock_enable  : 1;                   /*!< config of lockout enable */
    uint8_t prescale     : 3;                   /*!< config of prescale */
} wdt_config_mode_t;

/**
 * \brief           Wdt ticks config structure.
 */
typedef struct {
    uint32_t wdt_ticks;                         /*!< config of load value */
    uint32_t int_ticks;                         /*!< config of interrupt value */
    uint32_t wdt_min_ticks;                     /*!< config of wdt min value */
} wdt_config_tick_t;


/**
 * \brief           Register wdt callback function
 * \param[in]       wdt_cb: user callback function
 * \return          Function status, STATUS_SUCCESS
 */
uint32_t wdt_callback_register(wdt_cb_fn wdt_cb);

/**
 * \brief           WDT parameter setting and start
 * \param[in]       wdt_mode: wdt setting
 * \param[in]       wdt_cfg_ticks: wdt ticks setting
 * \param[in]       wdt_cb: user callback function
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM,
 *                  STATUS_INVALID_REQUEST
 */
uint32_t wdt_start(wdt_config_mode_t wdt_mode, wdt_config_tick_t wdt_cfg_ticks,
                   wdt_cb_fn wdt_cb);

/**
 * \brief           WDT stop
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_REQUEST
 */
uint32_t wdt_stop(void);

/**
 * \brief           Get WDT number of resets
 * \param[out]      reset_cnt: Pointer to a user-provided variable where the WDT reset 
 *                             event register value (`WDT->rst_occur.reg`) will be stored.
 * \return          Function status, STATUS_SUCCESS
 */
__STATIC_INLINE uint32_t wdt_reset_event_get(uint32_t* reset_cnt) {
    *reset_cnt = (WDT->rst_occur.reg & 0xFF);
    return STATUS_SUCCESS;
}

/**
 * \brief           Clear WDT number of resets
 * \return          Function status, STATUS_SUCCESS
 */
__STATIC_INLINE uint32_t wdt_reset_event_clear(void) {
    WDT->rst_occur.bit.reset_occur = 1;
    return STATUS_SUCCESS;
}

/**
 * \brief           Reload the watchdog value
 * \return          Function status, STATUS_SUCCESS
 */
__STATIC_INLINE uint32_t wdt_kick(void) {
    WDT->wdt_kick = WDT_KICK_VALUE;
    return STATUS_SUCCESS;
}

/**
 * \brief           Clear Watchdog interrupt flag
 * \return          Function status, STATUS_SUCCESS
 */
__STATIC_INLINE uint32_t wdt_interrupt_clear(void) {
    WDT->clear = 1;
    return STATUS_SUCCESS;
}

/**
 * \brief           Get watchdog timer current tick value
 * \param[out]      tick_value: Pointer to a user-provided variable 
 *                              where the WDT value will be stored.
 * \return          Function status, STATUS_SUCCESS
 */
__STATIC_INLINE uint32_t wdt_current_get(uint32_t* tick_value) {
    *tick_value = (WDT->value & 0xFFFFFFFF);
    return STATUS_SUCCESS;
}

#ifdef __cplusplus
}
#endif

#endif /* End of WDT_H */
