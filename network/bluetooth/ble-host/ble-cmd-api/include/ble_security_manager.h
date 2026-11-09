/*
 * Copyright (c) 2022-2025 Rafael Microelectronics Inc. All rights reserved.
 * 
 * SPDX-License-Identifier: LicenseRef-RafaelMicro-Proprietary-1.0
 *
 */

/** @file ble_security_manager.h
 *
 * @brief BLE security manager header file.
 *
 */

/**
 * @defgroup ble_sec BLE Security Management
 * @ingroup BLE_group
 * @{
 * @brief Define BLE Security definitions, structures, and functions.
 * @}
 */

#ifndef __BLE_SECURITY_MANAGER_H__
#define __BLE_SECURITY_MANAGER_H__

/**************************************************************************************************
 *    INCLUDES
 *************************************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include "ble_api.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**************************************************************************************************
 *    TYPEDEFS
 *************************************************************************************************/

/**
 * @defgroup ble_sec_key_gen_method BLE Security key generation method Definition
 * @{
 * @ingroup ble_sec
 * @details Define the legacy pairing STK (Short Term Key) generation method reported by
 *          @ref ble_evt_sm_stk_gen_method_t "the STK generation method event". It tells the
 *          local device whether it must ask the user to enter a passkey or generate and
 *          display one, based on the negotiated IO capabilities of both devices.
 */
typedef uint8_t ble_sm_key_gen_method_t;
#define PASSKEY_ENTRY                               0x01    /**< The local device must prompt the user to enter the passkey displayed on the peer device. */
#define PASSKEY_DISPLAY                             0x02    /**< The local device must generate and display a passkey for the user to enter on the peer device. */
/** @} */


/**
 * @defgroup ble_sec_io_caps BLE Security IO Capabilities Definition
 * @{
 * @ingroup ble_sec
 * @details Define the local device's SMP IO capability, as set by @ref ble_cmd_io_capability_set.
 *          Together with the peer's IO capability, this determines the pairing association
 *          model used (Just Works, Passkey Entry, or Numeric Comparison) and whether the
 *          resulting pairing is MITM-protected.
 */
typedef uint8_t io_caps_t;
#define DISPLAY_ONLY                                 0x00  /**< Device has a display but no input capability (e.g. no buttons/keyboard). */
#define DISPLAY_YESNO                                0x01  /**< Device has a display and can accept a Yes/No user confirmation input.    */
#define KEYBOARD_ONLY                                0x02  /**< Device has a keyboard (or numeric input) but no display.                 */
#define NOINPUT_NOOUTPUT                             0x03  /**< Device has neither a display nor any input capability.                   */
#define KEYBOARD_DISPLAY                             0x04  /**< Device has both a keyboard (or numeric input) and a display.             */
/** @} */


/**
 * @defgroup ble_sec_flag BLE Bonding Flag Definition
 * @{
 * @ingroup ble_sec
 * @details Define the bonding flag used by @ref ble_cmd_bonding_flag_set to control whether
 *          the security keys generated during pairing are stored for future reconnection.
 */
typedef uint8_t bonding_flag_t;
#define NO_BONDING                                   0x00  /**< Do not bond; pairing keys are not stored after the link is disconnected. */
#define BONDING                                      0x01  /**< Bond; pairing keys are stored so the peer can reconnect without re-pairing. */
/** @} */


/**
 * @brief BLE security request parameter.
 * @ingroup ble_sec
 */
typedef struct
{
    uint8_t   host_id;                          /**< The link's host ID. */
} ble_sm_security_request_param_t;


/**
 * @brief BLE restore cccd parameter.
 * @ingroup ble_sec
 */
typedef struct
{
    uint8_t   host_id;                          /**< The link's host ID. */
} ble_sm_restore_cccd_param_t;


/**
 * @brief BLE passkey parameter.
 * @ingroup ble_sec
 */
typedef struct
{
    uint8_t   host_id;                          /**< The link's host ID. */
    uint32_t  passkey;                          /**< The 6-digit passkey value (000000-999999) entered by the user, in response to a @ref BLE_SM_EVT_STK_GENERATION_METHOD event with @ref PASSKEY_ENTRY method. */
} ble_sm_passkey_param_t;

/**
 * @brief BLE numeric comparison parameter.
 * @ingroup ble_sec
 */
