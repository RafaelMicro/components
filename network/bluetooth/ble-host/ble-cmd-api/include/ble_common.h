/** @file ble_common.h
 *
 * @brief BLE common header file.
 *
 */
/**
 * @defgroup ble_common BLE Common
 * @ingroup BLE_group
 * @{
 * @brief Define BLE Common definitions, structures, and functions.
 * @}
 */
#ifndef __BLE_COMMON_H__
#define __BLE_COMMON_H__


/**************************************************************************************************
 *    INCLUDES
 *************************************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "ble_gap.h"
#include "ble_api.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**************************************************************************************************
 *    CONSTANTS AND DEFINES
 *************************************************************************************************/
/** @ingroup ble_common
 * @{
 */
#define BLE_STACK_VERSION                 0x0C      /**< Bluetooth Core Specification 5.3, see Assigned Numbers (https://www.bluetooth.com/specifications/assigned-numbers). */
#define BLE_COMPANY_ID                    0x0864    /**< Rafael Micro. company Id is 0x0864, see Assigned Numbers (https://www.bluetooth.com/specifications/assigned-numbers). */

#define BLE_EVENT_MASK_LENGTH             8

#define BLE_HOSTID_RESERVED               0xFF      /**< Reserved BLE host id.*/

#define SEC_BLE_MAC_REG                   0x1100    /**< MAC ADDR SEC REG.*/

/** @brief REF_SIZE_LE_HOST_PARA for checking host parameter size in application layer and host layer.
 * @attention Do NOT modify this definition.
 */
#define REF_SIZE_LE_HOST_PARA             272
/** @} */

#define LE_CONNECTION_COMPLETE_EVENT                                0x01
#define LE_ADVERTISING_REPORT_EVENT                                 0x02
#define LE_CONNECTION_UPDATE_COMPLETE_EVENT                         0x04
#define LE_READ_REMOTE_FEATURES_COMPLETE_EVENT                      0x08
#define LE_LONG_TERM_KEY_REQUEST_EVENT                              0x10
#define LE_REMOTE_CONNECTION_PARAMETER_REQUEST_EVENT                0x20
#define LE_DATA_LENGTH_CHANGE_EVENT                                 0x40
#define LE_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE_EVENT                0x80

#define LE_GENERATE_DHKEY_COMPLETE_EVENT                            0x01
#define LE_ENHANCED_CONNECTION_COMPLETE_V1_EVENT                    0x02
#define LE_DIRECTED_ADVERTISING_REPORT_EVENT                        0x04
#define LE_PHY_UPDATE_COMPLETE_EVENT                                0x08
#define LE_EXTENDED_ADVERTISING_REPORT_EVENT                        0x10
#define LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_V1_EVENT           0x20
#define LE_PERIODIC_ADVERTISING_REPORT_V1_EVENT                     0x40
#define LE_PERIODIC_ADVERTISING_SYNC_LOST_EVENT                     0x80

#define LE_SCAN_TIMEOUT_EVENT                                       0x01
#define LE_ADVERTISING_SET_TERMINATED_EVENT                         0x02
#define LE_SCAN_REQUEST_RECEIVED_EVENT                              0x04
#define LE_CHANNEL_SELECTION_ALGORITHM_EVENT                        0x08
#define LE_CONNECTIONLESS_IQ_REPORT_EVENT                           0x10
#define LE_CONNECTION_IQ_REPORT_EVENT                               0x20
#define LE_CTE_REQUEST_FAILED_EVENT                                 0x40
#define LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_V1_EVENT     0x80

#define LE_CIS_ESTABLISHED_EVENT                                    0x01
#define LE_CIS_REQUEST_EVENT                                        0x02
#define LE_CREATE_BIG_COMPLETE_EVENT                                0x04
#define LE_TERMINATE_BIG_COMPLETE_EVENT                             0x08
#define LE_BIG_SYNC_ESTABLISHED_EVENT                               0x10
#define LE_BIG_SYNC_LOST_EVENT                                      0x20
#define LE_REQUEST_PEER_SCA_COMPLETE_EVENT                          0x40
#define LE_PATH_LOSS_THRESHOLD_EVENT                                0x80

