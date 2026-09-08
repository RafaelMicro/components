/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/** @file ble_connect_cte.h
 *
 * @brief BLE CONN CTE header file.
 *
 */

/**
 * @defgroup ble_cte BLE Constant Tone Extension (CTE)
 * @ingroup BLE_group
 * @{
 * @brief Define BLE CONN CTE definitions, structures, and functions.
 * @}
 */

#ifndef __BLE_CONNECT_CTE_H__
#define __BLE_CONNECT_CTE_H__


/**************************************************************************************************
 *    INCLUDES
 *************************************************************************************************/
#include <stdint.h>
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

/** @brief BLE Set connection CTE receive parameter.
 * @ingroup ble_cte
*/
typedef struct ble_connection_cte_rx_param_s
{
    uint8_t                 host_id;          /**< Host id. */
    uint8_t                 sampling_enable;  /**< Enable (0x01) or disable (0x00) connection IQ sampling for CTEs received from the peer device. */
    uint8_t                 slot_durations;   /**< Switching and sampling slot durations: 0x01 = 1 us slots, 0x02 = 2 us slots. */
    uint8_t                 sw_pattern_length;/**< The number of Antenna IDs in the pattern. */
    uint8_t                 antenna_ids[];    /**< List of Antenna IDs in the pattern. */
} ble_connection_cte_rx_param_t;


/** @brief BLE Set connection CTE transmit parameter.
 * @ingroup ble_cte
*/
typedef struct ble_connection_cte_tx_param_s
{
    uint8_t                 host_id;          /**< Host id. */
    uint8_t                 cte_types;        /**< Bitmask of permitted CTE response types: bit 0 = AoA, bit 1 = AoD with 1 us slots, bit 2 = AoD with 2 us slots. */
    uint8_t                 sw_pattern_length;/**< The number of Antenna IDs in the pattern. */
    uint8_t                 antenna_ids[];    /**< List of Antenna IDs in the pattern. */
} ble_connection_cte_tx_param_t;


/** @brief BLE Set connection cte request enable.
 * @ingroup ble_cte
*/
typedef struct ble_connection_cte_req_enable_s
{
    uint8_t                 host_id;          /**< Host id. */
    uint8_t                 enable;           /**< Enable (0x01) or disable (0x00) the CTE Request procedure for this connection. */
    uint16_t                cte_req_interval; /**< Interval, in number of connection events, between successive initiations of the CTE Request procedure; 0x0000 initiates the procedure only once. */
    uint8_t                 req_cte_length;   /**< Minimum length of the requested Constant Tone Extension, in units of 8 us (range 0x02 to 0x14, i.e. 16 us to 160 us). */
    uint8_t                 req_cte_type;     /**< The type of Constant Tone Extension that the Controller shall request from the remote device. */
} ble_connection_cte_req_enable_t;


/** @brief BLE Set connection CTE response parameter.
 * @ingroup ble_cte
*/
typedef struct ble_connection_cte_rsp_enable_s
{
    uint8_t                 host_id;          /**< Host id. */
    uint8_t                 enable;           /**< Enable (0x01) or disable (0x00) the CTE Response procedure for this connection. */
} ble_connection_cte_rsp_enable_t;


/**
 * @brief Set CTE RX Event Parameters.
 * @ingroup ble_cte
*/
typedef struct __attribute__((packed)) ble_evt_conn_cte_rx_param_s
{
    uint8_t                 host_id;         /**< Host id. */
    uint8_t                 status;          /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
} ble_evt_conn_cte_rx_param_t;


/**
 * @brief Set CTE TX Event Parameters.
 * @ingroup ble_cte
*/
typedef struct __attribute__((packed)) ble_evt_conn_cte_tx_param_s
{
    uint8_t                 host_id;         /**< Host id. */
    uint8_t                 status;          /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
} ble_evt_conn_cte_tx_param_t;


/**
 * @brief Set CTE REQ Event Parameters.
 * @ingroup ble_cte
*/
typedef struct __attribute__((packed)) ble_evt_conn_cte_req_s
{
    uint8_t                 host_id;         /**< Host id. */
    uint8_t                 status;          /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
} ble_evt_conn_cte_req_t;


