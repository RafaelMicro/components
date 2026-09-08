/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/** @file
 *
 * @brief BLE extended advertising header file.
 *
 */

/**
 * @defgroup ble_extended_advertising extended Advertising
 * @ingroup BLE_group
 * @{
 * @brief Define BLE extended Advertising definitions, structures, and functions.
 * @}
 */

#ifndef __BLE_EXTENDED_ADVERTISING_H__
#define __BLE_EXTENDED_ADVERTISING_H__

/**************************************************************************************************
 *    INCLUDES
 *************************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "ble_gap.h"
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
 * @defgroup ble_adv_type BLE Advertising Type Definition
 * @{
 * @ingroup ble_extended_advertising
 * @brief  Define the periodic advertising sync transfer mode and the value limits used by the
 *         extended/periodic advertising and periodic advertising sync transfer (PAST) APIs.
 */
typedef uint8_t ble_periodic_adv_mode_type_t;
#define DISABLE_ALL_PERIODIC_ADV_EVENT                   0x00  /**< Do not send periodic advertising sync transfer events for this mode. */
#define SYNC_TRANSFER_EVENT_ONLY                         0x01  /**< Send a periodic advertising sync transfer received event only, no periodic advertising reports. */
#define PERIODIC_ADV_EVENT_WITHOUT_DUPLICATE_FILTER      0x02  /**< Send a sync transfer received event followed by periodic advertising report events, without duplicate filtering. */
#define PERIODIC_ADV_EVENT_WITH_DUPLICATE_FILTER         0x03  /**< Send a sync transfer received event followed by periodic advertising report events, with duplicate filtering enabled. */

#define BLE_PERIODIC_ADV_PKT_SKIP_MAX                    0x01F3  /**< Maximum number of consecutive periodic advertising packets that may be skipped after a successful receive. */
#define BLE_PERIODIC_ADV_SYNC_TIMEOUT_MIN                0x000A  /**< Minimum synchronization timeout for the periodic advertising train. Unit: 10 ms. */
#define BLE_PERIODIC_ADV_SYNC_TIMEOUT_MAX                0x4000  /**< Maximum synchronization timeout for the periodic advertising train. Unit: 10 ms. */

#define BLE_PERIODIC_ADV_RSP_DATA_LEN_MAX                251  /**< Maximum length, in octets, of periodic advertising response data (PAwR). */

#define BLE_PERIODIC_ADV_DATA_LEN_MAX                    252  /**< Maximum length, in octets, of periodic advertising data. */
#define BLE_PERIODIC_ADV_INTERVAL_MIN                    0x0006  /**< Minimum periodic advertising interval. Unit: 1.25 ms. */

#define BLE_PERIODIC_ADV_SUBEVENT_INTERVAL_MIN           0x06  /**< Minimum interval between periodic advertising with responses (PAwR) subevents. Unit: 1.25 ms. */
#define BLE_PERIODIC_ADV_SUBEVENT_NUM_MAX                0x80  /**< Maximum number of subevents in a periodic advertising with responses (PAwR) train. */


#define BLE_EXTENDED_ADV_PRIMARY_ADV_INTERVAL_MIN        0x000020  /**< Minimum primary extended advertising interval. Unit: 0.625 ms. */

#define BLE_EXTENDED_ADV_PRIMARY_ADV_PHY_1M              0x01  /**< Primary extended advertising is transmitted on the LE 1M PHY. */
#define BLE_EXTENDED_ADV_PRIMARY_ADV_PHY_CODED           0x03  /**< Primary extended advertising is transmitted on the LE Coded PHY. */

#define BLE_EXTENDED_ADV_SECONDARY_ADV_PHY_1M            0x01  /**< Secondary extended advertising is transmitted on the LE 1M PHY. */
#define BLE_EXTENDED_ADV_SECONDARY_ADV_PHY_2M            0x02  /**< Secondary extended advertising is transmitted on the LE 2M PHY. */
#define BLE_EXTENDED_ADV_SECONDARY_ADV_PHY_CODED         0x03  /**< Secondary extended advertising is transmitted on the LE Coded PHY. */

#define BLE_EXTENDED_ADV_SID_MAX                         0x0F  /**< Maximum value of the advertising set identifier (SID). */

/** @} */

/**
 * @defgroup ble_adv_event_properties BLE Advertising Event Properties Definition
 * @{
 * @ingroup ble_extended_advertising
 * @details Bitmask values for @ref ble_extended_adv_param_set_t::adv_event_properties describing the
 *          type of extended advertising event (see Bluetooth Core Spec, LE Set Extended Advertising Parameters).
 */