#define LE_TRANSMIT_POWER_REPORTING_EVENT                           0x01
#define LE_BIGINFO_ADVERTISING_REPORT_EVENT                         0x02
#define LE_SUBRATE_CHANGE_EVENT                                     0x04
#define LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_V2_EVENT           0x08
#define LE_PERIODIC_ADVERTISING_REPORT_V2_EVENT                     0x10
#define LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_V2_EVENT     0x20
#define LE_PERIODIC_ADVERTISING_SUBEVENT_DATA_REQUEST_EVENT         0x40
#define LE_PERIODIC_ADVERTISING_RESPONSE_REPORT_EVENT               0x80

#define LE_ENHANCED_CONNECTION_COMPLETE_V2_EVENT                    0x01

#define PAWR_SELECT_EVENT_MASK                                      BLE_PAWR_SELECT

#if (PAWR_SELECT_EVENT_MASK == 0x01)
static const uint8_t g_le_event_mask[] =
{
    (
        LE_CONNECTION_COMPLETE_EVENT |
        LE_ADVERTISING_REPORT_EVENT |
        LE_CONNECTION_UPDATE_COMPLETE_EVENT |
        LE_READ_REMOTE_FEATURES_COMPLETE_EVENT |
        LE_LONG_TERM_KEY_REQUEST_EVENT |
        LE_REMOTE_CONNECTION_PARAMETER_REQUEST_EVENT |
        LE_DATA_LENGTH_CHANGE_EVENT |
        //LE_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE_EVENT |
        0x00
    ),
    (
        //LE_GENERATE_DHKEY_COMPLETE_EVENT |
        //LE_ENHANCED_CONNECTION_COMPLETE_V1_EVENT |
        LE_DIRECTED_ADVERTISING_REPORT_EVENT |
        LE_PHY_UPDATE_COMPLETE_EVENT |
        LE_EXTENDED_ADVERTISING_REPORT_EVENT |
        LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_V1_EVENT |
        LE_PERIODIC_ADVERTISING_REPORT_V1_EVENT |
        LE_PERIODIC_ADVERTISING_SYNC_LOST_EVENT |
        0x00
    ),
    (
        //LE_SCAN_TIMEOUT_EVENT |
        LE_ADVERTISING_SET_TERMINATED_EVENT |
        //LE_SCAN_REQUEST_RECEIVED_EVENT |
        //LE_CHANNEL_SELECTION_ALGORITHM_EVENT |
        //LE_CONNECTIONLESS_IQ_REPORT_EVENT |
        //LE_CONNECTION_IQ_REPORT_EVENT |
        //LE_CTE_REQUEST_FAILED_EVENT |
        LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_V1_EVENT |
        0x00
    ),
    (
        //LE_CIS_ESTABLISHED_EVENT |
        //LE_CIS_REQUEST_EVENT |
        //LE_CREATE_BIG_COMPLETE_EVENT |
        //LE_TERMINATE_BIG_COMPLETE_EVENT |
        //LE_BIG_SYNC_ESTABLISHED_EVENT |
        //LE_BIG_SYNC_LOST_EVENT |
        //LE_REQUEST_PEER_SCA_COMPLETE_EVENT |
        //LE_PATH_LOSS_THRESHOLD_EVENT |
        0x00
    ),
    (
        //LE_TRANSMIT_POWER_REPORTING_EVENT |
        //LE_BIGINFO_ADVERTISING_REPORT_EVENT |
        //LE_SUBRATE_CHANGE_EVENT |
        LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_V2_EVENT |
        LE_PERIODIC_ADVERTISING_REPORT_V2_EVENT |
        LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_V2_EVENT |
        LE_PERIODIC_ADVERTISING_SUBEVENT_DATA_REQUEST_EVENT |
        LE_PERIODIC_ADVERTISING_RESPONSE_REPORT_EVENT |
        0x00
    ),
    (
        LE_ENHANCED_CONNECTION_COMPLETE_V2_EVENT |
        0x00
    ),
    0x00,
    0x00,
};
#else
static const uint8_t g_le_event_mask[] =
{
    (
        LE_CONNECTION_COMPLETE_EVENT |
        LE_ADVERTISING_REPORT_EVENT |
        LE_CONNECTION_UPDATE_COMPLETE_EVENT |
        LE_READ_REMOTE_FEATURES_COMPLETE_EVENT |
        LE_LONG_TERM_KEY_REQUEST_EVENT |
        LE_REMOTE_CONNECTION_PARAMETER_REQUEST_EVENT |
        LE_DATA_LENGTH_CHANGE_EVENT |
        //LE_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE_EVENT |
        0x00
    ),
    (
        //LE_GENERATE_DHKEY_COMPLETE_EVENT |
        //LE_ENHANCED_CONNECTION_COMPLETE_V1_EVENT |
        LE_DIRECTED_ADVERTISING_REPORT_EVENT |
        LE_PHY_UPDATE_COMPLETE_EVENT |
        //LE_EXTENDED_ADVERTISING_REPORT_EVENT |
        //LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_V1_EVENT |
        //LE_PERIODIC_ADVERTISING_REPORT_V1_EVENT |
        //LE_PERIODIC_ADVERTISING_SYNC_LOST_EVENT |
        0x00
    ),
    (
        //LE_SCAN_TIMEOUT_EVENT |
        //LE_ADVERTISING_SET_TERMINATED_EVENT |
        //LE_SCAN_REQUEST_RECEIVED_EVENT |
        //LE_CHANNEL_SELECTION_ALGORITHM_EVENT |
        //LE_CONNECTIONLESS_IQ_REPORT_EVENT |
        LE_CONNECTION_IQ_REPORT_EVENT |
        LE_CTE_REQUEST_FAILED_EVENT |
        //LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_V1_EVENT |
        0x00
    ),
    (
        //LE_CIS_ESTABLISHED_EVENT |
        //LE_CIS_REQUEST_EVENT |
        //LE_CREATE_BIG_COMPLETE_EVENT |
        //LE_TERMINATE_BIG_COMPLETE_EVENT |
        //LE_BIG_SYNC_ESTABLISHED_EVENT |
        //LE_BIG_SYNC_LOST_EVENT |
        //LE_REQUEST_PEER_SCA_COMPLETE_EVENT |
        //LE_PATH_LOSS_THRESHOLD_EVENT |
        0x00
    ),
    (
        //LE_TRANSMIT_POWER_REPORTING_EVENT |
        //LE_BIGINFO_ADVERTISING_REPORT_EVENT |
        //LE_SUBRATE_CHANGE_EVENT |
        //LE_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_V2_EVENT |
        //LE_PERIODIC_ADVERTISING_REPORT_V2_EVENT |
        //LE_PERIODIC_ADVERTISING_SYNC_TRANSFER_RECEIVED_V2_EVENT |
        //LE_PERIODIC_ADVERTISING_SUBEVENT_DATA_REQUEST_EVENT |
        //LE_PERIODIC_ADVERTISING_RESPONSE_REPORT_EVENT |
        0x00
    ),
    (
        //LE_ENHANCED_CONNECTION_COMPLETE_V2_EVENT |
        0x00
    ),
    0x00,
    0x00,
};
#endif

