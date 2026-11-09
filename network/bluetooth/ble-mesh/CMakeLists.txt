
sdk_generate_library(ble_mesh_api)
sdk_add_include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/ble-mesh-api/include
)
sdk_library_add_sources(
    ${CMAKE_CURRENT_LIST_DIR}/ble-mesh-api/src/ble_mesh_lib_api.c
)

# Source-vs-prebuilt detection assumes docs/SDK_Release/ignore/release_sqc_com_dev_ignore_files.txt
# strips every lib-ble-mesh/**/src/ directory for a source-less release -- keep both in sync.
file(GLOB_RECURSE BLE_MESH_SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/*.c)

if((${CONFIG_CHIP} STREQUAL "RT582") OR (${CONFIG_CHIP} STREQUAL "RT581") OR (${CONFIG_CHIP} STREQUAL "RT583"))
    set(BLE_MESH_SERVER_PREBUILT_LIB ${CMAKE_CURRENT_LIST_DIR}/libCM3_ble_mesh_server.a)
    set(BLE_MESH_CLIENT_PREBUILT_LIB ${CMAKE_CURRENT_LIST_DIR}/libCM3_ble_mesh_client.a)
elseif((${CONFIG_CHIP} STREQUAL "RT584H") OR (${CONFIG_CHIP} STREQUAL "RT584HA4") OR (${CONFIG_CHIP} STREQUAL "RT584L"))
    set(BLE_MESH_SERVER_PREBUILT_LIB ${CMAKE_CURRENT_LIST_DIR}/libCM33_ble_mesh_server.a)
    set(BLE_MESH_CLIENT_PREBUILT_LIB ${CMAKE_CURRENT_LIST_DIR}/libCM33_ble_mesh_client.a)
endif()

set(BLE_MESH_PREBUILT_OK TRUE)
if(NOT DEFINED BLE_MESH_SERVER_PREBUILT_LIB)
    set(BLE_MESH_PREBUILT_OK FALSE)
elseif(CONFIG_SUPPORT_MESH_SERVER AND NOT EXISTS ${BLE_MESH_SERVER_PREBUILT_LIB})
    set(BLE_MESH_PREBUILT_OK FALSE)
elseif(CONFIG_SUPPORT_MESH_CLIENT AND NOT EXISTS ${BLE_MESH_CLIENT_PREBUILT_LIB})
    set(BLE_MESH_PREBUILT_OK FALSE)
elseif(NOT CONFIG_SUPPORT_MESH_SERVER AND NOT CONFIG_SUPPORT_MESH_CLIENT)
    set(BLE_MESH_PREBUILT_OK FALSE)
endif()

if(BLE_MESH_SRC_FILES)
    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    # ble_mesh_api is the one BLE library in this tree that's actually
    # self-contained -- see the round-9 memory note: every other BLE host/mesh
    # library (CM3_ble_host, ble_cmd_api, ble_service, ble_fota,
    # CM3_ble_mesh_server/client, ble_mesh_model) unconditionally #includes a
    # per-example "ble_profile.h"/"product_config.h" it doesn't own, so those are
    # deliberately left non-strict this round. lib-ble-mesh/pib/include and
    # model/common/include are published bare by this file (below) and by
    # model/CMakeLists.txt -- declared directly, same pattern as elsewhere.
    sdk_add_private_include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/ble-mesh-api/include
        ${CMAKE_CURRENT_LIST_DIR}/../ble-host/ble-cmd-api/include
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/pib/include
        ${CMAKE_CURRENT_LIST_DIR}/model/common/include
    )
    sdk_library_depends_on(sdk::soc_driver log)
    if(CONFIG_FREERTOS)
        sdk_library_depends_on(sdk::freertos)
    endif()
    sdk_library_strict_includes()

    # CM3/CM33_ble_mesh_server/client not converted to strict includes
    # (library-boundary rework, docs/internal/architecture/lib-dependencies.md): most of
    # lib-ble-mesh/**/*.c unconditionally #include "ble_profile.h" (and pib.c
    # also "product_config.h"), per-example headers this library doesn't own --
    # see docs/internal/adr/0003-ble-app-profile-boundary.md.
    if (CONFIG_SUPPORT_MESH_SERVER)
    if((${CONFIG_CHIP} STREQUAL "RT582") OR (${CONFIG_CHIP} STREQUAL "RT581") OR (${CONFIG_CHIP} STREQUAL "RT583"))
        sdk_generate_library(CM3_ble_mesh_server)
    elseif((${CONFIG_CHIP} STREQUAL "RT584H") OR (${CONFIG_CHIP} STREQUAL "RT584HA4") OR (${CONFIG_CHIP} STREQUAL "RT584L"))
        sdk_generate_library(CM33_ble_mesh_server)
    endif()
    elseif (CONFIG_SUPPORT_MESH_CLIENT)
    if((${CONFIG_CHIP} STREQUAL "RT582") OR (${CONFIG_CHIP} STREQUAL "RT581") OR (${CONFIG_CHIP} STREQUAL "RT583"))
        sdk_generate_library(CM3_ble_mesh_client)
    elseif((${CONFIG_CHIP} STREQUAL "RT584H") OR (${CONFIG_CHIP} STREQUAL "RT584HA4") OR (${CONFIG_CHIP} STREQUAL "RT584L"))
        sdk_generate_library(CM33_ble_mesh_client)
    endif()
    endif()

    sdk_library_add_sources(
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/mib/src/mib_counter.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/pib/src/pib.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/pib/src/pib_flash.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/prod/src/prod_data.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/beacon/src/bcn_data.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/beacon/src/bcn_main.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/bearer/src/bar_data.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/bearer/src/bar_main.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/bearer/src/bar_pb_adv.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/bearer/src/bar_pb_gatt.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/bearer/src/bar_rx.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/bearer/src/bar_tx.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/bearer/src/bar_tx_fsm.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/config-model/src/cfg_mdl.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/config-model/src/cfg_mdl_cl.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/config-model/src/cfg_mdl_data.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/config-model/src/cfg_mdl_messages.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/config-model/src/cfg_mdl_mib.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/config-model/src/cfg_mdl_sr.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/config-model/src/cfg_mdl_sr_app_key.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/config-model/src/cfg_mdl_sr_app_net_key.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/config-model/src/cfg_mdl_sr_friend.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/config-model/src/cfg_mdl_sr_main.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/config-model/src/cfg_mdl_sr_subscr.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/dsm/src/device_state_manager.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/dsm/src/dsm_appkey.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/dsm/src/dsm_netkey.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/dsm/src/dsm_pul.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/dsm/src/dsm_sur.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/friend/src/friend.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/friend/src/friend_queue.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/friend/src/friend_sublist.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/lower-Layer/src/lower_layer.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/lprn/src/lpn.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/lprn/src/lpn_sub_mgmt.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/network/src/cache.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/network/src/net_pkt.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/network/src/net_state.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/network/src/network.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/provision/src/prv_api.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/provision/src/prv_cl.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/provision/src/prv_data.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/provision/src/prv_main.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/provision/src/prv_rx.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/provision/src/prv_sr.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/provision/src/prv_tx.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/proxy/src/proxy.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/proxy/src/proxy_filter.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/security/src/sec_aes_ccm.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/security/src/sec_keygen.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/security/src/sec_main.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/transport/src/transport.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/upper-layer/src/hb_main.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/upper-layer/src/ht_main.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/upper-layer/src/upper_layer.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/task/src/cmd_handle.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/task/src/mesh_api.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/task/src/mesh_task.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/task/src/sys_log.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/task/src/sys_log_bearer.c
    )
elseif(BLE_MESH_PREBUILT_OK)
    if((${CONFIG_CHIP} STREQUAL "RT582") OR (${CONFIG_CHIP} STREQUAL "RT581") OR (${CONFIG_CHIP} STREQUAL "RT583"))
        sdk_add_static_library_ifdef(CONFIG_SUPPORT_MESH_SERVER CM3_ble_mesh_server)
        sdk_add_static_library_ifdef(CONFIG_SUPPORT_MESH_CLIENT CM3_ble_mesh_client)
    elseif((${CONFIG_CHIP} STREQUAL "RT584H") OR (${CONFIG_CHIP} STREQUAL "RT584HA4") OR (${CONFIG_CHIP} STREQUAL "RT584L"))
        sdk_add_static_library_ifdef(CONFIG_SUPPORT_MESH_SERVER CM33_ble_mesh_server)
        sdk_add_static_library_ifdef(CONFIG_SUPPORT_MESH_CLIENT CM33_ble_mesh_client)
    endif()
else()
    message(FATAL_ERROR "[ble-mesh] No source and no prebuilt lib found!")
endif()

sdk_add_include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/mib/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/pib/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/prod/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/beacon/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/bearer/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/config-model/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/dsm/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/friend/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/lower-Layer/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/lprn/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/network/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/provision/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/proxy/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/security/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/security/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/security/bearssl/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/security/ecdh/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/transport/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/profile/upper-layer/include
    ${CMAKE_CURRENT_LIST_DIR}/lib-ble-mesh/task/include
)

sdk_add_subdirectory_ifdef(CONFIG_BUILD_COMPONENT_BLUETOOTH_LE_MESH ${CMAKE_CURRENT_LIST_DIR}/model)
