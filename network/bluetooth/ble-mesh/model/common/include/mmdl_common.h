/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */


#ifndef MMDL_COMMON_H
#define MMDL_COMMON_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "FreeRTOS.h"
#include "mesh_api.h"
#include "mmdl_client.h"
#include "mmdl_defs.h"
#include "mmdl_opcodes.h"
#include "pib.h"
#include "queue.h"
#include "util.h"
//#include "mmdl_publish.h"

/** @brief Shared transaction identifier (TID) counter used when originating model set/move messages. */
extern uint8_t tid;

/** @brief Dispatch an incoming mesh model event message to the addressed element(s) (unicast or group/virtual). */
void mmdl_evt_msg_cb(mesh_app_mdl_evt_msg_idc_t* pt_msg_idc);
/** @brief Look up a model instance with the given model ID within an element; returns 1 and outputs it via p_model on success. */
uint32_t search_model(ble_mesh_element_param_t* p_element, uint32_t model_id,
                      ble_mesh_model_param_t** p_model);

/** @brief Check whether an AppKey index is present in a model's key-binding list. */
uint32_t mmdl_model_binding_key_validate(uint16_t appkey_index,
                                         ble_mesh_model_param_t* p_model);
/** @brief Check whether an address matches a model's subscription list or a supported fixed group address. */
uint32_t mmdl_model_subscribe_address_validate(uint16_t subscribe_address,
                                               ble_mesh_model_param_t* p_model);

#ifdef __cplusplus
}
#endif

#endif /* MMDL_COMMON_H */