static const uint8_t g_ble_default_public_addr[BLE_ADDR_LEN] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};    /**< Default BLE public address..*/

/**************************************************************************************************
 *    TYPEDEFS
 *************************************************************************************************/
/**
 * @brief Set BLE Controller Information Parameters.
 * @ingroup ble_common
 */
typedef struct
{
    uint8_t     version;                               /**< BLE version. */
    uint16_t    company_id;                            /**< Company ID. */
    uint8_t     public_addr[BLE_ADDR_LEN];             /**< Public address. */
    uint8_t     le_event_mask[BLE_EVENT_MASK_LENGTH];  /**< LE event mask. */
} ble_common_controller_info_t;


/**
 * @brief Set scan request event report Parameter.
 * @ingroup ble_common
 */
typedef struct
{
    uint8_t     scan_req_rpt_status;                   /**< scan request report status.*/
} ble_vendor_scan_req_rpt_t;


/**
 * @brief Unique code Parameter format.
 * @ingroup ble_common
 */
typedef struct
{
    uint8_t addr_type;                                 /**<Address type.*/
    uint8_t Reserved;                                  /**<Reserved byte.*/
    uint8_t ble_addr[6];                               /**<BLE unique mac address code.*/
    uint8_t zigbee_addr[8];                            /**<ZigBee unique mac address code.*/
    uint8_t ble_irk[16];                               /**<BLE Identity Resolving Key code.*/
} ble_unique_code_format_t;