typedef struct
{
    uint8_t   host_id;                          /**< The link's host ID. */
    uint8_t   same_numeric;                     /**< User confirmation result for LESC numeric comparison: non-zero (TRUE) if the value shown on both devices matched (accept pairing), 0 (FALSE) if they did not match (reject pairing). */
} ble_sm_numeric_comp_result_param_t;

/**
 * @brief BLE io capabilities parameter.
 * @ingroup ble_sec
 */
typedef struct
{
    io_caps_t          io_caps_param;           /**< @ref io_caps_t "IO capabilities". */

} ble_sm_io_cap_param_t;


/**
 * @brief BLE bonding flag parameter.
 * @ingroup ble_sec
 */
typedef struct
{
    bonding_flag_t     bonding_flag;            /**< @ref bonding_flag_t "Bonding flags". */

} ble_sm_bonding_flag_param_t;


/**
 * @brief BLE identity resolving key parameter.
 * @ingroup ble_sec
 */
typedef struct
{
    uint8_t   irk[16];                          /**< 128-bit Identity Resolving Key (IRK), used to generate and resolve Resolvable Private Addresses (RPA). */
} ble_sm_irk_param_t;


/**
 * @brief STK Generator Method Event Parameters.
 * @ingroup ble_sec
*/
typedef struct __attribute__((packed)) ble_evt_sm_stk_gen_method_s
{
    uint8_t                   host_id;          /**< The link's host ID. */
    ble_sm_key_gen_method_t   key_gen_method;   /**< STK generation method the local device must perform: @ref PASSKEY_ENTRY or @ref PASSKEY_DISPLAY. */
} ble_evt_sm_stk_gen_method_t;


/**
 * @brief Passkey Confirmation Event Parameters.
 * @ingroup ble_sec
*/
typedef struct __attribute__((packed)) ble_evt_sm_passkey_confirm_param_s
{
    uint8_t      host_id;               /**< The link's host ID; the application should obtain a passkey from the user and submit it via @ref ble_cmd_passkey_set. */
} ble_evt_sm_passkey_confirm_param_t;

/**
 * @brief Numeric Comparison Event Parameters.
 * @ingroup ble_sec
*/
typedef struct __attribute__((packed)) ble_evt_sm_numeric_comparison_param_t
{
    uint8_t      host_id;               /**< The link's host ID. */
    uint32_t     comparison_value;      /**< 6-digit LESC numeric comparison value to display to the user; the application must confirm whether it matches the value displayed on the peer via @ref ble_cmd_numeric_comp_result_set. */
} ble_evt_sm_numeric_comparison_param_t;


/**
 * @brief Authentication Event Parameters.
 * @ingroup ble_sec
*/
typedef struct __attribute__((packed)) ble_evt_sm_auth_status_s
{
    uint8_t      host_id;               /**< The link's host ID. */
    uint8_t      status;                /**< Pairing/authentication result: BLE_HCI_ERR_CODE_SUCCESS (0x00) if pairing completed successfully, otherwise an HCI/SMP error code indicating the failure reason. */
    uint8_t      lesc: 1;               /**< Set to 1 if the pairing used LE Secure Connections (LESC); 0 if legacy pairing was used. */
    uint8_t      reserved: 7;           /**< Reserved for future use. */
} ble_evt_sm_auth_status_t;


/**
 * @brief Resolving Private Address Fail Status Event Parameters.
 * @ingroup ble_sec
*/
typedef struct __attribute__((packed)) ble_evt_sm_irk_resolving_fail_s
{
    uint8_t      host_id;               /**< The link's host ID for which resolving the peer's Resolvable Private Address (RPA) using the stored IRK failed. */
} ble_evt_sm_irk_resolving_fail_t;

/**
 * @brief BLE IO Capabilities event parameter.
 * @ingroup ble_sec
 *
 * @note Reserved for future use: no event code currently reports this member through
 *       @ref ble_evt_sm_handler; the local IO capability is instead configured via
 *       @ref ble_cmd_io_capability_set.
*/
typedef struct __attribute__((packed)) ble_evt_sm_io_cap_s
{
    io_caps_t          io_caps_param;           /**< @ref io_caps_t "IO capabilities". */

} ble_evt_sm_io_cap_t;


