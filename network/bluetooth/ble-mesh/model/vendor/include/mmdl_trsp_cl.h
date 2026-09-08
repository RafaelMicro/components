/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/**
 * @file mmdl_trsp_cl.h
 * @brief Public API of the Rafael vendor Transparent Transport Client model.
 */

#ifndef __MMDL_TRSP_CL_H__
#define __MMDL_TRSP_CL_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "mmdl_client.h"
#include "mmdl_trsp_common.h"

/** @brief Dispatch an incoming Transparent Transport model message (Status) to the appropriate opcode handler. */
extern void mmdl_rafael_trsp_cl_handler(mesh_app_mdl_evt_msg_idc_t *p_evt_msg, ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t is_broadcast);
/** @brief Send an acknowledged Transparent Transport Set message with the given raw data payload. */
extern int mmdl_rafael_trsp_send_set(mmdl_transmit_info_t tx_info, raf_trsp_set_msg_t *p_raf_trsp_set_msg);
/** @brief Send an unacknowledged Transparent Transport Set message with the given raw data payload. */
extern int mmdl_rafael_trsp_send_unack_set(mmdl_transmit_info_t tx_info, raf_trsp_set_msg_t *p_raf_trsp_set_msg);

#ifdef __cplusplus
};
#endif

#endif /* __MMDL_TRSP_CL_H__*/
