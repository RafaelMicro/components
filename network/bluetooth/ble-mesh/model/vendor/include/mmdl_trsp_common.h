/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/**
 * @file mmdl_trsp_common.h
 * @brief Common types, model/opcode IDs and message layouts shared by the Rafael vendor Transparent Transport models.
 */

#ifndef __MMDL_TRSP_COMMON_H__
#define __MMDL_TRSP_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BLE_COMPANY_ID
#define BLE_COMPANY_ID                      0x0864       /**< Rafael Micro. company Id is 0x0864, see Assigned Numbers (https://www.bluetooth.com/specifications/assigned-numbers). */
#endif

#define MMDL_RAFAEL_TRSP_MDL_ID_DEF(id_2B)      ((id_2B)*0x00010000 | (BLE_COMPANY_ID))
#define MMDL_RAFAEL_TRSP_OPCODE_DEF(op_6b)      ((((op_6b)*0x1000000)  | 0xC0000000) | ((BLE_COMPANY_ID*0x10000)&0x00FF0000) | (BLE_COMPANY_ID&0xFF00))

#define MMDL_RAFAEL_TRSP_SR_MDL_ID               MMDL_RAFAEL_TRSP_MDL_ID_DEF(0x0831)
#define MMDL_RAFAEL_TRSP_CL_MDL_ID               MMDL_RAFAEL_TRSP_MDL_ID_DEF(0x0832)
#define MMDL_RAFAEL_TRSP_STATUS_OPCODE           MMDL_RAFAEL_TRSP_OPCODE_DEF(0x00)
#define MMDL_RAFAEL_TRSP_SET_OPCODE              MMDL_RAFAEL_TRSP_OPCODE_DEF(0x01)
#define MMDL_RAFAEL_TRSP_SET_NO_ACK_OPCODE       MMDL_RAFAEL_TRSP_OPCODE_DEF(0x02)


/** @brief Parameters passed to the user callback when a Transparent Transport Set/Status message is received. */
typedef struct  raf_trsp_cb_params_s
{
    uint16_t    dst_addr;
    uint16_t    src_addr;
    uint16_t    appkey_index;
    uint8_t     is_group;
    uint16_t    data_len;
    uint8_t     data[];
} raf_trsp_cb_params_t;

/** @brief Persistent Transparent Transport Server model state: last received raw command buffer. */
typedef struct raf_trsp_state_s
{
    uint16_t    cmd_length;
    uint16_t    dummy;
    uint8_t     data[64];
} raf_trsp_state_t;

/** @brief Payload of the Transparent Transport Set(/Unacknowledged) message: a raw variable-length data blob. */
typedef struct  raf_trsp_set_msg_s
{
    uint16_t    data_len;
    uint8_t     data[];
} raf_trsp_set_msg_t;


/** @brief User callback invoked with the raw payload of a received Transparent Transport message. */
typedef void (*model_rafael_trsp_user_call_back)(raf_trsp_cb_params_t *p_raf_trsp_cb_params);


#ifdef __cplusplus
};
#endif

#endif /* __MMDL_TRSP_COMMON_H__*/
