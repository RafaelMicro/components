/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/**
 * @file mmdl_light_ctl_sr.h
 * @author Joshua Jean (joshua.jean@rafaelmicro.com)
 * @brief Public API of the BLE Mesh Light CTL server model.
 * @version 0.1
 * @date 2022-07-13
 *
 *
 */


#ifndef __MMDL_LIGHT_CTL_SR_H__
#define __MMDL_LIGHT_CTL_SR_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @brief Initialize the Light CTL server model instance on an element. */
extern void mmdl_light_ctl_sr_init(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);
/** @brief Dispatch an incoming Light CTL model message to the proper opcode handler. */
extern void mmdl_light_ctl_sr_handler(mesh_app_mdl_evt_msg_idc_t *p_evt_msg, ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t is_broadcast);
/** @brief Callback invoked by an extended child model to propagate its state into the Light CTL state. */
extern void mmdl_light_ctl_ex_cb(ble_mesh_element_param_t *p_current_element, ble_mesh_model_param_t *p_child_model, general_parameter_t p);
/** @brief Apply a lightness level pushed down from the extending Light Lightness model. */
extern void mmdl_light_ctl_extend_set(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint16_t lightness_level_state);
/** @brief Publish the current Light CTL status to the model's configured publish address. */
extern void mmdl_light_ctl_publish_state(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);
/** @brief Apply the Light CTL state recalled from a scene and propagate it to extended models. */
extern void mmdl_light_ctl_scene_set(ble_mesh_element_param_t *p_current_element);


#ifdef __cplusplus
};
#endif

#endif /* __MMDL_LIGHT_CTL_SR_H__*/