typedef uint16_t adv_event_properties_t;
#define ADV_EVENT_PROPERITES_CONN_ADV                    (0x0001)  /**< Connectable advertising. */
#define ADV_EVENT_PROPERITES_SCAN_ADV                    (0x0002)  /**< Scannable advertising. */
#define ADV_EVENT_PROPERITES_DIRECT_ADV                  (0x0004)  /**< Directed advertising. */
#define ADV_EVENT_PROPERITES_HIGH_DUTY_DIRECT_CONN_ADV   (0x0008)  /**< High duty cycle directed connectable advertising (<= 3.75 ms advertising interval). */
#define ADV_EVENT_PROPERITES_LEGACY_ADV                  (0x0010)  /**< Use a legacy advertising PDU. */
#define ADV_EVENT_PROPERITES_OMIT_ADDR                   (0x0020)  /**< Omit the advertiser's address from all PDUs (anonymous advertising). */
#define ADV_EVENT_PROPERITES_INCLUDE_TX_POWER            (0x0040)  /**< Include TxPower in the extended header of at least one advertising PDU. */
/** @} */

/**
 * @defgroup ble_scan_req_notify BLE Scan Request Notification Enable Definition
 * @{
 * @ingroup ble_extended_advertising
 * @details Controls whether a scan request notification event is generated when the extended
 *          advertising set receives a scan request.
 */
typedef uint8_t scan_req_notify_enable_t;
#define SCAN_REQ_NOTIFY_DISABLE                          (0x00)  /**< Scan request notifications disabled. */
#define SCAN_REQ_NOTIFY_ENABLE                           (0x01)  /**< Scan request notifications enabled. */
/** @} */



/** @brief Default periodic advertising sync transfer (PAST) parameters, applied to future
 *         incoming PAST transfers for connections that have not been given per-connection
 *         parameters via @ref ble_cmd_periodic_adv_sync_transfer_param_set.
 * @ingroup ble_extended_advertising
*/
typedef struct  __attribute__((packed))
{
    /**
     * @ref ble_adv_type "BLE advertising type"
     */
    ble_periodic_adv_mode_type_t      mode;

    /** Number of periodic advertising packets that can be skipped after a successful receive. */
    uint16_t                          skip;

    /** Synchronization timeout for the periodic advertising train. Unit: 10 ms. */
    uint16_t                          sync_timeout;

} ble_default_periodic_adv_sync_transfer_param_t;


/** @brief Periodic advertising sync transfer (PAST) parameters for a specific connection,
 *         applied when this device transfers (or receives, per role) periodic advertising
 *         synchronization information over that link.
 * @ingroup ble_extended_advertising
*/
typedef struct  __attribute__((packed))
{
    /** The link's host ID. The link identified by this host ID must already be connected. */
    uint8_t                           host_id;
    /**
     * @ref ble_adv_type "BLE advertising type"
     */
    ble_periodic_adv_mode_type_t      mode;

    /** Number of periodic advertising packets that can be skipped after a successful receive. */
    uint16_t                          skip;

    /** Synchronization timeout for the periodic advertising train. Unit: 10 ms. */
    uint16_t                          sync_timeout;

} ble_periodic_adv_sync_transfer_param_t;

/** @brief Periodic advertising with responses (PAwR) subevent to synchronize with.
 * @ingroup ble_extended_advertising
*/
typedef struct  __attribute__((packed))
{
    /** The periodic advertising sync handle. */
    uint16_t                         sync_handle;
    /** The subevent index to synchronize with. */
    uint8_t                          subevent;

} ble_periodic_sync_subevent_param_t;

/** @brief Periodic advertising sync terminate parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct  __attribute__((packed))
{
    /** The periodic advertising sync handle to terminate; the sync must currently be active (synced). */
    uint16_t                         sync_handle;

} ble_periodic_advertising_sync_terminate_param_t;

/** @brief Periodic advertising with responses (PAwR) response data set parameters, used by a
 *         synced device to respond to a subevent data request from the periodic advertiser.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_periodic_adv_rsp_data_set_param_s
{
    uint16_t                          sync_handle;       /**< The periodic advertising sync handle this response is sent on. */
    uint16_t                          req_event;         /**< The periodic event counter of the request this response answers. */
    uint8_t                           req_subevent;      /**< The subevent of the request this response answers. */
    uint8_t                           rsp_subevent;      /**< The subevent in which the response is sent. */
    uint8_t                           rsp_slot;          /**< The response slot in which the response is sent. */
    uint8_t                           rsp_data_len;      /**< Length, in octets, of @c rsp_data (max @ref BLE_PERIODIC_ADV_RSP_DATA_LEN_MAX). */
    uint8_t                           rsp_data[];        /**< Response data, @c rsp_data_len octets. */
} ble_periodic_adv_rsp_data_set_param_t;

