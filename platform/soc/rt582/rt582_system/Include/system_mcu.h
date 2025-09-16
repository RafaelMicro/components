/**
 * \file      System_mcu   CM3 Device MCU       
 * \brief     System Initialization header file for Cortex-M3 device based on CMSIS-CORE
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
 *
 * Author:        
 */
#ifndef SYSTEM_CM3MCU_H
#define SYSTEM_CM3MCU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "sysfun.h"

/**
 * \brief           PMU mode type definitions.
 */
#define PMU_LDO_MODE  0
#define PMU_DCDC_MODE 1

#ifndef SET_PMU_MODE
#define SET_PMU_MODE PMU_DCDC_MODE
#endif

/**
 * \brief           Set the system PMU mode
 * \param[in]       pmu_mode Specifies the system PMU mode
 *                  This parameter can be the following values:
 *                      \arg PMU_MODE_LDO: Specifies the system PMU LDO mode
 *                      \arg PMU_MODE_DCDC: Specifies the system PMU DCDC mode
 * \return          None
 */
void SystemPmuSetMode(pmu_mode_cfg_t pmu_mode);
extern uint32_t SystemFrequency;                /*!< System Clock Frequency (Core Clock)  */
extern uint32_t SystemCoreClock;                /*!< Processor Clock Frequency            */

/**
 * \brief           Setup the microcontroller system.
 *                  Initialize the System and update the SystemCoreClock variable.
 */
void SystemInit(void);

/**
 * \brief           Updates the SystemCoreClock with current core Clock
 *                  retrieved from cpu registers.
 */
void systemcoreclockupdate(void);

/**
 * \brief           Updates the SystemFrequency with current core Clock
 *                  retrieved from clock mode.
 */

void systemfrequencyupdate(void);

#ifdef __cplusplus
}
#endif

#endif /* end of SYSTEM_CM3MCU_H */
