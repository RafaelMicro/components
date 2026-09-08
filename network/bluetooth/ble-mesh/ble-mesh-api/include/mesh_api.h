/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/** @file mesh_api.h
 *
 * @brief BLE Mesh stack API header file.
 *
 */
/**
 * @defgroup mesh_api Mesh API
 * @ingroup BLE_group
 * @{
 * @brief Define BLE Mesh stack definitions, structures, and functions.
 * @}
 */
#ifndef __MESH_API_H__
#define __MESH_API_H__

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
//                Include (Better to prevent)
//=============================================================================
#include "stdint.h"
#include "stdbool.h"
#include "ble_api.h"

/** @brief Mesh stack event indication callback prototype.
 * @ingroup mesh_api
 */
typedef ble_err_t    (pf_mesh_evt_indication)(void *p_param);
extern pf_mesh_evt_indication *pf_app_indication;      /**< Application event indication callback registered by @ref mesh_stack_init.*/
//=============================================================================
//                Private ENUM
//=============================================================================
/** @brief Mesh TLV message type definition, used as @ref mesh_tlv_t "mesh_tlv_t.type" for the request/confirm/indication exchanged with the mesh stack.
 * @ingroup mesh_api
 */
typedef enum MESH_API_TYPE
{
    TYPE_MESH_API_START                                     = 1,      /**< Start of the mesh API message type range.*/

    TYPE_MESH_PROV_START_REQ = TYPE_MESH_API_START,                   /**< Request: start provisioning.*/
    TYPE_MESH_PROV_STOP_REQ,                                          /**< Request: stop provisioning.*/
    TYPE_MESH_PROV_SCAN_REQ,                                          /**< Request: scan for unprovisioned devices.*/
    TYPE_MESH_PROV_SEL_REQ,                                           /**< Request: select an unprovisioned device.*/

    TYPE_MESH_DEVICE_NAME_SET_REQ,                                    /**< Request: set the local mesh device name.*/

    TYPE_MESH_PROXY_ENABLE_REQ,                                       /**< Request: enable the proxy service.*/
    TYPE_MESH_PROXY_DISABLE_REQ,                                      /**< Request: disable the proxy service.*/

    TYPE_MESH_BLE_TRSPS_CONNECT_CREATE_REQ,                           /**< Request: create the BLE transparent service connection.*/
    TYPE_MESH_BLE_TRSPS_CONNECT_CANCEL_REQ,                           /**< Request: cancel the BLE transparent service connection.*/
    TYPE_MESH_BLE_TRSPS_DATA_SET_REQ,                                 /**< Request: send data over the BLE transparent service.*/

    TYPE_MESH_START_SCAN_UNPROV_DEVICE_REQ,                           /**< Request: start scanning for unprovisioned devices.*/
    TYPE_MESH_STOP_SCAN_UNPROV_DEVICE_REQ,                            /**< Request: stop scanning for unprovisioned devices.*/

    TYPE_MESH_LINK_OPEN_UNPROV_DEVICE_REQ,                            /**< Request: open the provisioning link to an unprovisioned device.*/

    TYPE_MESH_CFG_MDL_EVT_MSG_REQ,                                    /**< Request: send a Configuration Model message.*/

    TYPE_MESH_APP_MDL_REG_REQ,                                        /**< Request: register an application model.*/
    TYPE_MESH_APP_MDL_EVT_MSG_REQ,                                    /**< Request: send an application model message.*/

    TYPE_MESH_CMD_REQ                                       = 0x099,  /**< Request: mesh stack command (see @ref mesh_cmd_t).*/

    TYPE_MESH_PROV_START_CFM                                = 0x100,  /**< Confirm: provisioning start result.*/
    TYPE_MESH_PROV_SCAN_CFM,                                          /**< Confirm: unprovisioned device scan result.*/
    TYPE_MESH_PROV_SEL_CFM,                                           /**< Confirm: unprovisioned device selection result.*/

    TYPE_MESH_PROV_SCAN_IDC                                 = 0x200,  /**< Indication: unprovisioned device found during scan.*/
    TYPE_MESH_PROV_COMPLETE_IDC,                                      /**< Indication: provisioning link/procedure state change.*/
    TYPE_MESH_NODE_RESET_IDC,                                         /**< Indication: node has been reset.*/
    TYPE_MESH_UNPROV_DEVICE_IDC,                                      /**< Indication: unprovisioned device report.*/
    TYPE_MESH_PROVISION_COMPLETE_IDC,                                 /**< Indication: provisioning procedure completed.*/

    TYPE_MESH_PROV_ADV_ENABLED_IDC,                                   /**< Indication: provisioning advertising enabled.*/
    TYPE_MESH_PROV_ADV_DISABLED_IDC,                                  /**< Indication: provisioning advertising disabled.*/
    TYPE_MESH_PROXY_ENABLE_IDC,                                       /**< Indication: proxy service enabled.*/
    TYPE_MESH_PROXY_DISABLE_IDC,                                      /**< Indication: proxy service disabled.*/

    TYPE_MESH_BLE_TRSPS_CONNECT_CREATE_IDC,                           /**< Indication: BLE transparent service connection created.*/
    TYPE_MESH_BLE_TRSPS_CONNECT_CANCEL_IDC,                           /**< Indication: BLE transparent service connection canceled.*/
    TYPE_MESH_BLE_TRSPS_CONNECTED_IDC,                                /**< Indication: BLE transparent service connected.*/
    TYPE_MESH_BLE_TRSPS_DISCONNECTED_IDC,                             /**< Indication: BLE transparent service disconnected.*/
    TYPE_MESH_FRIEND_ESTABLISED_IDC,                                  /**< Indication: friendship established (see @ref mesh_friend_established_idc_t).*/
    TYPE_MESH_FRIEND_TERMINATED_IDC,                                  /**< Indication: friendship terminated (see @ref mesh_friend_terminated_idc_t).*/

    TYPE_MESH_APP_MDL_EVT_MSG_IDC                           = 0x300,  /**< Indication: application model message received.*/
    TYPE_MESH_CFG_MDL_EVT_MSG_IDC,                                    /**< Indication: Configuration Model message received.*/
    TYPE_MESH_CFG_MDL_APP_BIND_IDC,                                   /**< Indication: application key bound to a model.*/

    TYPE_MESH_BLE_SVC_TRSPS_WRITE_IDC                       = 0x400,  /**< Indication: BLE transparent service write received.*/
} mesh_api_type_t;


