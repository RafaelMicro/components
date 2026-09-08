/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/**
 * @file mmdl_trsp_sr.h
 * @brief Public API of the Rafael vendor Transparent Transport Server model.
 */

#ifndef __MMDL_TRSP_SRV_H__
#define __MMDL_TRSP_SRV_H__

#ifdef __cplusplus
extern "C" {
#endif


/** @brief Dispatch an incoming Transparent Transport model message (Set/Set Unacknowledged) to the appropriate opcode handler. */
extern void mmdl_rafael_trsp_sr_handler(mesh_app_mdl_evt_msg_idc_t *p_evt_msg, ble_mesh_element_param_t *p_element, ble_mesh_model_param_t *p_model, uint8_t is_broadcast);


#ifdef __cplusplus
};
#endif

#endif /* __MMDL_TRSP_SRV_H__*/
