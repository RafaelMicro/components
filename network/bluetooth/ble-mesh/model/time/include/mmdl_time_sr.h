/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/**
 * @file mmdl_time_sr.h
 * @brief Public API of the BLE Mesh Time Server and Time Setup Server models.
 */

#ifndef __MMDL_TIME_SRV_H__
#define __MMDL_TIME_SRV_H__

#ifdef __cplusplus
extern "C" {
#endif


/** @brief Dispatch an incoming Time model message (Get/Status/Timezone Get/Timedelta Get) to the appropriate opcode handler. */
extern void mmdl_time_sr_handler(mesh_app_mdl_evt_msg_idc_t *p_evt_msg, ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t is_broadcast);
/** @brief Dispatch an incoming Time Setup model message (Set/Timezone Set/Timedelta Set/Timerole Get/Set) to the appropriate opcode handler. */
extern void mmdl_time_setup_sr_handler(mesh_app_mdl_evt_msg_idc_t *p_evt_msg, ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t is_broadcast);
/** @brief Extended callback invoked to apply a Generic Power OnOff change triggered via the Time model. */
extern void mmdl_generic_power_onoff_ex_cb(ble_mesh_element_param_t *p_current_element, ble_mesh_model_param_t *p_child_model, general_parameter_t p);
/** @brief Apply the extended Generic Power OnOff On-Power-Up state to an element/model. */
extern void mmdl_generic_power_onoff_extend_set(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t onopowerup_state);
/** @brief Publish the current Generic Power OnOff state for an element/model. */
extern void mmdl_generic_power_onoff_publish_state(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);
/** @brief Initialize the Time Server model state for an element and start the RTC-driven time base. */
extern void mmdl_time_sr_init(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);
/** @brief Set the Time model's current time from a user-supplied UTC time and time zone (hours offset). */
extern void mmdl_time_UTC_set_user(rtc_time_t current_time, int8_t time_zone, ble_mesh_model_param_t *p_model);
/** @brief Recompute and apply the RTC UTC time from the current TAI seconds state. */
extern void mmdl_time_TAI_to_UTC_update(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);
/** @brief Recompute the TAI seconds state from the current RTC UTC time. */
extern void mmdl_time_UTC_to_TAI_update(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);

#ifdef __cplusplus
};
#endif

#endif /* __MMDL_TIME_SRV_H__*/
