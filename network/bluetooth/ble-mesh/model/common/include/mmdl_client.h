/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */


#ifndef MMDL_CLIENT_H
#define MMDL_CLIENT_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"
#include "mesh_api.h"
#include "pib.h"
#include "mmdl_opcodes.h"
#include "mmdl_defs.h"

/** @brief Build and send a model client access message with the given opcode/parameters to the mesh stack. */
void mmdl_client_send(uint16_t dst_addr, uint16_t src_addr, uint32_t opcode, uint16_t key_index, uint16_t param_len, uint8_t *p_param);

/** @brief Addressing/key context (destination, source and AppKey index) used when transmitting a model message. */
typedef struct  mmdl_transmit_info_s
{
    uint16_t    dst_addr;
    uint16_t    src_addr;
    uint16_t    appkey_index;
} mmdl_transmit_info_t;

#ifdef __cplusplus
}
#endif

#endif /* MMDL_CLIENT_H */
