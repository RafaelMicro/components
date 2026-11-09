/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/**
 * @file mmdl_publish_main.c
 * @author Joshua Jean (joshua.jean@rafaelmicro.com)
 * @brief Periodic timer-driven publication engine: schedules and retransmits model state publications.
 * @version 0.1
 * @date 2022-07-25
 *
 *
 */

//=============================================================================
//                Include
//=============================================================================
#include <math.h>
#include "ble_mesh_element.h"
#include "mmdl_common.h"

extern ble_mesh_element_param_t g_element_info[];

xQueueHandle mmdl_publish_msg_q;

static ble_mesh_element_param_t *p_element_base = g_element_info;
static TimerHandle_t *p_mmdl_publish_timer;
//=============================================================================
//                Private Functions Declaration
//=============================================================================
static void mmdl_publish_timer_start(void);
static void mmdl_publish_timer_handle(void *param);
static uint32_t mmdl_publish_interval_get(uint8_t steps, uint8_t resolution);
static void mmdl_publish_state_msg_send(ble_mesh_element_param_t *p_element,  ble_mesh_model_param_t  *p_model);






/** @brief Create the publish message queue and the periodic publication timer, then start the timer. */
void mmdl_publish_init(void)
{
    mmdl_publish_msg_q = xQueueCreate(16, sizeof(uint32_t));

    /* create a device publish timer -- auto-reload: mmdl_publish_timer_handle()
       increments each model's publish_current_timer_value on every call and
       expects to keep being called periodically. A one-shot timer here fires
       exactly once, ever, silently disabling all periodic Model Publication
       (and this function's own retransmit logic) after the first 50 ms tick. */
    p_mmdl_publish_timer = xTimerCreate("mmdlpul",
                                            pdMS_TO_TICKS(MMLDL_PUBLISH_UINT),
                                            pdTRUE,
                                            (void *)NULL,
                                            mmdl_publish_timer_handle);

    /* start the publish timer */
    mmdl_publish_timer_start();

}

/** @brief Start the periodic publication timer. */
static void mmdl_publish_timer_start(void)
{
    xTimerStart(p_mmdl_publish_timer);
}

/**
 * @brief Periodic timer callback: walks every model on every element and, for those with active
 * publication configured, counts down to the next publish/retransmit and triggers sending when due.
 */
static void mmdl_publish_timer_handle(void *param)
{
    uint32_t i, j;
    ble_mesh_model_param_t  *p_model;
    publication_info_t      *p_model_publish_info;

    /* loop for every model */

    for (i = 0; i < pib_element_count_get(); i++)
    {
        for (j = 0; j < p_element_base[i].element_models_count; j++)
        {
            p_model = p_element_base[i].p_model[j];
            p_model_publish_info = p_model->p_publish_info;
            /* check the publish info for each model */
            if (p_model_publish_info == NULL)
            {
                /* not configure yet, check next one */
                continue;
            }
            else if (p_model_publish_info->address == MESH_UNASSIGNED_ADDR)
            {
                /* not valid, check next one */
                p_model_publish_info->is_updated = 0;
                continue;
            }
            else
            {
                if (!p_model_publish_info->is_updated)
                {
                    /* update the timer value */
                    p_model_publish_info->publish_target_timer_value = mmdl_publish_interval_get(p_model_publish_info->step, p_model_publish_info->resolution);
                    p_model_publish_info->publish_current_timer_value = 0;
                    p_model_publish_info->transmit_count = p_model_publish_info->retransmit_count + 1;
                    p_model_publish_info->is_updated = 1;
                }

                p_model_publish_info->publish_current_timer_value++;
                if (p_model_publish_info->publish_current_timer_value >= p_model_publish_info->publish_target_timer_value)
                {
                    /* send the publish state */
                    mmdl_publish_state_msg_send((p_element_base + i), p_model);
                    p_model_publish_info->transmit_count --;

                    if (p_model_publish_info->transmit_count > 0)
                    {
                        p_model_publish_info->publish_target_timer_value += (p_model_publish_info->retransmit_interval_step + 1);
                    }
                    else
                    {
                        p_model_publish_info->publish_target_timer_value = mmdl_publish_interval_get(p_model_publish_info->step, p_model_publish_info->resolution);
                        p_model_publish_info->publish_current_timer_value = 0;
                    }
                }

            }

        }

    }
}

/** @brief Convert a publish period's step count and step resolution into a number of timer ticks. */
static uint32_t mmdl_publish_interval_get(uint8_t steps, uint8_t resolution)
{
    uint32_t unit_value = 0;

    switch (resolution)
    {
    case 0:
        unit_value = 2; //the base unit is 50ms, for this resolution is 100ms
        break;

    case 1:
        unit_value = 10 * 2;
        break;

    case 2:
        unit_value = 100 * 2;
        break;

    case 3:
        unit_value = 10 * 60 * 10 * 2;
        break;
    }

    return (steps * unit_value);
}

/** @brief Enqueue a publish request for a model by posting its publication_info_t address to the publish queue. */
static void mmdl_publish_state_msg_send(ble_mesh_element_param_t *p_element,  ble_mesh_model_param_t  *p_model)
{
    uint32_t    publish_info_address;
    //uint8_t     *pBuf = NULL;

    //pBuf = pvPortMalloc(sizeof(uint32_t));
    //if (pBuf)
    {
        /* convert address to uint32_t value */
        publish_info_address = (uint32_t)p_model->p_publish_info;
        p_model->p_publish_info->p_element = p_element;
        p_model->p_publish_info->p_model = p_model;

        xQueueSendToBack(mmdl_publish_msg_q, &publish_info_address, 0);
    }

}

/** @brief Dequeue handler: decode the publication_info_t pointer and invoke the model's publish-state callback. */
void mmdl_publish_state_by_msg(uint32_t publish_address_value)
{
    ble_mesh_element_param_t  *p_element;
    ble_mesh_model_param_t    *p_model;

    publication_info_t *p_publish_info = (void *)publish_address_value;

    p_element = (ble_mesh_element_param_t *)p_publish_info->p_element;
    p_model = (ble_mesh_model_param_t *)p_publish_info->p_model;
    ((publish_state_fp)(p_publish_info->p_mmdl_publish_func))(p_element, p_model);
}