/** @brief BLE Bonding Flags event parameter.
 * @ingroup ble_sec
 *
 * @note Reserved for future use: no event code currently reports this member through
 *       @ref ble_evt_sm_handler; the bonding flag is instead set via
 *       @ref ble_cmd_bonding_flag_set.
*/
typedef struct __attribute__((packed)) ble_evt_sm_bonding_flag_s
{
    bonding_flag_t     bonding_flag;            /**< @ref bonding_flag_t "Bonding flags". */

} ble_evt_sm_bonding_flag_t;


/**
 * @brief BLE Security Manager Event Parameters.
 * @ingroup ble_sec
*/
typedef struct ble_evt_sm_s
{
    union
    {
        ble_evt_sm_stk_gen_method_t           evt_stk_gen_method;           /**< STK generation method event parameters. */
        ble_evt_sm_passkey_confirm_param_t    evt_passkey_confirm_param;    /**< Passkey confirmation event parameters. */
        ble_evt_sm_numeric_comparison_param_t evt_numeric_comparison_param; /**< Numeric Comparison event parameters. */
        ble_evt_sm_auth_status_t              evt_auth_status;              /**< Authentication event parameters. */
        ble_evt_sm_irk_resolving_fail_t       evt_irk_resolving_fail;       /**< Resolving private address fail status event parameters. */
        ble_evt_sm_io_cap_t                   evt_io_caps;                  /**< IO Capabilities event parameters. */
        ble_evt_sm_bonding_flag_t             evt_bonding_flag;             /**< Bonding flag event parameters. */
    } param;                                                                /**< Event parameters. */

} ble_evt_sm_t;

/**************************************************************************************************
 *    MACROS
 *************************************************************************************************/


/**************************************************************************************************
 *    GLOBAL PROTOTYPES
 *************************************************************************************************/

