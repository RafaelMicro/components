/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/** @file ble_host_ref.h
 *
 * @brief BLE Queue reference definition file.
 *
 */
/**
 * @defgroup ble_host_ref BLE Host Queue Size reference definition
 * @ingroup BLE_group
 * @{
 * @brief Define BLE Host Queue Size reference definitions, structures.
 * @attention 1. The value of the definitions which are defined in this file shall NOT be modified. \n
 * @}
 */
#ifndef __BLE_HOST_REF_H__
#define __BLE_HOST_REF_H__


/**************************************************************************************************
 *    INCLUDES
 *************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Check if defined "BLE_SUPPORT_NUM_CONN_MAX" or show error message. */
#ifndef BLE_SUPPORT_NUM_CONN_MAX
#error "Undefine BLE_SUPPORT_NUM_CONN_MAX."
#endif
/**************************************************************************************************
 *    TYPEDEFS
 *************************************************************************************************/
/** @brief Per-connection state used to reassemble an L2CAP SDU from fragmented HCI ACL data packets.
 * @ingroup ble_host_ref
 * @{
*/
typedef struct
{
    void     *p_acl_data;      /**< Pointer to the message block currently used to reassemble the L2CAP SDU, NULL when no reassembly is in progress for this connection. */
    uint16_t conn_handle;      /**< Connection handle this reassembly buffer is assigned to, INVALID_HANDLE when the entry is free. */
    uint16_t l2cap_pdu_len;    /**< Total length of the L2CAP PDU being reassembled, parsed from the L2CAP length field of the first (start) fragment. */
    uint16_t rcvd_pdu_len;     /**< Number of bytes received so far for the L2CAP PDU currently being reassembled, including the L2CAP header. */
} l2cap_sdus_reassembly_t;
/** @} */

/**************************************************************************************************
 *    CONSTANTS AND DEFINES
 *************************************************************************************************/
/** @ingroup ble_host_ref
 * @{
*/
/** Define maximum connection links for Link Layer. */
#define NUM_LL_LINK                           BLE_SUPPORT_NUM_CONN_MAX

/** Define the minimum queue size for HCI command events. */
#define NUM_QUEUE_HCI_COMMAND_EVENT           8

/** Define the minimum queue size for HCI ACL data TX. */
#define NUM_QUEUE_HCI_ACL_DATA_TX             50

/** Define maximum connection links for Host Layer. */
#define NUM_HOST_LINK                         BLE_SUPPORT_NUM_CONN_MAX

/** Define the minimum queue size for Host to Application events. */
#define NUM_QUEUE_HOST_TO_APP_EVENT           40

/** Define the minimum queue size for Host to HCI ACL data. */
#define NUM_QUEUE_HOST_TO_HCI_ACL_DATA        8

/** Define the minimum queue size for Host RX. */
#define NUM_QUEUE_HOST_RX                     40

/** Define the minimum queue size for Host encryption. */
#define NUM_QUEUE_HOST_ENCRYPT                10

/** Define the size, in bytes, of the per-connection reserved block used for the BLE host command timers. */
#define REF_SIZE_CMDTMR                       60

/**************************************************************************
 * EXTERN DEFINITIONS
 **************************************************************************/
extern uint8_t const MAX_CONN_NO_APP;                                   /**< Define maximum number of BLE connection link for BLE stack. */
extern uint16_t const QUEUE_HCI_COMMAND_EVENT;                          /**< Define the size of the hci command queue for hci task. */
extern uint16_t const QUEUE_HCI_ACL_DATA_TX;                            /**< Define the size of the acl data queue for hci task. */
extern uint16_t const QUEUE_HCI_COMMON;                                 /**< Define the size of the HCI common queue for HCI task. */
extern uint16_t const QUEUE_HOST_TO_APP_EVENT;                          /**< Define the size of application event buffer queue for host task. */
extern uint16_t const QUEUE_HOST_TO_HCI_ACL_DATA;                       /**< Define the size of acl data buffer queue for host task. */
extern uint16_t const QUEUE_HOST_RX;                                    /**< Define the size of the rx queue for host task. */
extern uint16_t const QUEUE_HOST_ENCRYPT;                               /**< Define the size of the host encrypt queue for host task. */
extern uint32_t param_host_timer[NUM_LL_LINK][REF_SIZE_CMDTMR >> 2];    /**< A predefined and reserved block of memory used for the BLE host timers. */
extern l2cap_sdus_reassembly_t l2cap_sdus_reassembly[NUM_LL_LINK];      /**< A predefined and reserved block of memory used for the BLE HCI to reassemble incomplete ACL packets. */
extern uint8_t param_host_identity[NUM_LL_LINK][22];                    /**< A predefined and reserved block of memory used for the BLE identity resolving (IRK/RPA) function. */
extern uint8_t l2cap_identifier[NUM_LL_LINK];                           /**< A predefined and reserved block of memory used for the per-link L2CAP signaling packet identifier. */
extern uint32_t param_l2cap_credit_based[NUM_LL_LINK][5];               /**< A predefined and reserved block of memory used for the per-link BLE L2CAP LE credit-based flow control information. */
/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BLE_HOST_REF_H__ */
