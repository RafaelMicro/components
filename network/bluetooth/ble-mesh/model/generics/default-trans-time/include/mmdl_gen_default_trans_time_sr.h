/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

#ifndef __MMDL_GEN_DEFAULT_TRANS_TIME_SRV_H__
#define __MMDL_GEN_DEFAULT_TRANS_TIME_SRV_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Dispatch an incoming Generic Default Transition Time model message to the matching opcode handler. */
extern void mmdl_generic_default_trans_time_sr_handler(mesh_app_mdl_evt_msg_idc_t *p_evt_msg, ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t is_broadcast);
/** @brief Update the default transition time state from an extended (parent) model and publish the change. */
extern void mmdl_generic_default_trans_time_extend_set(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t transition_time);
/** @brief Publish the current Generic Default Transition Time state to the model's configured publish address. */
extern void mmdl_generic_default_trans_time_publish_state(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);

#ifdef __cplusplus
};
#endif

#endif /* __MMDL_GEN_DEFAULT_TRANS_TIME_SRV_H__*/
