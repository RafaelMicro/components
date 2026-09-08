/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/** @file ble_privacy.h
 *
 * @brief BLE Privacy header file.
 *
 */

/**
 * @defgroup ble_privacy BLE Privacy
 * @ingroup BLE_group
 * @{
 * @brief Define BLE Privacy definitions, structures, and functions.
 * @}
 */

#ifndef __BLE_PRIVACY_H__
#define __BLE_PRIVACY_H__


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
/**
 * @defgroup ble_privacy_param BLE Privacy Parameter Definition
 * @{
 * @ingroup ble_privacy
 * @brief Define BLE privacy parameter definition.
 */
typedef uint8_t ble_privacy_param_t;

#define BLE_PRIVACY_PARAM_FLD_ENABLE            0x01  /**< Bit field mask for the privacy enable/disable state. */
#define BLE_PRIVACY_PARAM_DISABLE               0x00  /**< Privacy is disabled (enable bit cleared). */
#define BLE_PRIVACY_PARAM_ENABLE                0x01  /**< Privacy is enabled (enable bit set). */

#define BLE_PRIVACY_PARAM_FLD_MODE              0x02  /**< Bit field mask for the privacy address mode. */
#define BLE_PRIVACY_PARAM_MODE_NETWORK          0x00  /**< Network Privacy Mode (mode bit cleared). */
#define BLE_PRIVACY_PARAM_MODE_DEVICE           0x02  /**< Device Privacy Mode (mode bit set). */

#define BLE_PRIVACY_PARAM_FLD_LL_PRIVACY        0x04  /**< Bit field mask for the LL Privacy support state. */
#define BLE_PRIVACY_PARAM_LL_PRIVACY_OFF        0x00  /**< LL_Privacy (link layer address resolution) is not supported. */
#define BLE_PRIVACY_PARAM_LL_PRIVACY_ON         0x04  /**< LL_Privacy (link layer address resolution) is supported. */

#define BLE_PRIVACY_PARAM_FLD_RESERVED          0xF8  /**< Reserved bits, not used. */
/** @} */

/** @defgroup ble_privacy_addr_sub_type BLE Random Address Sub-type Definition
 * @{
 * @ingroup ble_privacy
 * @details Define the sub-type field carried in the two most-significant bits of a random device
 *          address, used to classify the address as static, resolvable private, or
 *          non-resolvable private.
 */
#define BLE_ADDR_SUB_TYPE_FLD_RANDOM            0xC0  /**< Bit mask for extracting the random address sub-type field. */
#define BLE_ADDR_SUB_TYPE_RANDOM                0x00  /**< Non-resolvable private address (sub-type bits = 00). */
#define BLE_ADDR_SUB_TYPE_RANDOM_RESOLVABLE     0x40  /**< Resolvable private address (sub-type bits = 01). */
#define BLE_ADDR_SUB_TYPE_RANDOM_RESERVED       0x80  /**< Reserved for future use (sub-type bits = 10). */
#define BLE_ADDR_SUB_TYPE_RANDOM_STATIC         0xC0  /**< Static device address (sub-type bits = 11). */
/** @} */


/**************************************************************************************************
 *    TYPEDEFS
 *************************************************************************************************/

/** @defgroup ble_privacy_mode BLE Privacy mode Definition
 * @{
 * @ingroup ble_privacy
 * @details  Define different BLE Privacy mode.
 */
typedef uint8_t ble_privacy_mode_t;
#define NETWORK_PRIVACY_MODE                    0x00  /**< Use network privacy mode.  */
#define DEVICE_PRIVACY_MODE                     0x01  /**< Use device privacy mode.  */
/** @} */



/** @brief Set BLE Privacy mode parameter.
 * @ingroup ble_privacy
*/
typedef struct ble_set_privacy_cfg_s
{
    uint8_t                 host_id;            /**< Host id.*/
    ble_privacy_mode_t      privacy_mode;       /**< Privacy mode selection. */
} ble_set_privacy_cfg_t;



/** @brief BLE IRK and resolvable private address parameter.
 * @ingroup ble_privacy
*/
typedef struct ble_irk_rpa_addr_s
{
    uint8_t rpa_addr[6];                        /**< Currently generated local Resolvable Private Address (RPA). */
    uint8_t irk[16];                            /**< Identity Resolving Key (IRK) used to generate and resolve the resolvable private address. */
} ble_irk_rpa_addr_t;

/**************************************************************************************************
 *    MACROS
 *************************************************************************************************/


/**************************************************************************************************
 * EXTERN DEFINITIONS
 *************************************************************************************************/

/** @brief  Pointer to the array of per-host resolvable private address and IRK parameters.
 *
 *  Indexed by host id, each entry holds the locally generated Resolvable Private Address (RPA)
 *  and the Identity Resolving Key (IRK) used to generate and resolve it for that host.
 *
 * @ingroup ble_privacy
 */
extern ble_irk_rpa_addr_t *param_rpa;

/**************************************************************************************************
 *    GLOBAL PROTOTYPES
 *************************************************************************************************/
/** @brief check if the privacy mode set to "enable".
 *
 * @ingroup ble_privacy
 *
 * @note TRUE: enable, FALSE: disable
 *
 * @return true : the privacy mode is enable. \n
 *         false : the privacy mode is disable.
 */
bool ble_privacy_parameter_enable_check(void);


/** @brief check if the privacy mode set to "Device Privacy Mode".
 *
 * @ingroup ble_privacy
 *
 * @note TRUE: Device Privacy Mode, FALSE: Network Privacy Mode
 *
 * @return true : the privacy mode is Device Privacy Mode. \n
 *         false : the privacy mode is Network Privacy Mode.
 */
bool ble_privacy_parameter_device_mode_check(void);


/** @brief check if the privacy mode set to run "LL_privacy".
 *
 * @ingroup ble_privacy
 *
 * @note TRUE: LL_privacy enable, FALSE: LL_privacy disable
 *
 * @return true : LL_privacy is enable. \n
 *         false : LL_privacy is disable.
 */
bool ble_privacy_parameter_LL_privacy_on_check(void);


/** @brief Get the host id currently associated with the privacy feature.
 *
 * @ingroup ble_privacy
 *
 * @return host_id : the host id passed to @ref ble_cmd_privacy_enable, or @ref BLE_HOSTID_RESERVED
 *                    if privacy has not been enabled.
 */
uint8_t ble_privacy_host_id_get(void);


/** @brief BLE privacy enable function.
 *
 *  Enables BLE privacy for the given host and selects its address mode (Network or Device
 *  Privacy Mode). The host must already have an IRK associated with it.
 *
 * @ingroup ble_privacy
 *
 * @note Fails with @ref BLE_ERR_INVALID_STATE if scanning, advertising, or initiating is not idle.
 * @note Fails with @ref BLE_ERR_INVALID_PARAMETER if no IRK exists for the given host id.
 *
 * @param[in] p_param : a pointer to the privacy configuration value.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_privacy_enable(ble_set_privacy_cfg_t *p_param);

/** @brief BLE privacy disable function.
 *
 *  Disables BLE privacy and clears the host id previously set by @ref ble_cmd_privacy_enable.
 *
 * @ingroup ble_privacy
 *
 * @note Fails with @ref BLE_ERR_INVALID_STATE if scanning, advertising, or initiating is not idle.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_privacy_disable(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BLE_PRIVACY_H__ */
