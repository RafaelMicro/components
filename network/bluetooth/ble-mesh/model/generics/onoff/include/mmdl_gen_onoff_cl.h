/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

#ifndef __MMDL_GEN_ONOFF_CL_H__
#define __MMDL_GEN_ONOFF_CL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "mmdl_client.h"
#include "mmdl_gen_onoff_common.h"

/** @brief Initialize the Generic OnOff Client model instance for an element. */
extern void mmdl_generic_onoff_cl_init(ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model);
/** @brief Dispatch an incoming Generic OnOff model message (e.g. Status) to the matching opcode handler. */
extern void mmdl_generic_onoff_cl_handler(mesh_app_mdl_evt_msg_idc_t *p_evt_msg, ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t is_broadcast);
/** @brief Send an acknowledged Generic OnOff Set message to the given destination. */
extern void mmdl_generic_onoff_send_set(mmdl_transmit_info_t tx_info, gen_on_off_set_msg_t *p_onoff_set);
/** @brief Send an unacknowledged Generic OnOff Set message to the given destination. */
extern void mmdl_generic_onoff_send_unack_set(mmdl_transmit_info_t tx_info, gen_on_off_set_msg_t *p_onoff_set);


#ifdef __cplusplus
};
#endif

#endif /* __MMDL_GEN_ONOFF_CL_H__*/
