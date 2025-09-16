/**
 * \file            hosal_rtc.h
 * \brief           Hosal RTC driver header file
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

#ifndef HOSAL_RTC_H
#define HOSAL_RTC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "rtc.h"

/**
 * \brief           rtc alarm mode
 */
/* Geneate second interrupt for every new seconds */
#define HOSAL_RTC_MODE_EVERY_SEC_INTERRUPT RTC_MODE_EVERY_SEC_INTERRUPT
/* Geneate second interrupt only for matched second of every minutes */
#define HOSAL_RTC_MODE_MATCH_SEC_INTERRUPT RTC_MODE_MATCH_SEC_INTERRUPT
/* Geneate event interrupt for matched second of every munutes */
#define HOSAL_RTC_MODE_SECOND_EVENT_INTERRUPT RTC_MODE_SECOND_EVENT_INTERRUPT
/* Geneate minute interrupt for every new minutes (**:00) */
#define HOSAL_RTC_MODE_EVERY_MIN_INTERRUPT RTC_MODE_EVERY_MIN_INTERRUPT
/* Geneate minute interrupt only for matched minutes (mm:00) of every hours, mm is the value set in alarm minute */
#define HOSAL_RTC_MODE_MATCH_MIN_INTERRUPT RTC_MODE_MATCH_MIN_INTERRUPT
/* Geneate event interrupt for matched minutes (mm:ss) of every hours */
#define HOSAL_RTC_MODE_MINUTE_EVENT_INTERRUPT RTC_MODE_MINUTE_EVENT_INTERRUPT
/* Geneate hour interrupt for every new hours (**:00:00)  */
#define HOSAL_RTC_MODE_EVERY_HOUR_INTERRUPT RTC_MODE_EVERY_HOUR_INTERRUPT
/* Geneate hour interrupt only for matched hours (hh:00:00) of every days, HH is the value set in alarm hour */
#define HOSAL_RTC_MODE_MATCH_HOUR_INTERRUPT RTC_MODE_MATCH_HOUR_INTERRUPT
/* Geneate event interrupt only for matched hours (hh:mm:ss) of every days  */
#define HOSAL_RTC_MODE_HOUR_EVENT_INTERRUPT RTC_MODE_HOUR_EVENT_INTERRUPT
/* Geneate day interrupt for every new day (00:00:00) */
#define HOSAL_RTC_MODE_EVERY_DAY_INTERRUPT RTC_MODE_EVERY_DAY_INTERRUPT
/* Geneate day interrupt only for match day of months ( dd 00:00:00) */
#define HOSAL_RTC_MODE_MATCH_DAY_INTERRUPT RTC_MODE_MATCH_DAY_INTERRUPT
/* Geneate event interrupt for matched day (dd hh:mm:ss) */
#define HOSAL_RTC_MODE_DAY_EVENT_INTERRUPT RTC_MODE_DAY_EVENT_INTERRUPT
/* Geneate month interrupt for every new month ( **:00 00:00:00) */
#define HOSAL_RTC_MODE_EVERY_MONTH_INTERRUPT RTC_MODE_EVERY_MONTH_INTERRUPT
/* Geneate month interrupt only for matched month of years ( mm:00 00:00:00) */
#define HOSAL_RTC_MODE_MATCH_MONTH_INTERRUPT RTC_MODE_MATCH_MONTH_INTERRUPT
/* Geneate event interrupt for matched month (mm:dd hh:mm:ss) */
#define HOSAL_RTC_MODE_MONTH_EVENT_INTERRUPT RTC_MODE_MONTH_EVENT_INTERRUPT
/* Geneate year interrupt for every new year ( **:00:00 00:00:00) */
#define HOSAL_RTC_MODE_EVERY_YEAR_INTERRUPT RTC_MODE_EVERY_YEAR_INTERRUPT
/* Geneate year interrupt only for matched year of century ( YY:00:00 00:00:00) */
#define HOSAL_RTC_MODE_MATCH_YEAR_INTERRUPT RTC_MODE_MATCH_YEAR_INTERRUPT
/* Geneate event interrupt for matched year:month:day hour:minute:second (yy:mm:dd hh:mm:ss) */
#define HOSAL_RTC_MODE_YEAR_EVENT_INTERRUPT RTC_MODE_YEAR_EVENT_INTERRUPT