//=============================================================================
//                Private Definitions of const value
//=============================================================================

/** @brief Mesh stack task priority configuration.
 * @ingroup mesh_api
 */
typedef struct
{
    uint8_t     bearer_level;       /**< Bluetooth LE task PRIORITY : bearer level.*/
    uint8_t     mesh_level;         /**< Bluetooth LE task PRIORITY : ble mesh level.*/
} mesh_task_priority_t;

/** @brief Mesh stack command type, used with @ref TYPE_MESH_CMD_REQ.
 * @ingroup mesh_api
 */
typedef enum MESH_CMD_TYPE
{
    MESH_CMD_MIB_COUNTER = 0,      /**< Read the MIB counter.*/
    MESH_CMD_MIB_COUNTER_CLEAR,    /**< Clear the MIB counter.*/
    MESH_CMD_SYSLOG_INFO,          /**< Read the mesh stack system log information.*/
    MESH_CMD_MAX,                  /**< End of the mesh command type range.*/
} mesh_cmd_t;


/** @brief Mesh stack status/error code.
 * @ingroup mesh_api
 */
typedef enum
{
    MESH_ERR_ACK_TIMOUT              = -24,   /**< Acknowledgement timeout.*/
    MESH_ERR_NOT_FOUND               = -23,   /**< Requested item was not found.*/
    MESH_ERR_DUPLICATE_ADDR          = -22,   /**< Duplicate address.*/
    MESH_ERR_NO_MEM                  = -21,   /**< Out of memory.*/
    MESH_ERR_INVALID_PARAM           = -20,   /**< Invalid parameter.*/
    MESH_ERR_INVALID_ADDR            = -19,   /**< Invalid address.*/
    MESH_ERR_INVALID_LENGTH          = -18,   /**< Invalid length.*/
    MESH_ERR_NULL                    = -17,   /**< NULL pointer.*/
    MESH_ERR_BUSY                    = -16,   /**< Mesh stack is busy.*/
    MESH_ERR_TIMER_OP                = -15,   /**< Timer operation failed.*/
    MESH_ERR_ALLOC_MEMORY_FAIL       = -14,   /**< Memory allocation failed.*/
    MESH_ERR_RECVFROM_LEN_NOT_ENOUGH = -13,   /**< Received message length is not enough.*/
    MESH_ERR_RECVFROM_FAIL           = -12,   /**< Failed to receive the message.*/
    MESH_ERR_SENDTO_FAIL             = -11,   /**< Failed to send the message.*/
    MESH_ERR_SENDTO_POINTER_NULL     = -10,   /**< The message pointer to send is NULL.*/
    MESH_ERR_APP_KEY_NOT_FOUND       = -9,    /**< Application key was not found.*/
    MESH_ERR_WRONG_CONFIG            = -8,    /**< Wrong configuration.*/
    MESH_ERR_SEMAPHORE_MALLOC_FAIL   = -7,    /**< Semaphore allocation failed.*/
    MESH_ERR_QUEUE_MALLOC_FAIL       = -6,    /**< Queue allocation failed.*/
    MESH_ERR_DATA_MALLOC_FAIL        = -5,    /**< Data allocation failed.*/
    MESH_ERR_DUPLICATE_INIT          = -4,    /**< Mesh stack has already been initialized.*/
    MESH_ERR_NOT_INIT                = -3,    /**< Mesh stack has not been initialized.*/
    MESH_ERR_UNKNOW_TYPE             = -2,    /**< Unknown message type.*/
    MESH_ERR_RESULT_WAITING          = -1,    /**< Result is pending.*/
    MESH_SUCCESS                     = 0,     /**< Success.*/
} mesh_status_t;