/** @brief BLE periodic advertising parameter set command parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_periodic_adv_param_set_param_s
{
    uint8_t                           adv_handle;                   /**< Advertising handle identifying the advertising set. */
    adv_event_properties_t            adv_event_properties;         /**< Reserved; not consumed by the current periodic advertising parameter set implementation. */
    uint16_t                          padv_interval_min;            /**< Minimum periodic advertising interval (>= @ref BLE_PERIODIC_ADV_INTERVAL_MIN). Unit: 1.25 ms. */
    uint16_t                          padv_interval_max;            /**< Maximum periodic advertising interval (>= @ref BLE_PERIODIC_ADV_INTERVAL_MIN). Unit: 1.25 ms. */
    uint16_t                          padv_properties;              /**< Periodic advertising properties bitmask (e.g. whether to include TX power). */
    uint8_t                           num_subevents;                /**< number of subevents. */
    uint8_t                           subevent_interval;            /**< interval between subevents. */
    uint8_t                           rsp_slot_delay;          /**< time between adv packet and the first response slot. */
    uint8_t                           rsp_slot_spacing;        /**< time between response slots. */
    uint8_t                           num_rsp_slot;            /**< number of subevent response slots. */
} ble_periodic_adv_param_set_param_t;

/** @brief BLE periodic advertising data set command parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_periodic_adv_data_set_param_s
{
    uint8_t                          adv_handle;        /**< Advertising handle identifying the advertising set. */
    uint8_t                          adv_data_len;      /**< Length, in octets, of @c adv_data (max @ref BLE_PERIODIC_ADV_DATA_LEN_MAX). */
    uint8_t                          adv_data[];        /**< Periodic advertising data, @c adv_data_len octets. */
} ble_periodic_adv_data_set_param_t;

/** @brief Periodic advertising set information transfer command parameters, used to transfer a
 *         periodic advertising set's synchronization information to a connected peer (PAST).
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_periodic_adv_set_info_transfer_set_param_s
{
    uint8_t                          host_id;           /**< The link's host ID; the link must already be connected. */
    uint16_t                         service_data;      /**< Service data value provided to the peer's sync transfer received event. */
    uint8_t                          adv_handle;        /**< Advertising handle of the local periodic advertising set to transfer. */
} ble_periodic_adv_set_info_transfer_set_param_t;

/** @brief BLE periodic advertising enable command parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_periodic_adv_enable_set_param_s
{
    uint8_t                          adv_handle;   /**< Advertising handle identifying the advertising set to enable. */
} ble_periodic_adv_enable_set_param_t;

/** @brief BLE periodic advertising disable command parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_periodic_adv_disable_set_param_s
{
    uint8_t                          adv_handle;   /**< Advertising handle identifying the advertising set to disable. */
} ble_periodic_adv_disable_set_param_t;


/** @brief One subevent entry within a periodic advertising with responses (PAwR) subevent data set request.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) periodic_adv_subevent_param_
{
    uint8_t                          subevent;              /**< Subevent index. */
    uint8_t                          rsp_slot_start;        /**< First response slot to listen to for this subevent. */
    uint8_t                          rsp_slot_count;        /**< Number of response slots to listen to for this subevent. */
    uint8_t                          subevent_data_len;     /**< Length, in octets, of @c subevent_data (max 251). */
    uint8_t                          subevent_data[];       /**< Subevent advertising data, @c subevent_data_len octets. */
} periodic_adv_subevent_param_t;

/** @brief BLE periodic advertising with responses (PAwR) subevent data set command parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_periodic_adv_subevent_data_set_param_s
{
    uint8_t                          adv_handle;       /**< Advertising handle identifying the advertising set. */
    uint8_t                          num_subevents;    /**< Number of @ref periodic_adv_subevent_param_t entries in @c subevents (1 to 15). */
    uint8_t                          subevents[];      /**< Concatenated @ref periodic_adv_subevent_param_t entries, @c num_subevents in total. */
} ble_periodic_adv_subevent_data_set_param_t;

