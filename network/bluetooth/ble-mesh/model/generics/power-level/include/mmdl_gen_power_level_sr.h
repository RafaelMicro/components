/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

#ifndef __MMDL_GEN_POWERUP_LEVEL_SRV_H__
#define __MMDL_GEN_POWERUP_LEVEL_SRV_H__

#ifdef __cplusplus
extern "C" {
#endif


/** @brief Dispatch an incoming Generic Power Level model message to the matching opcode handler. */
extern void mmdl_generic_power_level_sr_handler(mesh_app_mdl_evt_msg_idc_t *p_evt_msg, ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t is_broadcast);
/** @brief Apply the current Power Level state to sibling OnOff/Level models when a scene is recalled. */
extern void mmdl_generic_power_level_scene_set(ble_mesh_element_param_t *p_current_element);

/** @brief Callback invoked by an extending child model (OnOff/Level/Power OnOff) to update the Power Level state. */
extern void mmdl_generic_power_level_ex_cb(ble_mesh_element_param_t *p_current_element, ble_mesh_model_param_t *p_child_model, general_parameter_t p);
/** @brief Propagate the current Power Level state to the other extended sibling models (OnOff/Level). */
extern void mmdl_generic_power_level_update_extend(ble_mesh_element_param_t *p_current_element, ble_mesh_model_param_t *p_parent_model, ble_mesh_model_param_t *p_child_model);
/** @brief Update the Power OnOff sub-state from an extended (parent) model and publish the change. */
extern void mmdl_generic_power_level_extend_set(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t onopowerup_state);
/** @brief Publish the current Generic Power Level state to the model's configured publish address. */
extern void mmdl_generic_power_level_publish_state(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);

#ifdef __cplusplus
};
#endif

#endif /* __MMDL_GEN_POWERUP_ONOFF_SRV_H__*/