/**
 * @brief Filter accept list format.
 * @ingroup ble_common
 */
typedef struct
{
    ble_addr_type_t addr_type;            /**< @ref ble_gap_addr_type "Address type".*/
    uint8_t         addr[BLE_ADDR_LEN];   /**< Address.*/
} ble_filter_accept_list_t;


/**
 * @brief Set Controller Information Event Parameters.
 * @ingroup ble_common
 */
typedef struct __attribute__((packed)) ble_evt_common_set_cntlr_info_s
{
    uint8_t             status;                        /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */

} ble_evt_common_set_cntlr_info_t;


/**
 * @brief Set Event Mask Event Parameters.
 * @ingroup ble_common
 */
typedef struct __attribute__((packed)) ble_evt_common_set_event_mask_s
{
    uint8_t             status;                        /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */

} ble_evt_common_set_event_mask_t;


/**
 * @brief Read Local Version Event Parameters.
 * @ingroup ble_common
 */
typedef struct __attribute__((packed)) ble_evt_common_read_local_ver_s
{
    uint8_t             status;                        /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t             hci_version;                   /**< HCI version. */
    uint16_t            hci_revision;                  /**< Revision of the Current HCI in the BR/EDR Controller. */
    uint8_t             lmp_pal_version;               /**< Version of the Current LMP or PAL in the Controller. */
    uint16_t            manufacturer_name;             /**< Manufacturer Name of the BR/EDR Controller. */
    uint16_t            lmp_pal_subversion;            /**< Subversion of the Current LMP or PAL in the Controller. This value is implementation dependent. */
} ble_evt_common_read_local_ver_t;


/**
 * @brief Read Buffer Size Event Parameters.
 * @ingroup ble_common
 */
typedef struct __attribute__((packed)) ble_evt_common_read_buffer_size_s
{
    uint8_t             status;                        /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint16_t            data_packet_length;            /**< Data packet length. */
    uint8_t             total_num_data_packet;         /**< Total number of data packets. */
} ble_evt_common_read_buffer_size_t;

/**
 * @brief Read Filter Accept List Size Event Parameters.
 * @ingroup ble_common
 */
typedef struct __attribute__((packed)) ble_evt_common_read_filter_accept_list_size_s
{
    uint8_t             status;                        /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t             filter_accept_list_size;       /**< Filter accept list size. */
} ble_evt_common_read_filter_accept_list_size_t;


/**
 * @brief Clear Filter Accept List Event Parameters.
 * @ingroup ble_common
 */
typedef struct __attribute__((packed)) ble_evt_common_clear_filter_accept_list_s
{
    uint8_t             status;                        /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
} ble_evt_common_clear_filter_accept_list_t;


/**
 * @brief Add Filter Accept List Event Parameters.
 * @ingroup ble_common
 */
typedef struct __attribute__((packed)) ble_evt_common_add_filter_accept_list_s
{
    uint8_t             status;                        /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
} ble_evt_common_add_filter_accept_list_t;


/**
 * @brief Remove Filter Accept List Event Parameters.
 * @ingroup ble_common
 */
typedef struct __attribute__((packed)) ble_evt_common_remove_filter_accept_list_s
{
    uint8_t             status;                        /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
} ble_evt_common_remove_filter_accept_list_t;


/**
 * @brief Read antenna information Event Parameters.
 * @ingroup ble_common
 */
typedef struct __attribute__((packed)) ble_evt_common_read_antenna_info_s
{
    uint8_t             status;                        /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
    uint8_t             supported_rates;               /**< Supported switching sampling rates. */
    uint8_t             num_antennae;                  /**< The number of antennae supported. */
    uint8_t             max_pattern_length;            /**< Maximum length of antenna switching pattern supported. */
    uint8_t             max_cte_length;                /**< Maximum length of a transmitted constant tone extension supported in 8us uints. */
} ble_evt_common_read_antenna_info_t;


