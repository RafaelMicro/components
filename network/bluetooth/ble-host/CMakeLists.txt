
# Not converted to strict includes (library-boundary rework,
# docs/internal/architecture/lib-dependencies.md): lib-host/src/{host_management,task_host}.c
# unconditionally #include "ble_profile.h", a per-example header this library
# doesn't own -- see docs/internal/adr/0003-ble-app-profile-boundary.md.

# Source-vs-prebuilt detection assumes docs/SDK_Release/ignore/release_sqc_com_dev_ignore_files.txt
# strips exactly hci/src/ and lib-host/ for a source-less release -- keep both in sync.
file(GLOB BLE_HOST_SRC_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_LIST_DIR}/hci/src/*.c
    ${CMAKE_CURRENT_LIST_DIR}/lib-host/src/*.c
)

if((${CONFIG_CHIP} STREQUAL "RT582") OR (${CONFIG_CHIP} STREQUAL "RT581") OR (${CONFIG_CHIP} STREQUAL "RT583"))
    set(BLE_HOST_PREBUILT_LIB ${CMAKE_CURRENT_LIST_DIR}/libCM3_ble_host.a)
elseif((${CONFIG_CHIP} STREQUAL "RF1301") OR (${CONFIG_CHIP} STREQUAL "RT584H") OR (${CONFIG_CHIP} STREQUAL "RT584HA4") OR (${CONFIG_CHIP} STREQUAL "RT584L"))
    set(BLE_HOST_PREBUILT_LIB ${CMAKE_CURRENT_LIST_DIR}/libCM33_ble_host.a)
endif()

if(BLE_HOST_SRC_FILES)
    sdk_add_include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/fota/include
        ${CMAKE_CURRENT_LIST_DIR}/uecc
    )

    if((${CONFIG_CHIP} STREQUAL "RT582") OR (${CONFIG_CHIP} STREQUAL "RT581") OR (${CONFIG_CHIP} STREQUAL "RT583"))
         sdk_generate_library(CM3_ble_host)
    elseif((${CONFIG_CHIP} STREQUAL "RF1301") OR (${CONFIG_CHIP} STREQUAL "RT584H") OR (${CONFIG_CHIP} STREQUAL "RT584HA4") OR (${CONFIG_CHIP} STREQUAL "RT584L"))
         sdk_generate_library(CM33_ble_host)
    endif()

    sdk_add_include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/ble-cmd-api/include
        ${CMAKE_CURRENT_LIST_DIR}/hci/include
        ${CMAKE_CURRENT_LIST_DIR}/lib-host/include
    )
    sdk_library_add_sources(
        ${CMAKE_CURRENT_LIST_DIR}/hci/src/hci_cmd_advertising.c
        ${CMAKE_CURRENT_LIST_DIR}/hci/src/hci_cmd_extended_advertising.c
        ${CMAKE_CURRENT_LIST_DIR}/hci/src/hci_cmd_connect_cte.c
        ${CMAKE_CURRENT_LIST_DIR}/hci/src/hci_cmd_connect.c
        ${CMAKE_CURRENT_LIST_DIR}/hci/src/hci_cmd_controller.c
        ${CMAKE_CURRENT_LIST_DIR}/hci/src/hci_cmd_privacy.c
        ${CMAKE_CURRENT_LIST_DIR}/hci/src/hci_cmd_scan.c
        ${CMAKE_CURRENT_LIST_DIR}/hci/src/hci_cmd_security.c
        ${CMAKE_CURRENT_LIST_DIR}/hci/src/hci_cmd_vendor.c
        ${CMAKE_CURRENT_LIST_DIR}/hci/src/hci_event.c

        ${CMAKE_CURRENT_LIST_DIR}/lib-host/src/att.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-host/src/ble_api.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-host/src/ble_bonding_storage.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-host/src/ble_event_module.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-host/src/ble_lesc.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-host/src/ble_memory.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-host/src/host_management.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-host/src/l2cap.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-host/src/smp.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-host/src/sec_aes_cmac.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-host/src/sec_aes.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-host/src/task_host.c
        ${CMAKE_CURRENT_LIST_DIR}/lib-host/src/task_host_tx.c

        ${CMAKE_CURRENT_LIST_DIR}/uecc/uECC.c
    )
elseif(DEFINED BLE_HOST_PREBUILT_LIB AND EXISTS ${BLE_HOST_PREBUILT_LIB})
    if((${CONFIG_CHIP} STREQUAL "RT582") OR (${CONFIG_CHIP} STREQUAL "RT581") OR (${CONFIG_CHIP} STREQUAL "RT583"))
         sdk_add_static_library(CM3_ble_host)
    elseif((${CONFIG_CHIP} STREQUAL "RF1301") OR (${CONFIG_CHIP} STREQUAL "RT584H") OR (${CONFIG_CHIP} STREQUAL "RT584HA4") OR (${CONFIG_CHIP} STREQUAL "RT584L"))
        sdk_add_static_library(CM33_ble_host)
    endif()

    sdk_add_include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/ble-cmd-api/include
        ${CMAKE_CURRENT_LIST_DIR}/hci/include
        ${CMAKE_CURRENT_LIST_DIR}/fota/include
        ${CMAKE_CURRENT_LIST_DIR}/uecc
    )
else()
    message(FATAL_ERROR "[ble-host] No source and no prebuilt lib found!")
endif()

sdk_add_subdirectory_ifdef(CONFIG_BUILD_COMPONENT_BLUETOOTH_LE_HOST ${CMAKE_CURRENT_LIST_DIR}/ble-cmd-api)
sdk_add_subdirectory_ifdef(CONFIG_BUILD_COMPONENT_BLUETOOTH_LE_HOST ${CMAKE_CURRENT_LIST_DIR}/ble-service)
sdk_add_subdirectory_ifdef(CONFIG_BLUETOOTH_LE_SERVICE_FOTA ${CMAKE_CURRENT_LIST_DIR}/fota)
