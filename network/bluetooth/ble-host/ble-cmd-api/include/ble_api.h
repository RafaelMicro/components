/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/** @file ble_api.h
 *
 * @brief BLE API header file.
 *
 */

/**
 * @defgroup ble_api BLE API Definition
 * @ingroup BLE_group
 * @{
 * @brief Define BLE API definitions, structures, and functions.
 * @}
 */
#ifndef __BLE_API_H__
#define __BLE_API_H__

/**************************************************************************************************
 *    INCLUDES
 *************************************************************************************************/
#include <stdint.h>
#include "ble_hci_error.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**************************************************************************************************
 *    TYPEDEFS
 *************************************************************************************************/



/** @brief BLE API return/error code definitions.
 * @ingroup ble_api
*/
typedef enum
{
    BLE_ERR_L2CAP_DATA_DEST_ID_UNMATCH    = -29,  /**< BLE L2CAP data destination id does not match. */
    BLE_ERR_L2CAP_DATA_CHANNEL_NOT_EXIST  = -28,  /**< BLE L2CAP data channel does not exist. */
    BLE_ERR_RESOURCE_NOT_ENOUGH           = -27,  /**< BLE resource is not enough. */
    BLE_ERR_HCI_TX_DATA_QUEUE_FULL        = -26,  /**< BLE HCI TX data queue full. */
    BLE_ERR_HCI_TX_CMD_QUEUE_FULL         = -25,  /**< BLE HCI TX command queue full. */
    BLE_ERR_SEQUENTIAL_PROTOCOL_VIOLATION = -24,  /**< Detected a sequential protocol violation. Usually happens when another GATT request is already in progress; please wait and retry. */
    BLE_ERR_DB_PARSING_IN_PROGRESS        = -23,  /**< Host peripheral database parsing is still in progress. */
    BLE_ERR_INVALID_HANDLE                = -22,  /**< Invalid BLE handle. */
    BLE_ERR_INVALID_HOST_ID               = -21,  /**< Invalid Host ID. */
    BLE_ERR_CMD_NOT_SUPPORTED             = -20,  /**< Command not supported. */
    BLE_ERR_INVALID_PARAMETER             = -19,  /**< Invalid parameter. */
    BLE_ERR_INVALID_STATE                 = -18,  /**< Invalid state. */
    BLE_ERR_TIMER_OP                      = -17,  /**< BLE software timer operation (e.g. start/stop) failed. */
    BLE_ERR_ALLOC_MEMORY_FAIL             = -16,  /**< Memory allocation fail. */
    BLE_ERR_RECVFROM_LEN_NOT_ENOUGH       = -15,  /**< RECVFROM length error. */
    BLE_ERR_RECVFROM_FAIL                 = -14,  /**< RECVFROM fail. */
    BLE_ERR_RECVFROM_NO_DATA              = -13,  /**< RECVFROM no data. */
    BLE_ERR_RECVFROM_POINTER_NULL         = -12,  /**< RECVFROM Pointer NULL. */
    BLE_ERR_SENDTO_FAIL                   = -11,  /**< SENDTO fail. */
    BLE_ERR_SENDTO_POINTER_NULL           = -10,  /**< SENDTO Pointer NULL. */
    BLE_BUSY                              = -9,   /**< Busy. */
    BLE_ERR_WRONG_CONFIG                  = -8,   /**< Wrong configuration. */
    BLE_ERR_SEMAPHORE_MALLOC_FAIL         = -7,   /**< Semaphore malloc fail. */
    BLE_ERR_THREAD_MALLOC_FAIL            = -6,   /**< Thread malloc fail. */
    BLE_ERR_QUEUE_MALLOC_FAIL             = -5,   /**< Queue malloc fail. */
    BLE_ERR_DATA_MALLOC_FAIL              = -4,   /**< Data malloc fail. */
    BLE_ERR_DUPLICATE_INIT                = -3,   /**< Duplicate init. */
    BLE_ERR_NOT_INIT                      = -2,   /**< Not initial. */
    BLE_ERR_UNKNOW_TYPE                   = -1,   /**< Unknown type. */
    BLE_ERR_OK                            = 0,    /**< Success. */
} ble_err_t;


/** @brief BLE GATT data-send type, used to select the GATT operation performed by @ref ble_svcs_data_send.
 * @ingroup ble_api
 */