/**
 * @brief BLE Extended Advertising Parameter Set command parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_extended_adv_param_set_s
{
    uint8_t                           adv_handle;                    /**< Advertising handle identifying the advertising set (0 to @ref BLE_MAX_PADV_HANDLE). */
    adv_event_properties_t            adv_event_properties;          /**< @ref ble_adv_event_properties "Advertising event properties" bitmask. */
    uint32_t                          primary_adv_interval_min;      /**< Minimum primary advertising interval (>= @ref BLE_EXTENDED_ADV_PRIMARY_ADV_INTERVAL_MIN). Unit: 0.625 ms. */
    uint32_t                          primary_adv_interval_max;      /**< Maximum primary advertising interval (>= @ref BLE_EXTENDED_ADV_PRIMARY_ADV_INTERVAL_MIN). Unit: 0.625 ms. */
    uint8_t                           primary_adv_ch_map;            /**< @ref ble_adv_channel "Primary advertising channel map" bitmask. */
    uint8_t                           own_address_type;              /**< @ref ble_gap_addr_type "Own address type". */
    uint8_t                           peer_address_type;             /**< @ref ble_gap_addr_type "Peer address type", used when directed advertising or resolving a peer identity. */
    uint8_t                           peer_address[6];               /**< Peer device address, used when directed advertising or resolving a peer identity. */
    uint8_t                           adv_filter_policy;             /**< @ref ble_adv_filter "Advertising filter policy". */
    uint8_t                           primary_adv_phy;               /**< PHY for primary advertising: @ref BLE_EXTENDED_ADV_PRIMARY_ADV_PHY_1M or @ref BLE_EXTENDED_ADV_PRIMARY_ADV_PHY_CODED. */
    uint8_t                           secondary_adv_max_skip;        /**< Maximum number of primary advertising events that can be skipped before sending an AUX_ADV_IND on the secondary channel. */
    uint8_t                           secondary_adv_phy;             /**< PHY for secondary advertising: @ref BLE_EXTENDED_ADV_SECONDARY_ADV_PHY_1M, @ref BLE_EXTENDED_ADV_SECONDARY_ADV_PHY_2M, or @ref BLE_EXTENDED_ADV_SECONDARY_ADV_PHY_CODED. */
    uint8_t                           adv_sid;                       /**< Advertising set identifier (SID), 0 to @ref BLE_EXTENDED_ADV_SID_MAX. */
    scan_req_notify_enable_t          scan_req_notification_enable;  /**< @ref ble_scan_req_notify "Scan request notification enable". */
} ble_extended_adv_param_set_t;


/** @brief BLE extended advertising enable command parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_extended_adv_enable_set_s
{
    uint8_t                  enable;                    /**< 0x01 to start extended advertising, 0x00 to stop it. */
    uint8_t                  adv_handle;                /**< Advertising handle identifying the advertising set. */
    uint16_t                 duration;                  /**< Advertising duration; 0 means advertise until manually disabled. Unit: 10 ms. */
    uint8_t                  max_extended_adv_events;   /**< Maximum number of extended advertising events to send before stopping; 0 means no limit. */
} ble_extended_adv_enable_set_t;

/** @brief BLE extended advertising data set command parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_extended_adv_data_set_s
{
    uint8_t                  adv_handle;       /**< Advertising handle identifying the advertising set. */
    uint8_t                  adv_data_len;     /**< Length, in octets, of @c adv_data. */
    uint8_t                  adv_data[];       /**< Extended advertising data, @c adv_data_len octets. */
} ble_extended_adv_data_set_t;

/** @brief Advertising set random device address set command parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_adv_set_random_address_set_s
{
    uint8_t                  adv_handle;              /**< Advertising handle identifying the advertising set (0 to @ref BLE_MAX_PADV_HANDLE). */
    uint8_t                  addr[BLE_ADDR_LEN];      /**< Random device address to use for this advertising set. */
} ble_adv_set_random_address_set_t;

/**
 * @brief Periodic Advertising Receive Enable Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_set_padv_receive_enable_s
{
    /** @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t     status;

} ble_evt_padv_set_padv_receive_enable_t;

/**
 * @brief Default Periodic Advertising Sync Transfer Parameter Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_set_default_padv_sync_transfer_param_s
{
    /** @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t     status;

} ble_evt_padv_set_default_padv_sync_transfer_param_t;

/**
 * @brief Periodic Advertising Sync Transfer Parameter Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_set_padv_sync_transfer_param_s
{
    /** @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t     status;

} ble_evt_padv_set_padv_sync_transfer_param_t;

/**
 * @brief Periodic Advertising Subevent Data Set Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_set_padv_subevent_data_s
{
    uint8_t     status;         /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t     adv_handle;     /**< Advertising handle identifying the advertising set. */
} ble_evt_padv_set_padv_subevent_data_t;