/** @brief Friendship termination reason, used by @ref mesh_friend_terminated_idc_t.
 * @ingroup mesh_api
 */
typedef enum
{
    MESH_FRIEND_TERMINATED_REASON_POLL_TIMEOUT, /**< No response from the LPN within the Poll Timeout. */
    MESH_FRIEND_TERMINATED_REASON_NEW_FRIEND    /**< The LPN established a friendship with a another Friend. */
} mesh_friend_terminated_reason_t;

/** @brief Mesh TLV (Type-Length-Value) message format exchanged with the mesh stack.
 * @ingroup mesh_api
 */
typedef struct MESH_TLV_FORMAT
{
    uint16_t    type;       /**< Payload Identifier : defined by each module.*/
    uint16_t    length;     /**< Payload Length : the length of the payload data.*/
    uint8_t     value[];    /**< Payload Data.*/
} mesh_tlv_t;

/** @brief Mesh local configuration.
 * @ingroup mesh_api
 */
typedef struct MESH_LOCAL_CONFIG
{
    uint32_t type;      /**< Local configuration type.*/
} mesh_local_cfg_t;

/** @brief Mesh application configuration used to initialize the mesh stack.
 * @ingroup mesh_api
 */
typedef struct MESH_APP_CONFIG
{
    pf_mesh_evt_indication  *pf_evt_indication;    /**< Application event indication callback.*/
    mesh_local_cfg_t        *pt_local_cfg;         /**< Pointer to the local configuration.*/
} mesh_app_cfg_t;

/** @brief Provisioning OOB (Out-Of-Band) capabilities.
 * @ingroup mesh_api
 */
typedef struct __attribute((packed))
{
    uint8_t     num_elements;          /**< Number of elements supported by the device.*/
    uint16_t    algorithms;             /**< Supported provisioning algorithms.*/
    uint8_t     pubkey_type;            /**< Public key type.*/
    uint8_t     oob_static_types;       /**< Supported static OOB types.*/
    uint8_t     oob_output_size;        /**< Maximum size of the OOB output.*/
    uint16_t    oob_output_actions;     /**< Supported OOB output actions.*/
    uint8_t     oob_input_size;         /**< Maximum size of the OOB input.*/
    uint16_t    oob_input_actions;      /**< Supported OOB input actions.*/
}
ble_mesh_prov_evt_oob_caps_t;


