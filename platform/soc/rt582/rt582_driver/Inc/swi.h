/**
 * \file            swi.h
 * \brief           software interrupt driver header file
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
 * Author:         ives.Lee
 */
#ifndef SWI_H
#define SWI_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "mcu.h"

/**
 * \brief           software interrupt const define
 */
#define MAX_NUMBER_OF_SOFT_INT              1
#define MAX_NUMBER_OF_SWI                   32
/**
 * \brief           software interrupt enum define
 */
typedef enum {
    SWI_ID_0 = 0,                                /*!< swi0 idefinitions */
    SWI_MAX
} swi_id_t;

/**
 * \brief           User cb handler prototype.
 *
 * This function is called when the requested number of samples has been processed.
 *
 * \param[in]       swi_id Software Interrupt ID
 *                      \arg SWI_ID_0 ~ SWI_ID_31
 */
typedef void (*swi_isr_handler_t)(uint32_t id);

#define SWI_INT_ENABLE(para_set)           (REMAP->sw_irq_en_set = para_set)   /*!< Enable the  software interrupt> */
#define SWI_INT_ENABLE_GET()               (REMAP->sw_irq_en_set)              /*!< Return the software interrupt enable status */
#define SWI_INT_DISABLE(para_set)          (REMAP->sw_irq_en_clr = para_set)   /*!< Disable thesoftware interrupt */
#define SWI_INT_CLEAR(para_set)            (REMAP->sw_irq_clr = para_set)      /*!< Clear the software interrupt status */
#define SWI_INT_STATUS_SET(para_set)       (REMAP->sw_irq_set = para_set)      /*!< Set thesoftware interrupt status */
#define SWI_INT_STATUS_GET()               (REMAP->sw_irq_set)                 /*!< Return thesoftware interrupt status */

/**
 * \brief           Clear all SWI interrupt service routine callback.
 * \return          None
 */
uint32_t swi_int_callback_clear(uint32_t id);

/**
 * \brief           Enable the specified software interrupts
 * \param[in]       swi_id Software Interrupt ID
 *                      \arg SWI_ID_0 ~ SWI_ID_31
 * \param[in]       swi_int_callback Software interrupt callback handler
 */
uint32_t swi_int_enable(uint32_t swi_id, uint32_t swi_trig_id, swi_isr_handler_t swi_int_callback);

/**
 * \brief           Disable software interrupt(s)
 * \param[in]       swi_id Software interrupt ID
 *                      \arg SWI_ID_0 ~ SWI_ID_31
 */
uint32_t swi_int_disable(uint32_t id, uint32_t swi_trig_id);

/**
 * \brief           Trigger software interrupt(s)
 * \param[in]       swi_id Software interrupt ID
 *                      \arg SWI_ID_0 ~ SWI_ID_31
 */
uint32_t swi_int_trigger(uint32_t id, uint32_t swi_trig_id);


#ifdef __cplusplus
}
#endif

#endif /* End of SWI_H */
