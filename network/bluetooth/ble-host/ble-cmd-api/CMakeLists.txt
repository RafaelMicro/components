sdk_generate_library(ble_cmd_api)
# Not converted to strict includes (library-boundary rework,
# docs/internal/architecture/lib-dependencies.md): ble_cmd_gap.c/ble_cmd_att_gatt.c
# unconditionally #include "ble_profile.h", a per-example header this library
# doesn't own -- see docs/internal/adr/0003-ble-app-profile-boundary.md.
sdk_add_include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/include
)
sdk_library_add_sources(
    ${CMAKE_CURRENT_LIST_DIR}/src/ble_cmd_advertising.c
    ${CMAKE_CURRENT_LIST_DIR}/src/ble_cmd_extended_advertising.c
    ${CMAKE_CURRENT_LIST_DIR}/src/ble_cmd_att_gatt.c
    ${CMAKE_CURRENT_LIST_DIR}/src/ble_cmd_common.c
    ${CMAKE_CURRENT_LIST_DIR}/src/ble_cmd_connect_cte.c
    ${CMAKE_CURRENT_LIST_DIR}/src/ble_cmd_gap.c
    ${CMAKE_CURRENT_LIST_DIR}/src/ble_cmd_l2cap.c
    ${CMAKE_CURRENT_LIST_DIR}/src/ble_cmd_privacy.c
    ${CMAKE_CURRENT_LIST_DIR}/src/ble_cmd_scan.c
    ${CMAKE_CURRENT_LIST_DIR}/src/ble_cmd_security_manager.c
    ${CMAKE_CURRENT_LIST_DIR}/src/ble_host_ref.c
)