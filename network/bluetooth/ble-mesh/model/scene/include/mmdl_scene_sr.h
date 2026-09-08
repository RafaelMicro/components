/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/**
 * @file mmdl_scene_sr.h
 * @author Joshua Jean (joshua.jean@rafaelmicro.com)
 * @brief Public API of the BLE Mesh Scene Server model.
 * @version 0.1
 * @date 2022-07-27
 *
 *
 */


#ifndef __MMDL_SCENE_SR_H__
#define __MMDL_SCENE_SR_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief Erase all persisted scene data for every element from flash. */
extern void scene_info_reset(void);
/** @brief Initialize the Scene Server model state for an element, loading any stored scene data from flash. */
extern void mmdl_scene_sr_init(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);
/** @brief Dispatch an incoming Scene model message to the appropriate opcode handler. */
extern void mmdl_scene_sr_handler(mesh_app_mdl_evt_msg_idc_t *p_evt_msg, ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t is_broadcast);

#ifdef __cplusplus
};
#endif

#endif /* __MMDL_SCENE_SR_H__*/