/**
 * @brief Periodic Advertising Response Data Set Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_set_padv_response_data_s
{
    /** @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t     status;
    uint16_t    sync_handle;    /**< The periodic advertising sync handle the response data was set on. */
} ble_evt_padv_set_padv_response_data_t;

/**
 * @brief Periodic Advertising Sync Transfer Received Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_padv_sync_transfer_received_s
{
    /** @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t     status;
    uint8_t     host_id;                   /**< The link's host ID that received the sync transfer, or @ref BLE_HOSTID_RESERVED. */
    uint16_t    service_data;              /**< Service data. */
    uint16_t    sync_handle;               /**< Sync handle. */
    uint8_t     advertising_sid;            /**< Advertising SID. */
    uint8_t     advertiser_address_type;    /**< Advertiser address type. */
    uint8_t     advertiser_address[6];      /**< Advertiser address. */
    uint8_t     advertiser_phy;             /**< Advertiser PHY. */
    uint16_t    periodic_adv_interval;     /**< Periodic advertising interval. */
    uint8_t     advertiser_clock_accuracy;  /**< Advertiser clock accuracy. */
} ble_evt_padv_padv_sync_transfer_received_t;

/**
 * @brief Periodic Advertising Sync Transfer Received Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_padv_sync_transfer_received_v2_s
{
    /** @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t     status;
    uint8_t     host_id;                   /**< The link's host ID that received the sync transfer, or @ref BLE_HOSTID_RESERVED. */
    uint16_t    service_data;              /**< Service data. */
    uint16_t    sync_handle;               /**< Sync handle. */
    uint8_t     advertising_sid;            /**< Advertising SID. */
    uint8_t     advertiser_address_type;    /**< Advertiser address type. */
    uint8_t     advertiser_address[6];      /**< Advertiser address. */
    uint8_t     advertiser_phy;             /**< Advertiser PHY. */
    uint16_t    periodic_adv_interval;     /**< Periodic advertising interval. */
    uint8_t     advertiser_clock_accuracy;  /**< Advertiser clock accuracy. */
    uint8_t     num_subevents;              /**< Number of subevents. */
    uint8_t     subevent_interval;          /**< Subevent interval. */
    uint8_t     response_slot_delay;        /**< Response slot delay. */
    uint8_t     response_slot_spacing;      /**< Response slot spacing. */
} ble_evt_padv_padv_sync_transfer_received_v2_t;

/**
 * @brief Periodic Advertising Sync Established Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_padv_sync_established_s
{
    /** @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t     status;
    uint16_t    sync_handle;               /**< Sync handle. */
    uint8_t     advertising_sid;            /**< Advertising SID. */
    uint8_t     advertiser_address_type;    /**< Advertiser address type. */
    uint8_t     advertiser_address[6];      /**< Advertiser address. */
    uint8_t     advertiser_phy;             /**< Advertiser PHY. */
    uint16_t    periodic_adv_interval;     /**< Periodic advertising interval. */
    uint8_t     advertiser_clock_accuracy;  /**< Advertiser clock accuracy. */
} ble_evt_padv_padv_sync_established_t;

/**
 * @brief Periodic Advertising Sync Established v2 Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_padv_sync_established_v2_s
{
    /** @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t     status;
    uint16_t    sync_handle;               /**< Sync handle. */
    uint8_t     advertising_sid;            /**< Advertising SID. */
    uint8_t     advertiser_address_type;    /**< Advertiser address type. */
    uint8_t     advertiser_address[6];      /**< Advertiser address. */
    uint8_t     advertiser_phy;             /**< Advertiser PHY. */
    uint16_t    periodic_adv_interval;     /**< Periodic advertising interval. */
    uint8_t     advertiser_clock_accuracy;  /**< Advertiser clock accuracy. */
    uint8_t     num_subevents;              /**< Number of subevents. */
    uint8_t     subevent_interval;          /**< Subevent interval. */
    uint8_t     response_slot_delay;        /**< Response slot delay. */
    uint8_t     response_slot_spacing;      /**< Response slot spacing. */
} ble_evt_padv_padv_sync_established_v2_t;


/**
 * @brief Periodic Advertising Subevent Data Request Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_padv_subevent_data_req_s
{
    uint8_t   adv_handle;                 /**< Advertising handle. */
    uint8_t   subevent_start;             /**< Subevent start. */
    uint8_t   subevent_data_cnt;          /**< Subevent data counter. */
} ble_evt_padv_padv_subevent_data_req_t;

