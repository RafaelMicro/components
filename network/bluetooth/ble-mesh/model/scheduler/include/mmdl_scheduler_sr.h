/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/**
 * @file mmdl_scheduler_sr.h
 * @brief Public API of the BLE Mesh Scheduler Server and Scheduler Setup Server models.
 */

#ifndef __MMDL_SCHEDULER_SRV_H__
#define __MMDL_SCHEDULER_SRV_H__

#ifdef __cplusplus
extern "C" {
#endif


/** @brief Dispatch an incoming Scheduler model message (Get/Action Get) to the appropriate opcode handler. */
extern void mmdl_scheduler_sr_handler(mesh_app_mdl_evt_msg_idc_t *p_evt_msg, ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t in_is_broadcast);
/** @brief Dispatch an incoming Scheduler Setup model message (Action Set/Set Unacknowledged) to the appropriate opcode handler. */
extern void mmdl_scheduler_setup_sr_handler(mesh_app_mdl_evt_msg_idc_t *p_evt_msg, ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t is_broadcast);
/** @brief Extended callback invoked to apply a Generic Power OnOff change triggered via the scheduler. */
extern void mmdl_generic_power_onoff_ex_cb(ble_mesh_element_param_t *current_p_element, ble_mesh_model_param_t *child_p_model, general_parameter_t p);
/** @brief Apply the extended Generic Power OnOff On-Power-Up state to an element/model. */
extern void mmdl_generic_power_onoff_extend_set(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t onopowerup_state);
/** @brief Publish the current Generic Power OnOff state for an element/model. */
extern void mmdl_generic_power_onoff_publish_state(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);
/** @brief Initialize the Scheduler Server model state for an element, resetting all schedule register entries. */
extern void mmdl_scheduler_sr_init(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);

#ifdef __cplusplus
};
#endif

#endif /* __MMDL_SCHEDULER_SRV_H__*/
