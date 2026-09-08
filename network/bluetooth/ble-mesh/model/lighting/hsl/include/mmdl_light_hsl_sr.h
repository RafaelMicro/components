/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/**
 * @file mmdl_light_hsl_sr.h
 * @author Joshua Jean (joshua.jean@rafaelmicro.com)
 * @brief Public API of the BLE Mesh Light HSL server model and its Hue/Saturation sub-models.
 * @version 0.1
 * @date 2022-07-13
 *
 *
 */

#ifndef __MMDL_LIGHT_HSL_SR_H__
#define __MMDL_LIGHT_HSL_SR_H__

#ifdef __cplusplus
extern "C"
{
#endif



/* declartion for HSL model */
/** @brief Initialize the Light HSL server model instance on an element. */
extern void mmdl_light_hsl_sr_init(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);
/** @brief Dispatch an incoming Light HSL model message to the proper opcode handler. */
extern void mmdl_light_hsl_sr_handler(mesh_app_mdl_evt_msg_idc_t *p_evt_msg, ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t is_broadcast);
/** @brief Callback invoked by an extended child model to propagate its state into the Light HSL state. */
extern void mmdl_light_hsl_ex_cb(ble_mesh_element_param_t *p_current_element, ble_mesh_model_param_t *p_child_model, general_parameter_t p);
/** @brief Publish the current Light HSL status to the model's configured publish address. */
extern void mmdl_light_hsl_publish_state(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);

/* declartion for HUE model */
/** @brief Initialize the Light HSL Hue server model instance on an element. */
extern void mmdl_light_hsl_hue_sr_init(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);
/** @brief Dispatch an incoming Light HSL Hue message to the proper opcode handler. */
extern void mmdl_light_hsl_hue_sr_handler(mesh_app_mdl_evt_msg_idc_t *p_evt_msg, ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t is_broadcast);
/** @brief Callback invoked by the extended Generic Level model to propagate its state into the hue state. */
extern void mmdl_light_hsl_hue_ex_cb(ble_mesh_element_param_t *p_current_element, ble_mesh_model_param_t *p_child_model, general_parameter_t p);
/** @brief Publish the current Light HSL Hue status to the model's configured publish address. */
extern void mmdl_light_hsl_hue_publish_state(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);


/* declartion for saturation model */
/** @brief Initialize the Light HSL Saturation server model instance on an element. */
extern void mmdl_light_hsl_sat_sr_init(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);
/** @brief Dispatch an incoming Light HSL Saturation message to the proper opcode handler. */
extern void mmdl_light_hsl_sat_sr_handler(mesh_app_mdl_evt_msg_idc_t *p_evt_msg, ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t is_broadcast);
/** @brief Callback invoked by the extended Generic Level model to propagate its state into the saturation state. */
extern void mmdl_light_hsl_sat_ex_cb(ble_mesh_element_param_t *p_current_element, ble_mesh_model_param_t *p_child_model, general_parameter_t p);
/** @brief Publish the current Light HSL Saturation status to the model's configured publish address. */
extern void mmdl_light_hsl_sat_publish_state(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);



#ifdef __cplusplus
};
#endif

#endif /* __MMDL_LIGHT_HSL_SR_H__*/
