/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

#ifndef __MMDL_GEN_LEVEL_SRV_H__
#define __MMDL_GEN_LEVEL_SRV_H__

#ifdef __cplusplus
extern "C" {
#endif



/** @brief Initialize the Generic Level Server model instance for an element. */
extern void mmdl_generic_level_sr_init(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);
/** @brief Dispatch an incoming Generic Level model message to the matching opcode handler. */
extern void mmdl_generic_level_sr_handler(mesh_app_mdl_evt_msg_idc_t *p_evt_msg, ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t is_broadcast);
/** @brief Update the level state from an extended (parent) model without going through message processing. */
extern void mmdl_generic_level_extend_set(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, int16_t level_state);
/** @brief Publish the current Generic Level state to the model's configured publish address. */
extern void mmdl_generic_level_publish_state(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);

/** @brief Register the Generic Level Server model for the given element. */
void mmdl_generic_level_sr_register(uint16_t element_id, uint16_t element_address);




#ifdef __cplusplus
};
#endif

#endif /* __MMDL_GEN_LEVEL_SRV_H__*/