/**
 * @brief One response entry within a Periodic Advertising Response Report event.
 * @ingroup ble_extended_advertising
*/
typedef struct padv_rsp_report_s
{
    uint8_t tx_power;         /**< TX power level of the response, in dBm. */
    uint8_t rssi;             /**< RSSI of the response, in dBm. */
    uint8_t cte_type;         /**< Constant Tone Extension (CTE) type of the response. */
    uint8_t response_slot;    /**< Response slot the response was received in. */
    uint8_t data_status;      /**< Data status (e.g. complete, incomplete, truncated). */
    uint8_t data_length;      /**< Length, in octets, of @c data. */
    uint8_t data[];           /**< Response data, @c data_length octets. */
} padv_rsp_report_t;

/**
 * @brief Periodic Advertising Response Report Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_padv_rsp_report_s
{
    uint8_t   adv_handle;                 /**< Advertising handle. */
    uint8_t   subevent;                   /**< Subevent. */
    uint8_t   tx_status;                  /**< Tx status. */
    uint8_t   num_responses;              /**< Number of responses. */
    padv_rsp_report_t rsp_info[];         /**< Response information */
} ble_evt_padv_padv_rsp_report_t;


/**
 * @brief Set Periodic Sync Subevent Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_set_psync_subevent_s
{
    uint8_t     status;                    /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint16_t    sync_handle;               /**< Sync handle. */
} ble_evt_padv_set_psync_subevent_t;

/**
 * @brief Periodic Advertising Terminate Sync Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_terminate_sync_s
{
    uint8_t     status;   /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
} ble_evt_padv_terminate_sync_t;
/**
 * @brief Advertising Set Terminated Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_adv_set_terminated_s
{
    uint8_t     status;                         /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t     adv_handle;                     /**< Advertising handle identifying the advertising set that terminated. */
    uint16_t    connect_handle;                 /**< Connection handle of the connection created by this advertising set, if any. */
    uint8_t     num_completed_ext_adv_events;   /**< Number of completed extended advertising events. */
} ble_evt_adv_set_terminated_t;

/**
 * @brief Periodic Advertising Report Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_padv_report_s
{
    uint16_t  sync_handle;                /**< Sync handle. */
    int8_t    tx_power;                   /**< tx power level. */
    int8_t    rssi;                       /**< RSSI value. */
    uint8_t   cte_type;                   /**< CTE Type. */
    uint8_t   data_status;                /**< data status. */
    uint8_t   data_length;                /**< data length. */
    uint8_t   data[];                     /**< data. */
} ble_evt_padv_padv_report_t;


/**
 * @brief Periodic Advertising Report v2 Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_padv_report_v2_s
{
    uint16_t  sync_handle;                 /**< Sync handle. */
    int8_t    tx_power;                   /**< tx power level. */
    int8_t    rssi;                       /**< RSSI value. */
    uint8_t   cte_type;                   /**< CTE Type. */
    uint16_t  periodic_evt_cnt;           /**< Periodic Event Counter. */
    uint8_t   subevent;                   /**< Subevent. */
    uint8_t   data_status;                /**< data status. */
    uint8_t   data_length;                /**< data length. */
    uint8_t   data[];                     /**< data. */
} ble_evt_padv_padv_report_v2_t;


/**
 * @brief Periodic Advertising Sync Lost Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_padv_sync_lost_s
{
    uint16_t  sync_handle;                 /**< Sync handle. */
} ble_evt_padv_padv_sync_lost_t;

/**
 * @brief Periodic Advertising Parameters Set Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_padv_params_set_s
{
    uint8_t     status;                   /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t     adv_handle;               /**< advertising handle. */
} ble_evt_padv_padv_params_set_t;

/**
 * @brief Periodic Advertising Data Set Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_padv_data_set_s
{
    uint8_t     status;   /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
} ble_evt_padv_padv_data_set_t;

/**
 * @brief Periodic Advertising Enable Set Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_padv_enable_set_s
{
    uint8_t     status;   /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
} ble_evt_padv_padv_enable_set_t;

/**
 * @brief Periodic Advertising Set Information Transfer Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_padv_padv_info_transfer_set_s
{
    uint8_t     status;    /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t     host_id;   /**< The link's host ID the periodic advertising set information was transferred to. */
} ble_evt_padv_padv_info_transfer_set_t;

/**
 * @brief Extended Advertising Parameters Set Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_extended_adv_params_s
{
    /** @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t     status;
    uint8_t     selected_tx_power;   /**< TX power, in dBm, selected by the Controller for this advertising set (127 if unavailable). */

} ble_evt_extended_adv_params_t;