/**
 * @brief Scan Request Report Event Parameters.
 * @ingroup ble_common
 */
typedef struct __attribute__((packed)) ble_evt_vendor_scan_req_rpt_s
{
    uint8_t             addr_type;                     /**< Address type. */
    uint8_t             addr[BLE_ADDR_LEN];            /**< Address. */
    int8_t              rssi;                          /**< RSSI value. */
} ble_evt_vendor_scan_req_rpt_t;


/**
 * @brief BLE Common Event Parameters.
 * @ingroup ble_common
 */
typedef struct ble_evt_common_s
{
    union
    {
        ble_evt_common_set_cntlr_info_t                 evt_set_cntlr_info;         /**< Set controller information event parameters. */
        ble_evt_common_set_event_mask_t                 evt_set_event_mask;         /**< Set event mask event parameters. */
        ble_evt_common_read_local_ver_t                 evt_read_local_ver;         /**< Read local version event parameters. */
        ble_evt_common_read_buffer_size_t               evt_read_buffer_size;       /**< Read buffer size event parameters. */
        ble_evt_common_read_filter_accept_list_size_t   evt_read_accept_list_size;  /**< Read filter accept list size event parameters. */
        ble_evt_common_clear_filter_accept_list_t       evt_clear_accept_list;      /**< Clear filter accept list event parameters. */
        ble_evt_common_add_filter_accept_list_t         evt_add_accept_list;        /**< Add filter accept list event parameters. */
        ble_evt_common_remove_filter_accept_list_t      evt_remove_accept_list;     /**< Remove filter accept list event parameters. */
        ble_evt_vendor_scan_req_rpt_t                   evt_scan_req_rpt;           /**< Scan request report parameters. */
        ble_evt_common_read_antenna_info_t              evt_read_antenna_info;      /**< Antenna information parameters. */
    } param;                                                      /**< Event parameters. */
} ble_evt_common_t;


/**************************************************************************************************
 *    MACROS
 *************************************************************************************************/
#define SIZE_ARRAY_ROW(a)                 (sizeof((a))/sizeof((a[0]))) /**< The size of the array.*/


/**************************************************************************************************
 *    GLOBAL PROTOTYPES
 *************************************************************************************************/

/** @brief BLE common controller setting initial function (BLE stack initialization included).
 *
 * @ingroup ble_common
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_phy_controller_init(void);


/** @brief Read unique code from Flash.
 *
 * @ingroup ble_common
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_read_unique_code(ble_unique_code_format_t *p_param);


/** @brief Read filter accept list size.
 *
 * @ingroup ble_common
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_read_filter_accept_list_size(void);


/** @brief Clear filter accept list.
 *
 * @ingroup ble_common
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_clear_filter_accept_list(void);


/** @brief Add device to filter accept list.
 *
 * @ingroup ble_common
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_add_device_to_accept_list(ble_filter_accept_list_t *p_accept_list);


/** @brief Remove device from filter accept list.
 *
 * @ingroup ble_common
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_remove_device_from_accept_list(ble_filter_accept_list_t *p_accept_list);


/** @brief Read antenna information.
 *
 * @ingroup ble_common
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_antenna_info_read(void);


/** @brief BLE Vendor command : scan request report.
 *
 * @ingroup ble_common
 *
 * @param p_param :  a pointer to the scan request report parameter @ref ble_hci_vcmd_scan_req_rpt_param_t.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_vendor_scan_req_report_set(ble_vendor_scan_req_rpt_t *p_param);


/** @brief BLE common events handler
 *
 * @ingroup ble_common
 *
 * @param p_param :  a pointer to the event parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_evt_common_handler(void *p_param);


/** @brief BLE common events handler
 *
 * @ingroup ble_common
 *
 * @param p_param :  a pointer to the event parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_evt_vendor_handler(void *p_param);




#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BLE_COMMON_H__ */
