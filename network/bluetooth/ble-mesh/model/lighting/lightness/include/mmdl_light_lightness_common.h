/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/**
 * @file mmdl_light_lughtness_sr.h
 * @author Joshua Jean (joshua.jean@rafaelmicro.com)
 * @brief Shared state and message structures for the BLE Mesh Light Lightness server/setup server models.
 * @version 0.1
 * @date 2022-07-13
 *
 *
 */


#ifndef __MMDL_LIGHT_LIGHTNESS_COMMON_H__
#define __MMDL_LIGHT_LIGHTNESS_COMMON_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Lightness model and setup model sharing the same data structure */
typedef struct light_lightness_state_s
{
    /* states for lightness model */
    uint16_t    lightness_linear;
    uint16_t    lightness_actual;
    uint16_t    lightness_last;

    /* states for lightness setup model */
    uint16_t    lightness_default;
    uint16_t    lightness_range_min;
    uint16_t    lightness_range_max;

    /* private variables accessed internal */
    uint16_t    lightness_target;
} light_lightness_state_t;

/** @brief Wire format for the Light Lightness (Actual) Set / Set Unacknowledged message. */
typedef struct __attribute__((packed)) light_lightness_set_msg_s
{
    uint16_t    lightness;
    uint8_t     tid;
    uint8_t     transition_time;
    uint8_t     delay;
} light_lightness_set_msg_t;

/** @brief Wire format for the Light Lightness Linear Set / Set Unacknowledged message. */
typedef struct __attribute__((packed)) light_lightness_linear_set_msg_s
{
    uint16_t    lightness;
    uint8_t     tid;
    uint8_t     transition_time;
    uint8_t     delay;
} light_lightness_linear_set_msg_t;

/** @brief Wire format for the Light Lightness Default Set / Set Unacknowledged message. */
typedef struct __attribute__((packed)) light_lightness_default_set_msg_s
{
    uint16_t    lightness;
} light_lightness_default_set_msg_t;

/** @brief Wire format for the Light Lightness Range Set / Set Unacknowledged message. */
typedef struct __attribute__((packed)) light_lightness_range_set_msg_s
{
    uint16_t range_min;
    uint16_t range_max;
} light_lightness_range_set_msg_t;

/** @brief Wire format for the Light Lightness / Lightness Linear Status reply message. */
typedef struct __attribute__((packed)) light_lightness_status_msg_s
{
    uint16_t present_lightness;
    uint16_t target_lightness;
    uint8_t  remaining_time;
} light_lightness_status_msg_t, light_lightness_linear_status_msg_t;

/** @brief Wire format for the Light Lightness Last / Default Status reply message. */
typedef struct __attribute__((packed)) light_lightness_last_status_msg_s
{
    uint16_t lightness;
} light_lightness_last_status_msg_t, light_lightness_default_status_msg_t;


/** @brief Wire format for the Light Lightness Range Status reply message. */
typedef struct __attribute__((packed)) light_lightness_range_status_msg_s
{
    uint8_t     status_code;
    uint16_t    range_min;
    uint16_t    range_max;
} light_lightness_range_status_msg_t;


/** @brief User callback signature invoked when the Light Lightness actual state changes, reporting the element address and new state. */
typedef void (*model_lightness_user_call_back)(uint16_t element_address, uint16_t state);

#ifdef __cplusplus
};
#endif

#endif /* __MMDL_LIGHT_LIGHTNESS_SR_H__*/