/**
 * @brief Extended Advertising Enable Set Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_extended_adv_enable_s
{
    /** @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t     status;

} ble_evt_extended_adv_enable_t;

/**
 * @brief Extended Advertising Data Set Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_extended_adv_data_s
{
    /** @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t     status;

} ble_evt_extended_adv_data_t;

/**
 * @brief Advertising Set Random Address Set Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct __attribute__((packed)) ble_evt_adv_set_random_addr_s
{
    /** @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t     status;

} ble_evt_adv_set_random_addr_t;

/**
 * @brief BLE Advertising Event Parameters.
 * @ingroup ble_extended_advertising
*/
typedef struct
{
    union
    {
        ble_evt_adv_set_random_addr_t                         evt_set_random_addr;                   /**< Set advertising set random address event parameters. */
        ble_evt_extended_adv_params_t                         evt_set_extended_adv_params;           /**< Set extended advertising parameters event parameters. */
        ble_evt_extended_adv_enable_t                         evt_set_extended_adv_enable;           /**< Set extended advertising enable event parameters. */
        ble_evt_extended_adv_data_t                           evt_set_extended_adv_data;             /**< Set extended advertising data event parameters. */
        ble_evt_padv_set_padv_receive_enable_t                evt_set_padv_receive_enable;           /**< Set periodic advertising receive enable event parameters. */
        ble_evt_padv_set_padv_sync_transfer_param_t           evt_set_padv_sync_transfer_param;      /**< Set periodic advertising sync transfer parameter event parameters. */
        ble_evt_padv_set_default_padv_sync_transfer_param_t   evt_set_default_padv_sync_transfer_param;  /**< Set default periodic advertising sync transfer parameter event parameters. */
        ble_evt_padv_set_padv_subevent_data_t                 evt_set_padv_subevent_data;            /**< Set periodic advertising subevent data event parameters. */
        ble_evt_padv_set_padv_response_data_t                 evt_set_padv_rsp_data;                 /**< Set periodic advertising response data event parameters. */
        ble_evt_padv_padv_sync_transfer_received_t            evt_padv_sync_transfer_received;       /**< Periodic advertising sync transfer received event parameters. */
        ble_evt_padv_padv_sync_transfer_received_v2_t         evt_padv_sync_transfer_received_v2;    /**< Periodic advertising sync transfer received v2 event parameters. */
        ble_evt_padv_padv_sync_established_t                  evt_padv_sync_established;             /**< Periodic advertising sync established event parameters. */
        ble_evt_padv_padv_sync_established_v2_t               evt_padv_sync_established_v2;          /**< Periodic advertising sync established v2 event parameters. */
        ble_evt_padv_padv_subevent_data_req_t                 evt_padv_subevent_data_req;            /**< Periodic advertising subevent data request event parameters. */
        ble_evt_padv_padv_rsp_report_t                        evt_padv_rsp_report;                   /**< Periodic advertising response report event parameters. */
        ble_evt_padv_set_psync_subevent_t                     evt_set_psync_subevent;                /**< Set periodic sync subevent event parameters. */
        ble_evt_padv_padv_report_t                            evt_padv_report;                       /**< Periodic advertising report event parameters. */
        ble_evt_padv_padv_report_v2_t                         evt_padv_report_v2;                    /**< Periodic advertising report v2 event parameters. */
        ble_evt_padv_padv_sync_lost_t                         evt_padv_sync_lost;                    /**< Periodic advertising sync lost event parameters. */
        ble_evt_padv_padv_params_set_t                        evt_padv_params_set;                   /**< Periodic advertising parameters set event parameters. */
        ble_evt_padv_padv_data_set_t                          evt_padv_data_set;                     /**< Periodic advertising data set event parameters. */
        ble_evt_padv_padv_enable_set_t                        evt_padv_enable_set;                   /**< Periodic advertising enable set event parameters. */
        ble_evt_padv_padv_info_transfer_set_t                 evt_padv_set_info_transfer_set;        /**< Periodic advertising set information transfer event parameters. */
        ble_evt_padv_terminate_sync_t                         evt_padv_sync_terminate;               /**< Periodic advertising sync terminate event parameters. */
        ble_evt_adv_set_terminated_t                          evt_adv_set_terminated;                /**< Advertising set terminated event parameters. */

    } param; /**< Event parameters. */

} ble_evt_periodic_adv_t;