/** @brief Mesh network layer data request.
 * @ingroup mesh_api
 */
typedef struct MESH_NWK_DATA_REQ
{
    uint8_t    addr_type;          /**< Destination address type.*/
    uint16_t   addr;               /**< Destination address.*/
    uint8_t    *p_virtual_uuid;    /**< Pointer to the virtual address UUID, valid when addr_type indicates a virtual address.*/
    uint16_t   src;                /**< Source address.*/
    uint8_t    ttl;                /**< Time-to-live.*/
    bool       control_packet;     /**< TRUE if the packet is a control (transport control) packet.*/
    uint8_t    mpdu_len;           /**< Length of the mesh PDU.*/
    uint8_t    mpdu[16];           /**< Mesh PDU payload.*/
} mesh_nwk_data_req_t;

/** @brief Request to start provisioning (device role).
 * @ingroup mesh_api
 */
typedef struct MESH_PROVISION_START_REQ
{
    uint32_t    gatt_provision;    /**< TRUE to provision over GATT bearer, FALSE for PB-ADV bearer.*/
    uint32_t    beacon_interval;   /**< Unprovisioned device beacon interval, in milliseconds.*/
    uint8_t     uuid[16];          /**< Device UUID.*/
} mesh_prov_start_req_t;

/** @brief Request to select/open a link to an unprovisioned device (provisioner role).
 * @ingroup mesh_api
 */
typedef struct MESH_PROVISION_DEVICE_REQ
{
    uint16_t    primary_address;   /**< Primary element address to be assigned to the device.*/
    uint8_t     uuid[16];          /**< UUID of the unprovisioned device.*/
} mesh_prov_device_req_t;

/** @brief Confirm the result of @ref TYPE_MESH_PROV_START_REQ.
 * @ingroup mesh_api
 */
typedef struct MESH_PROVISION_START_CFM
{
    uint32_t    status;             /**< @ref mesh_status_t "Provisioning start status".*/
    uint16_t    element_address;    /**< Assigned primary element address.*/
} mesh_prov_start_cfm_t;

/** @brief Request to scan for unprovisioned devices.
 * @ingroup mesh_api
 */
typedef struct MESH_PROVISION_SCAN_REQ
{
    uint32_t    scan_window;    /**< Scan window duration, in milliseconds.*/
} mesh_prov_scan_req_t;

/** @brief Confirm the result of @ref TYPE_MESH_PROV_SCAN_REQ.
 * @ingroup mesh_api
 */
typedef struct MESH_PROVISION_SCAN_CFM
{
    uint32_t    status;    /**< @ref mesh_status_t "Scan request status".*/
} mesh_prov_scan_cfm_t;

/** @brief Indication reporting an unprovisioned device found while scanning.
 * @ingroup mesh_api
 */
typedef struct MESH_PROVISION_SCAN_IDC
{
    uint8_t      uuid[16];    /**< UUID of the unprovisioned device found.*/
} mesh_prov_scan_idc_t;

/** @brief Request to select an unprovisioned device for provisioning.
 * @ingroup mesh_api
 */
typedef struct MESH_PROVISION_SELECT_REQ
{
    uint8_t      uuid[16];    /**< UUID of the unprovisioned device to select.*/
} mesh_prov_select_req_t;

/** @brief Confirm the result of @ref TYPE_MESH_PROV_SEL_REQ.
 * @ingroup mesh_api
 */
typedef struct MESH_PROVISION_SELECT_CFM
{
    uint32_t    status;    /**< @ref mesh_status_t "Selection status".*/
} mesh_prov_select_cfm_t;

/** @brief Indication that the provisioning procedure has completed.
 * @ingroup mesh_api
 */
