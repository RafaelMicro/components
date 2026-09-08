/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/** @file
 *
 * @brief BLE l2cap header file.
 *
 */

/**
 * @defgroup ble_l2cap L2CAP
 * @ingroup BLE_group
 * @{
 * @brief Define LE l2cap definitions, structures, and functions.
 * @}
 */

#ifndef __BLE_L2CAP_H__
#define __BLE_L2CAP_H__

/**************************************************************************************************
 *    INCLUDES
 *************************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "ble_api.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**************************************************************************************************
 *    CONSTANTS AND DEFINES
 *************************************************************************************************/



/**************************************************************************************************
 *    TYPEDEFS
 *************************************************************************************************/
/**
 * @defgroup ble_l2cap_evt_type BLE L2CAP Event Type Definition
 * @{
 * @ingroup ble_l2cap
 * @details BLE module event type definition which is indicated the event from BLE stack.
 */
typedef uint8_t ble_l2cap_evt_t;
#define LE_L2CAP_EVT_CREDIT_BASED_CONNECT_REQ_RSP       0x01  /**< LE Credit Based Connection request/response event. Reported both when a peer's incoming connection request has been answered and when the peer's response to a locally initiated @ref ble_cmd_l2cap_chan_connect request is received. See @ref ble_l2cap_credit_based_conn_req_rsp_t. */
#define LE_L2CAP_EVT_DISCONNECT                         0x02  /**< The LE credit-based connection-oriented channel has been disconnected. */
#define LE_L2CAP_EVT_FLOW_CTRL_CREDIT_IND               0x03  /**< The peer has sent an LE Flow Control Credit Ind, granting additional credits so more data can be sent on the channel. See @ref ble_l2cap_flow_ctrl_credit_ind_t. */
#define LE_L2CAP_EVT_DATA_RECEIVED                      0x04  /**< Data has been received on an established LE credit-based channel. See @ref ble_l2cap_data_param_t. */
/** @} */


/** @brief BLE l2cap channel connect parameters.
 * @ingroup ble_l2cap
*/
typedef struct __attribute__((packed))
{
    uint8_t     host_id;   /**< The link's host id used to identify the ACL connection on which the LE credit-based channel is created. */
    uint16_t    spsm;      /**< SPSM (Simplified Protocol/Service Multiplexer) of the L2CAP service on the peer device to connect to. */
    uint16_t    mtu;       /**< Local MTU, in bytes, offered for the new channel. Shall be no smaller than @ref BLE_GATT_ATT_MTU_MIN. */
} ble_l2cap_chan_connect_t;


/** @brief BLE l2cap data send parameters.
 * @ingroup ble_l2cap
*/
typedef struct __attribute__((packed))
{
    uint8_t     host_id;   /**< The link's host id used to identify the ACL connection the data is sent over. */
    uint16_t    dest_id;   /**< Destination CID of the peer's LE credit-based channel, as reported in @ref ble_l2cap_credit_based_conn_req_rsp_t::dest_id. Must match the channel's negotiated destination CID. */
    uint16_t    length;    /**< Length of the data, in bytes. */
    uint8_t     data[];    /**< Data payload to be sent. */
} ble_l2cap_data_send_t;


/** @brief BLE l2cap data event parameters.
 * @ingroup ble_l2cap
*/
typedef struct __attribute__((packed))
{
    uint8_t host_id;    /**< The link's host id that received the data. */
    uint16_t psm;       /**< SPSM of the local LE credit-based channel that the data was received on. */
    uint16_t length;    /**< Length of the received data, in bytes. */
    uint8_t data[];     /**< Received data payload. */
} ble_l2cap_data_param_t;


/** @brief BLE l2cap LE Credit Based Connection request/response event parameters.
 * @ingroup ble_l2cap
*/
typedef struct __attribute__((packed))
{
    uint8_t  host_id;         /**< The link's host id that the LE credit-based channel belongs to. */
    uint16_t dest_id;         /**< Destination CID assigned to this LE credit-based channel by the peer device. Used as @ref ble_l2cap_data_send_t::dest_id when sending data. */
    uint16_t mtu;             /**< Negotiated MTU, in bytes, for this LE credit-based channel. */
    uint16_t mps;             /**< Negotiated MPS (Maximum PDU Size), in bytes, for this LE credit-based channel. */
    uint16_t init_credits;    /**< Initial number of credits granted by the peer for sending data on this channel. */
    uint16_t result;          /**< Result of the LE Credit Based Connection request. 0x0000 indicates the connection was successful; other values indicate the L2CAP connection failure reason (e.g. insufficient resources or unacceptable parameters). */
} ble_l2cap_credit_based_conn_req_rsp_t;


/** @brief BLE l2cap flow control credit indication event parameters.
 * @ingroup ble_l2cap
*/
typedef struct __attribute__((packed))
{
    uint8_t host_id;     /**< The link's host id that the LE credit-based channel belongs to. */
    uint16_t cid;        /**< CID of the LE credit-based channel that the credits apply to. */
    uint16_t credits;    /**< Number of credits granted, allowing that many additional K-frames to be sent on the channel. */
} ble_l2cap_flow_ctrl_credit_ind_t;


/**
 * @brief BLE L2CAP Event Parameters.
 * @ingroup ble_l2cap
 */
typedef struct  __attribute__((packed))
{
    ble_l2cap_evt_t         event;    /**< BLE event @ref ble_l2cap_evt_type "ble_l2cap_evt_t". */
    uint16_t                length;   /**< Length, in bytes, of the valid member in the evt_param union below. */
    union
    {
        ble_l2cap_data_param_t                  l2cap_data_param;
        ble_l2cap_credit_based_conn_req_rsp_t   l2cap_conn_req_rsp;
        ble_l2cap_flow_ctrl_credit_ind_t        l2cap_flow_ctrl_credit_ind;
    } evt_param;                                  /**< Event parameters. */
} ble_l2cap_evt_param_t;



/**************************************************************************************************
 *    MACROS
 *************************************************************************************************/


/**************************************************************************************************
 *    GLOBAL PROTOTYPES
 *************************************************************************************************/
/** @brief Initiate an LE Credit Based Connection request on an existing ACL link.
 *
 *  Sends an LE Credit Based Connection Request to the peer's SPSM over the
 *  L2CAP LE signaling channel of the connection identified by p_param->host_id,
 *  offering the local MTU given by p_param->mtu. The result of the request
 *  (including the negotiated MTU/MPS, initial credits, and destination CID)
 *  is reported later via the @ref LE_L2CAP_EVT_CREDIT_BASED_CONNECT_REQ_RSP
 *  event.
 *
 * @ingroup ble_l2cap
 *
 * @param[in] p_param : a pointer to the l2cap channel connect parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_l2cap_chan_connect(ble_l2cap_chan_connect_t* p_param);

/** @brief Send data on an established LE credit-based connection-oriented channel.
 *
 *  Transmits p_param->length bytes of p_param->data to the peer's channel
 *  identified by p_param->dest_id, over the ACL link identified by
 *  p_param->host_id. The channel must have already been established (as the
 *  initiator via @ref ble_cmd_l2cap_chan_connect or as the acceptor of an
 *  incoming request) and p_param->dest_id must match the channel's negotiated
 *  destination CID.
 *
 * @ingroup ble_l2cap
 *
 * @param[in] p_param : a pointer to the l2cap data send parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_l2cap_data_send(ble_l2cap_data_send_t* p_param);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BLE_L2CAP_H__*/