/** @brief Send an SMP security request.
 *
 *  Sends a Security Request PDU to the peer of the specified link, asking it to initiate
 *  pairing or re-establish encryption. Typically used by a peripheral that cannot itself
 *  initiate pairing.
 *
 * @ingroup ble_sec
 *
 * @note Returns @ref BLE_ERR_INVALID_HOST_ID if host_id is not a valid host ID, or
 *       @ref BLE_ERR_INVALID_STATE if the link is not currently connected.
 *
 * @param[in] host_id : The link's host ID.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_security_request_set(uint8_t host_id);


/** @brief Set the BLE pairing passkey value.
 *
 *  Submits the passkey (entered by the user) to the stack to continue legacy or LESC
 *  passkey-entry pairing, in response to a @ref BLE_SM_EVT_STK_GENERATION_METHOD event
 *  reporting @ref PASSKEY_ENTRY.
 *
 * @ingroup ble_sec
 *
 * @note Returns @ref BLE_ERR_INVALID_PARAMETER if p_param is NULL, @ref BLE_ERR_INVALID_HOST_ID
 *       if the host ID is invalid, @ref BLE_ERR_INVALID_STATE if the link is not connected, or
 *       @ref BLE_BUSY if the passkey could not be forwarded to the stack.
 *
 * @param[in] p_param : a pointer to the passkey parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_passkey_set(ble_sm_passkey_param_t *p_param);


/** @brief Set the BLE numeric comparison result value.
 *
 *  Submits the user's confirmation of whether the numeric comparison value matched the
 *  peer's, in response to a @ref BLE_SM_EVT_NUMERIC_COMPARISON event during LESC pairing.
 *
 * @ingroup ble_sec
 *
 * @note Returns @ref BLE_ERR_INVALID_PARAMETER if p_param is NULL, @ref BLE_ERR_INVALID_HOST_ID
 *       if the host ID is invalid, @ref BLE_ERR_INVALID_STATE if the link is not connected, or
 *       @ref BLE_BUSY if the result could not be forwarded to the stack.
 *
 * @param[in] p_param : a pointer to the numeric comparison result parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_numeric_comp_result_set(ble_sm_numeric_comp_result_param_t *p_param);


/** @brief Set the local BLE IO capabilities.
 *
 *  Configures the IO capability used for future pairing procedures, determining the
 *  association model (Just Works, Passkey Entry, or Numeric Comparison) negotiated with peers.
 *
 * @ingroup ble_sec
 *
 * @note Must be called while advertising, scanning, and initiating are all idle and there are
 *       no active connections (e.g. during initialization), otherwise @ref BLE_ERR_INVALID_STATE
 *       is returned. Returns @ref BLE_ERR_INVALID_PARAMETER if io_caps_param is not one of the
 *       @ref ble_sec_io_caps "defined IO capability values".
 *
 * @param[in] p_param : a pointer to the IO capability parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_io_capability_set(ble_sm_io_cap_param_t *p_param);


/** @brief Set the BLE bonding flag.
 *
 *  Configures whether keys generated by future pairing procedures are bonded (stored for
 *  reconnection) or not.
 *
 * @ingroup ble_sec
 *
 * @note Must be called while advertising, scanning, and initiating are all idle and there are
 *       no active connections (e.g. during initialization), otherwise @ref BLE_ERR_INVALID_STATE
 *       is returned. Returns @ref BLE_ERR_INVALID_PARAMETER if bonding_flag is neither
 *       @ref NO_BONDING nor @ref BONDING.
 *
 * @param[in] p_param : a pointer to the bonding parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_bonding_flag_set(ble_sm_bonding_flag_param_t *p_param);


/** @brief Restore the BLE bonding CCCD.
 *
 *  Restores the Client Characteristic Configuration Descriptor (CCCD/notification and
 *  indication subscription) state saved from a previous bond for a reconnected, previously
 *  bonded peer. Typically called after a successful @ref BLE_SM_EVT_AUTH_STATUS event.
 *
 * @ingroup ble_sec
 *
 * @note Returns @ref BLE_ERR_INVALID_HOST_ID if host_id is not a valid host ID, or
 *       @ref BLE_ERR_INVALID_STATE if the link is not currently connected.
 *
 * @param[in] host_id : The link's host ID.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_cccd_restore(uint8_t host_id);


/** @brief Initialize the bonding information storage space.
 *
 *  Initializes the storage space used to hold bonded peers' security keys (e.g. LTK, IRK) and
 *  CCCD state.
 *
 * @ingroup ble_sec
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_bonding_space_init(void);


/** @brief Write the BLE Identity Resolving Key.
 *
 *  Writes the Identity Resolving Key (IRK) used by the BLE security module to generate and
 *  resolve Resolvable Private Addresses (RPA).
 *
 * @ingroup ble_sec
 *
 * @note Must be called while advertising, scanning, and initiating are all idle and there are
 *       no active connections (e.g. during initialization), otherwise @ref BLE_ERR_INVALID_STATE
 *       is returned.
 *
 * @param[in] p_param : a pointer to the identity resolving key parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_write_identity_resolving_key(ble_sm_irk_param_t *p_param);



/** @brief Initialize LE Secure Connections.
 *
 *  Initializes LE Secure Connections (LESC) pairing support. Typically called once during
 *  BLE stack initialization, before any pairing procedure takes place.
 *
 * @ingroup ble_sec
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_lesc_init(void);


/** @brief Enable or disable LE Secure Connections Debug Mode.
 *
 *  When enabled, future LESC key pair generation (see @ref ble_cmd_lesc_init) uses the
 *  publicly documented Bluetooth SIG debug key pair instead of a randomly generated one, so
 *  a protocol analyzer that also knows this key (e.g. Wireshark/Ellisys) can decrypt and
 *  verify this device's LESC pairing exchanges. Call before @ref ble_cmd_lesc_init (or before
 *  the next pairing) so the fixed key pair is in place before it's needed; if a key pair
 *  already exists, enabling it takes effect immediately.
 *
 * @ingroup ble_sec
 *
 * @warning Never enable this in a production build -- it makes every LESC pairing this
 *          device performs trivially observable to anyone who also knows the debug key.
 *
 * @param[in] enable : true to use the debug key pair, false to return to random key pairs
 *                     (takes effect on the next LESC key pair generation).
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_cmd_lesc_debug_mode_set(bool enable);


/** @brief Query whether LE Secure Connections Debug Mode is currently enabled.
 *
 * @ingroup ble_sec
 *
 * @return true if debug mode is enabled, false otherwise.
 */
bool ble_cmd_lesc_debug_mode_get(void);


/** @brief BLE security manager event handler.
 *
 *  Dispatches security manager (SM) events - STK generation method, passkey confirmation,
 *  numeric comparison, authentication status, and IRK resolving failure - to the
 *  application's registered event callback.
 *
 * @ingroup ble_sec
 *
 * @param[in] p_param : a pointer to the @ref ble_evt_param_t event parameter.
 *
 * @return @ref BLE_ERR_OK is success or an @ref ble_err_t "error".
 */
ble_err_t ble_evt_sm_handler(void *p_param);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BLE_SECURITY_MANAGER_H__ */