typedef struct __attribute__((packed))
{
    uint8_t    status;                 /**< @ref mesh_status_t "Provisioning completion status".*/
    uint8_t    device_uuid[16];        /**< UUID of the provisioned device.*/
    uint16_t   element_address;        /**< Primary element address assigned to the device.*/
    uint8_t    element_count;          /**< Number of elements on the device.*/
    uint8_t    device_key[16];         /**< Device key generated for the provisioned device.*/
}
mesh_prov_complete_idc_t;

/** @brief Indication reporting an unprovisioned device advertising report.
 * @ingroup mesh_api
 */
typedef struct MESH_UNPROVISION_DEVICE_IDC
{
    uint8_t      uuid[16];             /**< UUID of the unprovisioned device.*/
    uint8_t      peer_mac_addr[6];     /**< BLE MAC address of the unprovisioned device.*/
    int8_t       rssi;                 /**< RSSI of the received advertising report.*/
} mesh_unprov_device_idc_t;

/** @brief Indication of provisioning advertising enable/disable state.
 * @ingroup mesh_api
 */
typedef struct __attribute__((packed))
{
    uint8_t    status;    /**< @ref mesh_status_t "Provisioning advertising status".*/
}
mesh_prov_adv_enable_idc_t;

/** @brief Indication of proxy advertising enable/disable state.
 * @ingroup mesh_api
 */
typedef struct __attribute__((packed))
{
    uint8_t    status;    /**< @ref mesh_status_t "Proxy advertising status".*/
}
mesh_proxy_adv_enable_idc_t;

/** @brief Request to register an application/SIG model on an element.
 * @ingroup mesh_api
 */
typedef struct MESH_MDL_REGIST_REQ
{
    bool        is_sig;             /**< TRUE for a SIG defined model, FALSE for a vendor model.*/
    uint32_t    model_id;           /**< Model identifier.*/
    uint16_t    element_address;    /**< Element address the model is registered on.*/
} mesh_mdl_reg_req_t;

/** @brief Request to send an application model message.
 * @ingroup mesh_api
 */
typedef struct MESH_APP_MDL_EVT_MSG_REQ
{
    uint32_t ttl             : 8;     /**< Time-to-live.*/
    uint32_t opcode_invalid  : 1;     /**< TRUE if the opcode field is a raw (non-standard) value.*/
    uint32_t appkey_index    : 12;    /**< Application key index used to encrypt the message.*/
    uint32_t                 : 11;    /**< Reserved.*/
    uint32_t dst_addr        : 16;    /**< Destination address.*/
    uint32_t src_addr        : 16;    /**< Source element address.*/
    uint32_t opcode;                  /**< Model message opcode.*/
    uint32_t parameter_len;           /**< Length of the parameter payload.*/
    uint8_t parameter[];              /**< Model message parameter payload.*/
} mesh_app_mdl_evt_msg_req_t;

/** @brief Request to send a Configuration Model message.
 * @ingroup mesh_api
 */
typedef struct MESH_CFG_MDL_EVT_MSG_REQ
{
    uint32_t dst_addr      : 16;    /**< Destination address.*/
    uint32_t src_addr      : 16;    /**< Source element address.*/
    uint32_t opcode;                /**< Configuration model message opcode.*/
    uint16_t netkey_index;          /**< Network key index used to encrypt the message.*/
    uint16_t ttl           : 8;     /**< Time-to-live.*/
    uint16_t mic_size      : 8;     /**< Message Integrity Check size.*/
    uint8_t  config_key[16];        /**< Device key or application key used for the configuration message.*/
    uint32_t parameter_len;         /**< Length of the parameter payload.*/
    uint8_t  parameter[];           /**< Configuration model message parameter payload.*/
} mesh_cfg_mdl_evt_msg_req_t;

/** @brief Indication that an application model message has been received.
 * @ingroup mesh_api
 */