/**************************************************************************************************
 *    MACROS
 *************************************************************************************************/


/**************************************************************************************************
 *    GLOBAL PROTOTYPES
 *************************************************************************************************/
/** @brief Set BLE extended advertising parameters.
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] p_param : a pointer to the extended advertising parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_extended_adv_parameter_set(ble_extended_adv_param_set_t *p_param);

/** @brief Enable or disable BLE extended advertising.
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] host_id : the link's host id, or @ref BLE_HOSTID_RESERVED if not associated with a specific connection.
 * @param[in] p_param : a pointer to the extended advertising enable parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_extended_adv_enable_set(uint8_t host_id, ble_extended_adv_enable_set_t *p_param);

/** @brief Set BLE extended advertising data.
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] p_param : a pointer to the extended advertising data parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_extended_adv_data_set(ble_extended_adv_data_set_t *p_param);

/** @brief Set the random address of a BLE advertising set.
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] p_param : a pointer to the advertising set random address parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_adv_set_random_addr_set(ble_adv_set_random_address_set_t *p_param);

/** @brief Set the default periodic advertising sync transfer (PAST) parameters.
 *
 *  These parameters apply to future PAST transfers for connections that have not been
 *  configured with connection-specific parameters via @ref ble_cmd_periodic_adv_sync_transfer_param_set.
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] p_param : a pointer to the default periodic advertising sync transfer parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_default_periodic_adv_sync_transfer_param_set(ble_default_periodic_adv_sync_transfer_param_t *p_param);

/** @brief Set the periodic advertising sync transfer (PAST) parameters for a specific connection.
 *
 * @ingroup ble_extended_advertising
 *
 * @note The link identified by @c p_param->host_id must already be connected, otherwise
 *       @ref BLE_ERR_INVALID_HOST_ID is returned.
 *
 * @param[in] p_param : a pointer to the periodic advertising sync transfer parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_periodic_adv_sync_transfer_param_set(ble_periodic_adv_sync_transfer_param_t *p_param);

/** @brief Set the subevent that a periodic advertising with responses (PAwR) sync should receive.
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] p_param : a pointer to the periodic sync subevent parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_periodic_sync_subevent_set(ble_periodic_sync_subevent_param_t *p_param);

/** @brief Terminate the periodic advertising sync (stop receiving a periodic advertising train).
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] p_param : a pointer to the periodic advertising sync terminate parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_periodic_advertising_sync_terminate(ble_periodic_advertising_sync_terminate_param_t *p_param);

/** @brief Start receiving a periodic advertising train.
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] sync_handle : the periodic advertising sync handle.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_periodic_adv_receive_enable(uint16_t sync_handle);

/** @brief Stop receiving a periodic advertising train.
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] sync_handle : the periodic advertising sync handle.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_periodic_adv_receive_disable(uint16_t sync_handle);

/** @brief Set BLE periodic advertising response data.
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] p_param : a pointer to the periodic advertising response data parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_periodic_adv_rsp_data_set(ble_periodic_adv_rsp_data_set_param_t *p_param);

/** @brief Set BLE periodic advertising parameters.
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] p_param : a pointer to the periodic advertising parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_periodic_adv_parameter_set(ble_periodic_adv_param_set_param_t *p_param);

/** @brief Start BLE periodic advertising.
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] p_param : a pointer to the periodic advertising enable parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_periodic_adv_enable_set(ble_periodic_adv_enable_set_param_t *p_param);

/** @brief Stop BLE periodic advertising.
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] p_param : a pointer to the periodic advertising disable parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_periodic_adv_disable_set(ble_periodic_adv_disable_set_param_t *p_param);

/** @brief Set BLE periodic advertising data.
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] p_param : a pointer to the periodic advertising data parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_periodic_adv_data_set(ble_periodic_adv_data_set_param_t *p_param);

/** @brief Transfer a BLE periodic advertising set's information to a connected peer.
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] p_param : a pointer to the periodic advertising set information transfer parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_periodic_adv_set_info_transfer_set(ble_periodic_adv_set_info_transfer_set_param_t *p_param);

/** @brief Set BLE periodic advertising subevent data.
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] p_param : a pointer to the periodic advertising subevent data parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_periodic_adv_subevent_data_set(ble_periodic_adv_subevent_data_set_param_t *p_param);

/** @brief BLE advertising events handler.
 *
 * @ingroup ble_extended_advertising
 *
 * @param[in] p_param : a pointer to the event parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_evt_periodic_adv_handler(void *p_param);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BLE_EXTENDED_ADVERTISING_H__*/
