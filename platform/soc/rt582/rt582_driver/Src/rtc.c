/**
 * \file            rtc.c
 * \brief           RTC driver file
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


#include "mcu.h"


static rtc_cb_fn user_rtc_isr;

void rtc_callback_register(rtc_cb_fn rtc_cb) {
    user_rtc_isr = rtc_cb;

    return;
}

__STATIC_INLINE uint32_t bcd2bin(uint32_t val) {
    return ((val & 0xF) + ((val & 0xFF) >> 4) * 10);
}

__STATIC_INLINE uint32_t bin2bcd(uint32_t val) {
    return (((val / 10) << 4) | (val % 10));
}

uint32_t rtc_get_time(rtc_time_t* tm) {
    uint32_t temp;

    if (tm == NULL) {
        return STATUS_INVALID_PARAM;
    }

    do {
        tm->tm_sec = bcd2bin(RTC->second);
        tm->tm_min = bcd2bin(RTC->minute);
        tm->tm_hour = bcd2bin(RTC->hour);
        tm->tm_day = bcd2bin(RTC->day);
        tm->tm_mon = bcd2bin(RTC->month);
        tm->tm_year = bcd2bin(RTC->year);

        /*recheck second again.*/
        temp = bcd2bin(RTC->second);
    } while (temp == 0); /* maybe HH:MM:59 to become
                         HH:(MM+1):00 so we read again.*/

    tm->tm_sec = temp; /* just second update one second. */

    return STATUS_SUCCESS;
}

uint32_t rtc_set_time(rtc_time_t* tm) {
    if (tm == NULL) {
        return STATUS_INVALID_PARAM;
    }

    RTC->second = bin2bcd(tm->tm_sec);
    RTC->minute = bin2bcd(tm->tm_min);
    RTC->hour = bin2bcd(tm->tm_hour);
    RTC->day = bin2bcd(tm->tm_day);
    RTC->month = bin2bcd(tm->tm_mon);
    RTC->year = bin2bcd(tm->tm_year);

    RTC->load = RTC_LOAD_TIME;

    /* wait this take effect, wait RTC_LOAD bcome 0 */
    while (RTC->load) {}

    return STATUS_SUCCESS;
}

uint32_t rtc_get_alarm(rtc_time_t* tm) {
    if (tm == NULL) {
        return STATUS_INVALID_PARAM;
    }

    tm->tm_sec = bcd2bin(RTC->alarm_second);
    tm->tm_min = bcd2bin(RTC->alarm_minute);
    tm->tm_hour = bcd2bin(RTC->alarm_hour);
    tm->tm_day = bcd2bin(RTC->alarm_day);
    tm->tm_mon = bcd2bin(RTC->alarm_month);
    tm->tm_year = bcd2bin(RTC->alarm_year);

    return STATUS_SUCCESS;
}

uint32_t rtc_set_alarm(rtc_time_t* tm, uint32_t rtc_int_mode,
                       rtc_cb_fn rtc_usr_isr) {
    uint32_t temp_int_reg;

    if (tm == NULL) {
        return STATUS_INVALID_PARAM;
    }

    if (rtc_usr_isr == NULL) {
        return STATUS_INVALID_PARAM;
    }

    /*
     * IRQ Event and IRQ Event Repeat bit in hardware register is bit8 and bit9
     * But In our software flag, each event flag in different position, so we need
     * adjust the shift number depends on the flag type.
     */
    RTC->alarm_second = bin2bcd(tm->tm_sec)
                        | ((rtc_int_mode & RTC_SEC_MASK)
                           << RTC_IRQEVENT_SEC_SHIFT);
    RTC->alarm_minute = bin2bcd(tm->tm_min)
                        | ((rtc_int_mode & RTC_MIN_MASK)
                           << RTC_IRQEVENT_MIN_SHIFT);
    RTC->alarm_hour = bin2bcd(tm->tm_hour)
                      | ((rtc_int_mode & RTC_HOUR_MASK)
                         << RTC_IRQEVENT_HOUR_SHIFT);
    RTC->alarm_day = bin2bcd(tm->tm_day)
                     | ((rtc_int_mode & RTC_DAY_MASK)
                        << RTC_IRQEVENT_DAY_SHIFT);
    RTC->alarm_month = bin2bcd(tm->tm_mon)
                       | ((rtc_int_mode & RTC_MONTH_MASK)
                          << RTC_IRQEVENT_MONTH_SHIFT);
    RTC->alarm_year = bin2bcd(tm->tm_year)
                      | ((rtc_int_mode & RTC_YEAR_MASK)
                         >> RTC_IRQEVENT_YEAR_RSHIFT);

    temp_int_reg = (rtc_int_mode >> RTC_INTERRUPT_MASK_SHIFT)
                   & RTC_INTERRUPT_MASK;

    /* clear all interrupt source first */
    RTC->int_clear = RTC_INTERRUPT_MASK;

    RTC->int_control = temp_int_reg;

    rtc_callback_register(rtc_usr_isr);

    RTC->load = RTC_LOAD_ALARM;

    /* wait this take effect, wait RTC_LOAD bcome 0 */
    while (RTC->load) {}

    return STATUS_SUCCESS;
}

uint32_t rtc_disable_alarm(void) {

    /* set control register to disable all interrpt */
    RTC->int_control = 0;

    /* clear all interrupt source first */
    RTC->int_clear = RTC_INTERRUPT_MASK;

    return STATUS_SUCCESS;
}

uint32_t rtc_set_clk(uint32_t clk) {
    /* only 16bits. */
    RTC->clock_div = (clk - 1) & 0xFFFF;
    RTC->load = RTC_LOAD_DIVISOR;

    /* wait this take effect, wait RTC_LOAD bcome 0 */
    while (RTC->load) {}

    return STATUS_SUCCESS;
}

uint32_t rtc_reset(void) {

    RTC->control = RTC_CTRL_CLRPLS;

    /* clear in progress */
    while (RTC->control & RTC_CTRL_CLRPLS) {}

    return STATUS_SUCCESS;
}

/**
 * \brief           RTC Interrupt Handler
 */
void rtc_handler(void) {
    uint32_t status;

    status = RTC->int_status;
    /* clear interrupt status */
    RTC->int_clear = status;

    if (user_rtc_isr != NULL) {
        /* call RTC user isr */
        user_rtc_isr(status);
    }
}