typedef struct MESH_APP_MDL_EVT_MSG_IDC
{
    uint32_t src_addr           : 16;    /**< Source address of the message.*/
    uint32_t dst_addr           : 16;    /**< Destination address of the message.*/
    uint32_t opcode;                     /**< Model message opcode.*/
    uint32_t appkey_index: 16;           /**< Application key index the message was decrypted with.*/
    uint32_t parameter_len: 16;          /**< Length of the parameter payload.*/

    uint8_t parameter[];                 /**< Model message parameter payload.*/
} mesh_app_mdl_evt_msg_idc_t;

/** @brief Indication that a Configuration Model message has been received.
 * @ingroup mesh_api
 */
typedef struct MESH_CFG_MDL_EVT_MSG_IDC
{
    uint32_t opcode;                     /**< Configuration model message opcode.*/
    uint32_t src_addr       : 16;        /**< Source address of the message.*/
    uint32_t parameter_len  : 16;        /**< Length of the parameter payload.*/
    uint8_t parameter[];                 /**< Configuration model message parameter payload.*/
} mesh_cfg_mdl_evt_msg_idc_t;

/** @brief Indication that an application key has been bound to a model.
 * @ingroup mesh_api
 */
typedef struct MESH_CFG_MDL_APP_BIND_IDC
{
    uint16_t element_address;    /**< Element address of the model.*/
    uint16_t appkey_index;       /**< Application key index bound to the model.*/
    uint32_t model_id;           /**< Model identifier.*/
} mesh_cfg_mdl_app_bind_idc_t;

/** @brief Indication that a friendship has been established (Friend role).
 * @ingroup mesh_api
 */
typedef struct MESH_FRIEND_ESTABLISHED_IDC
{
    uint16_t lpn_address;    /**< Address of the Low Power Node.*/
    uint16_t element_cnt;    /**< Number of elements on the Low Power Node.*/
} mesh_friend_established_idc_t;

/** @brief Indication that a friendship has been terminated (Friend role).
 * @ingroup mesh_api
 */
typedef struct MESH_FRIEND_TERMINATED_IDC
{
    uint16_t                        lpn_address;         /**< Address of the Low Power Node.*/
    mesh_friend_terminated_reason_t terminate_reason;     /**< @ref mesh_friend_terminated_reason_t "Termination reason".*/
} mesh_friend_terminated_idc_t;


/** @brief Mesh stack command request, used with @ref TYPE_MESH_CMD_REQ.
 * @ingroup mesh_api
 */
typedef struct MESH_CMD_REQUEST_PARAMETER
{
    uint32_t cmd_type;        /**< @ref mesh_cmd_t "Command type".*/
    uint32_t cmd_length;      /**< Length of the command value.*/
    uint32_t cmd_value[];     /**< Command value payload.*/
} mesh_cmd_req_t;

//=============================================================================
//                Public Function Declaration
//=============================================================================
/** @brief Initialize the mesh stack, including the bearer/mesh task creation and the application event callback registration.
 *
 * @ingroup mesh_api
 *
 * @param p_task_priority_cfg : a pointer to the bearer/mesh task priority configuration @ref mesh_task_priority_t.
 * @param pfn_callback : the application event indication callback to receive mesh stack events.
 *
 * @return 0 is success, or a negative @ref mesh_status_t "error code".
 */
int mesh_stack_init(mesh_task_priority_t *p_task_priority_cfg, pf_mesh_evt_indication *pfn_callback);

/** @brief Send a confirmation response back to the mesh stack for a received request.
 *
 * @ingroup mesh_api
 *
 * @param err_code : the @ref mesh_status_t "result status" to confirm.
 * @param dst : destination address of the confirmation.
 * @param src : source address of the confirmation.
 */
void mesh_cfm_send(mesh_status_t err_code, uint16_t dst, uint16_t src);

/** @brief Send a mesh TLV message to the mesh stack.
 *
 * @ingroup mesh_api
 *
 * @param pt_tlv : a pointer to the mesh TLV message @ref mesh_tlv_t to send.
 *
 * @return 0 is success, or a negative @ref mesh_status_t "error code".
 */
int mesh_evt_msg_sendto(mesh_tlv_t *pt_tlv);


#ifdef __cplusplus
};
#endif
#endif /* __MESH_API_H__*/