/**
 * @brief Set CTE RSP Event Parameters.
 * @ingroup ble_cte
*/
typedef struct __attribute__((packed)) ble_evt_conn_cte_rsp_s
{
    uint8_t                 host_id;         /**< Host id. */
    uint8_t                 status;          /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
} ble_evt_conn_cte_rsp_t;


/**
 * @brief BLE CTE IQ report event parameters.
 * @ingroup ble_cte
*/
typedef struct __attribute__((packed)) ble_evt_conn_iq_report_s
{
    uint8_t                 host_id;        /**< Host id. */
    uint8_t                 rx_phy;         /**< Receiver PHY. */
    uint8_t                 data_ch_idx;    /**< The index of the data channel. */
    int16_t                 rssi;           /**< RSSI of the received packet, in dBm. */
    uint8_t                 rssi_antenna_id;    /**< ID of the antenna on which the RSSI was measured. */
    uint8_t                 cte_type;       /**< CTE type of the received packet: 0x00 = AoA, 0x01 = AoD with 1 us slots, 0x02 = AoD with 2 us slots. */
    uint8_t                 slot_durations; /**< Switching and sampling slot durations: 0x01 = 1 us slots, 0x02 = 2 us slots. */
    uint8_t                 packet_status;  /**< Validity of the IQ samples: 0x00 = CRC correct, 0x01 = CRC incorrect but length/CTEInfo valid, 0x02 = insufficient resources to sample, 0xFF = CTE present but samples not collected. */
    uint16_t                conn_evt_cnt;   /**< The value of the connection event counter. */
    uint8_t                 sample_cnt;     /**< Number of IQ samples in sample_iq (0 if no valid samples were collected). */
    uint8_t                 sample_iq[];    /**< Array of reported I/Q samples, alternating I and Q values. */
} ble_evt_conn_iq_report_t;


/**
 * @brief CTE REQ Failed Event Parameters.
 * @ingroup ble_cte
*/
typedef struct __attribute__((packed)) ble_evt_cte_req_failed_s
{
    uint8_t                 host_id;        /**< Host id. */
    uint8_t                 status;          /**< @ref hci_cmd_param_error_code "ble_hci_error_code_t". */
} ble_evt_cte_req_failed_t;


/**
 * @brief BLE CONN CTE Event Parameters.
 * @ingroup ble_cte
*/
typedef struct ble_evt_cte_s
{
    union
    {
        ble_evt_conn_cte_rx_param_t      evt_conn_cte_rx_param; /**< BLE set connection cte rx parameters event. */
        ble_evt_conn_cte_tx_param_t      evt_conn_cte_tx_param; /**< BLE set connection cte tx parameters event. */
        ble_evt_conn_cte_req_t           evt_conn_cte_req;      /**< BLE set connection cte request event. */
        ble_evt_conn_cte_rsp_t           evt_conn_cte_rsp;      /**< BLE set connection cte response event. */
        ble_evt_conn_iq_report_t         evt_conn_iq_report;    /**< BLE connection IQ report event. */
        ble_evt_cte_req_failed_t         evt_cte_req_failed;    /**< BLE CTE request failed event. */
    } param;                                                    /**< Event parameters. */
} ble_evt_cte_t;

/**************************************************************************************************
 *    MACROS
 *************************************************************************************************/


/**************************************************************************************************
 *    GLOBAL PROTOTYPES
 *************************************************************************************************/

/** @brief BLE Set connection CTE receiver parameters.
 *
 * @ingroup ble_cte
 *
 * @param[in] p_param : a pointer of the CTE receiver parameters structure.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_connection_cte_receive_parameters_set(ble_connection_cte_rx_param_t *p_param);


/** @brief BLE Set connection CTE transmit parameters.
 *
 * @ingroup ble_cte
 *
 * @param[in] p_param : a pointer of the CTE transmit parameters structure.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_connection_cte_transmit_parameters_set(ble_connection_cte_tx_param_t *p_param);


/** @brief BLE Set connection CTE request enable.
 *
 * @ingroup ble_cte
 *
 * @param[in] p_param : a pointer of the CTE request enable structure.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_connection_cte_request_enable(ble_connection_cte_req_enable_t *p_param);

/** @brief BLE Set connection CTE response enable.
 *
 * @ingroup ble_cte
 *
 * @param[in] p_param : a pointer of the CTE response enable structure.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_connection_cte_response_enable(ble_connection_cte_rsp_enable_t *p_param);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BLE_CONNECT_CTE_H__ */