typedef enum
{
    //====================================================================
    //     BLE GATT MAPPING
    //====================================================================
    TYPE_BLE_GATT_START,  /**< Start marker of the BLE GATT data-send type range (alias of @ref TYPE_BLE_GATT_READ_RSP, value 0). Not a valid data-send type by itself. */

    /** @brief BLE GATT Read Response.
     *  @par   none
     *
     *  @attention Only supported if GATT role is @ref BLE_GATT_ROLE_SERVER.
     *  @note The read response is sent in reply to a received Read Request and contains the value of the attribute that has been read.
     *  @param @ref ble_gatt_data_param_t
     */
    TYPE_BLE_GATT_READ_RSP = TYPE_BLE_GATT_START,

    /** @brief BLE GATT Read By Type Response.
     *  @par   none
     *
     *  @attention Only supported if GATT role is @ref BLE_GATT_ROLE_SERVER.
     *  @note The read by type response is sent in reply to a received Read By Type Request and contains the handle number and value of the attribute that has been read.
     *  @param @ref ble_gatt_data_param_t
     */
    TYPE_BLE_GATT_READ_BY_TYPE_RSP,

    /** @brief BLE GATT Read Blob Response.
     *  @par   none
     *
     *  @attention Only supported if GATT role is @ref BLE_GATT_ROLE_SERVER.
     *  @note The read blob response is sent in reply to a received Read Blob Request and contains the value of the attribute that has been read.
     *  @param @ref ble_gatt_data_param_t
     */
    TYPE_BLE_GATT_READ_BLOB_RSP,

    /** @brief BLE GATT notification.
     *  @par   none
     *
     *  @attention Only supported if GATT role is @ref BLE_GATT_ROLE_SERVER.
     *  @note When a server is configured to notify a Characteristic Value to a client without the acknowledgment that the notification was successfully received.
     *  @param @ref ble_gatt_data_param_t
     */
    TYPE_BLE_GATT_NOTIFICATION,

    /** @brief BLE GATT indication.
     *  @par   none
     *
     *  @attention Only supported if GATT role is @ref BLE_GATT_ROLE_SERVER.
     *  @note When a server is configured to indicate a Characteristic Value to a client and expects the indication was successfully received.
     *  @param @ref ble_gatt_data_param_t
     */
    TYPE_BLE_GATT_INDICATION,

    /** @brief BLE GATT Write Request.
     *  @par   none
     *
     *  @attention Only supported if GATT role is @ref BLE_GATT_ROLE_CLIENT.
     *  @note The Write Request is used to request the server to write the value of an attribute and acknowledge that this has been achieved in a Write Response. \n
     *        A Write Response shall be sent by the server if the write of the Characteristic Value succeeded.
     *  @param @ref ble_gatt_data_param_t
     */
    TYPE_BLE_GATT_WRITE_REQ,

    /** @brief BLE GATT Write Command.
     *  @par   none
     *
     *  @attention Only supported if GATT role is @ref BLE_GATT_ROLE_CLIENT.
     *  @note Write a Characteristic Value to a server when the client knows the Characteristic Value Handle \n
     *        and the client does not need an acknowledgment that the write was successfully performed.
     *  @param @ref ble_gatt_data_param_t
     */
    TYPE_BLE_GATT_WRITE_CMD,

    //====================================================================
    //     END
    //====================================================================
    TYPE_BLE_API_MAX,     /**< End marker / number of valid @ref ble_api_type_t values. Not a valid data-send type. */

} ble_api_type_t;


/** @brief BLE host-to-application queue event type.
 * @details Internal tag used by the BLE host task to classify each message it posts to the
 *          host-to-application event queue, so it knows which application callback registered
 *          via @c ble_host_callback_set() (declared in ble_host_cmd.h) the message's parameter
 *          should be dispatched to.
 * @note This is a different type from @c ble_app_event_t (also declared in ble_host_cmd.h), which
 *       is the value passed as the argument of @c ble_host_callback_set() to select which
 *       callback (general event, service event, or L2CAP data) is being registered. Both
 *       @ref BLE_APP_RETURN_PARAMETER_EVENT and @ref BLE_APP_GENERAL_EVENT are delivered to the
 *       callback registered for the general-event category.
 * @ingroup ble_api
 */
typedef enum
{
    BLE_APP_RETURN_PARAMETER_EVENT,   /**< Return (completion) parameter of a previously issued BLE command; delivered to the general-event callback. */
    BLE_APP_GENERAL_EVENT,            /**< General BLE event (e.g. GAP/HCI asynchronous event); delivered to the general-event callback. */
    BLE_APP_SERVICE_EVENT,            /**< GATT service (attribute) event/data; delivered to the service-event callback. */
    BLE_APP_L2CAP_EVENT,              /**< L2CAP connection-oriented channel data; delivered to the L2CAP-event callback. */
} ble_event_t;


/** @brief Generic type-length-value (TLV) container used to carry an event's or request's parameter data
 *         (for example, through an application message queue).
 * @ingroup ble_api
 */
typedef struct
{
    uint16_t    type;       /**< Payload identifier: defined by each module. */
    uint16_t    length;     /**< Payload length: the length of the payload data, in bytes. */
    uint8_t     value[];    /**< Payload data. */
} ble_tlv_t;


/** @brief BLE host FreeRTOS task priority configuration, passed to @ref ble_host_stack_init.
 * @ingroup ble_api
 */
typedef struct
{
    uint8_t     hci_tx_level;       /**< Bluetooth LE task priority: HCI TX task level. */
    uint8_t     ble_host_level;     /**< Bluetooth LE task priority: host task level. */
} ble_task_priority_t;





/**************************************************************************************************
 *    GLOBAL PROTOTYPES
 *************************************************************************************************/

/** @brief Set BLE host stack initialization.
 *
 * @ingroup ble_api
 *
 * @param[in] p_priority : a pointer to the task priority configuration.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
int ble_host_stack_init(ble_task_priority_t* p_priority);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BLE_API_H__*/
