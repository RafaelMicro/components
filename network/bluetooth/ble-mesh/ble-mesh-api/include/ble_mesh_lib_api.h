/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/** @file ble_mesh_lib_api.h
 *
 * @brief BLE Mesh library API header file.
 *
 */
/**
 * @defgroup ble_mesh_lib_api BLE Mesh Library API
 * @ingroup BLE_group
 * @{
 * @brief Define BLE Mesh library API functions built on top of @ref mesh_api.
 * @}
 */
#ifndef __BLE_MESH_LIB_API_H__
#define __BLE_MESH_LIB_API_H__

#ifdef __cplusplus
extern "C" {
#endif

//=============================================================================
//                Include (Better to prevent)
//=============================================================================
#include "stdint.h"
#include "stdbool.h"

//=============================================================================
//                Private ENUM
//=============================================================================
//=============================================================================
//                Private Definitions of const value
//=============================================================================


//=============================================================================
//                Public Function Declaration
//=============================================================================
/** @brief Start scanning for unprovisioned mesh devices.
 *
 * @ingroup ble_mesh_lib_api
 */
void ble_mesh_find_unprov_device_start(void);

/** @brief Stop scanning for unprovisioned mesh devices.
 *
 * @ingroup ble_mesh_lib_api
 */
void ble_mesh_find_unprov_device_stop(void);

/** @brief Start the mesh provisioning procedure for the local device.
 *
 * @ingroup ble_mesh_lib_api
 *
 * @param from_gatt : TRUE(1) to provision over the GATT bearer, FALSE(0) to provision over the PB-ADV bearer.
 */
void ble_mesh_provision_start(uint8_t from_gatt);

/** @brief Stop the mesh provisioning procedure.
 *
 * @ingroup ble_mesh_lib_api
 */
void ble_mesh_provision_stop(void);

/** @brief Enable the mesh proxy service.
 *
 * @ingroup ble_mesh_lib_api
 */
void ble_mesh_proxy_enable(void);

/** @brief Disable the mesh proxy service.
 *
 * @ingroup ble_mesh_lib_api
 */
void ble_mesh_proxy_disable(void);

/** @brief Select an unprovisioned device and open the provisioning link (provisioner role).
 *
 * @ingroup ble_mesh_lib_api
 *
 * @param primary_address : the primary element address to be assigned to the device.
 * @param p_uuid : a pointer to the 16-byte UUID of the unprovisioned device to select.
 */
void ble_mesh_select_unprovisioned_device(uint16_t primary_address, uint8_t *p_uuid);

/** @brief Set the local mesh device name.
 *
 * @ingroup ble_mesh_lib_api
 *
 * @param len : length of the device name, must be no larger than 31 bytes.
 * @param p_device_name : a pointer to the device name buffer.
 *
 * @return TRUE if the request was sent to the mesh stack successfully, FALSE otherwise.
 */
bool ble_mesh_device_name_set(uint8_t len, uint8_t *p_device_name);

/** @brief Create a BLE transparent service (TRSPS) connection.
 *
 * @ingroup ble_mesh_lib_api
 */
void ble_trsps_connection_create(void);

/** @brief Cancel a BLE transparent service (TRSPS) connection.
 *
 * @ingroup ble_mesh_lib_api
 */
void ble_trsps_connection_cancel(void);

/** @brief Send data over the BLE transparent service (TRSPS).
 *
 * @ingroup ble_mesh_lib_api
 *
 * @param len : length of the data to send.
 * @param p_data : a pointer to the data buffer to send.
 *
 * @return TRUE if the request was sent to the mesh stack successfully, FALSE otherwise.
 */
bool ble_trsps_data_set(uint16_t len, uint8_t *p_data);


#ifdef __cplusplus
};
#endif
#endif /* __BLE_MESH_LIB_API_H__*/