/**
 * \brief           rtc interrupt enable
 */
/* Geneate Second interrupt */
#define HOSAL_RTC_MODE_EN_SEC_INTERRUPT RTC_MODE_EN_SEC_INTERRUPT
/* Geneate Minute interrupt */
#define HOSAL_RTC_MODE_EN_MIN_INTERRUPT RTC_MODE_EN_MIN_INTERRUPT
/* Geneate Hour interrupt */
#define HOSAL_RTC_MODE_EN_HOUR_INTERRUPT RTC_MODE_EN_HOUR_INTERRUPT
/* Geneate Day interrupt */
#define HOSAL_RTC_MODE_EN_DAY_INTERRUPT RTC_MODE_EN_DAY_INTERRUPT
/* Geneate Month interrupt */
#define HOSAL_RTC_MODE_EN_MONTH_INTERRUPT RTC_MODE_EN_MONTH_INTERRUPT
/* Geneate Year interrupt */
#define HOSAL_RTC_MODE_EN_YEAR_INTERRUPT RTC_MODE_EN_YEAR_INTERRUPT
/* Geneate Event interrupt */
#define HOSAL_RTC_MODE_EVENT_INTERRUPT RTC_MODE_EVENT_INTERRUPT

/**
 * \brief           RTC timer structure for RTC time value
 */
typedef struct {
    uint32_t tm_sec;  /*!< rtc second in decimal */
    uint32_t tm_min;  /*!< rtc minute in decimal */
    uint32_t tm_hour; /*!< rtc hour in decimal */
    uint32_t tm_day;  /*!< rtc day in decimal */
    uint32_t tm_mon;  /*!< rtc month in decimal */
    uint32_t tm_year; /*!< rtc year in decimal */
} hosal_rtc_time_t;


/**
 * \brief           Get current rtc time value
 * \param[out]      tm: save time value you want to get
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM
 */
uint32_t hosal_rtc_get_time(void* tm);

/**
 * \brief           Set rtc current time value
 * \param[in]       tm: the time value you want to set
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM
 */
uint32_t hosal_rtc_set_time(void* tm);

/**
 * \brief           Get rtc alarm  time value
 * \param[out]      tm: save the time alarm value you want to get
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM
 */
uint32_t hosal_rtc_get_alarm(void* tm);

/**
 * \brief           Set rtc alarm time value and alarm mode
 * \param[in]       tm: the time value you want to alarm
 * \param[in]       rtc_int_mode: the rtc alarm mode
 * \param[in]       rtc_usr_isr: when rtc interrupt happen it will call rtc_usr_isr to
 *                               notify the interrupt happen
 * \return          Function status, STATUS_SUCCESS, STATUS_INVALID_PARAM
 */
uint32_t hosal_rtc_set_alarm(void* tm, uint32_t rtc_int_mode,
                             void* rtc_usr_isr);

/**
 * \brief           Use to disable rtc alarm
 * \return          Function status, STATUS_SUCCESS
 */
uint32_t hosal_rtc_disable_alarm(void);

/**
 * \brief           Use to set rtc ticks for second
 * \param[in]       clk: Set ticks for one second used for RTC counter
 * \return          Function status, STATUS_SUCCESS
 */
uint32_t hosal_rtc_set_clk(uint32_t clk);

/**
 * \brief           Use to reset the RTC to default setting
 * \return          Function status, STATUS_SUCCESS
 */
uint32_t hosal_rtc_reset(void);

#ifdef __cplusplus
}
#endif

#endif /* End of HOSAL_RTC_H */
