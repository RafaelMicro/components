# Not converted to strict includes (library-boundary rework,
# docs/internal/architecture/lib-dependencies.md): ble_fota.c unconditionally
# #include "ble_profile.h", a per-example header this library doesn't own --
# see docs/internal/adr/0003-ble-app-profile-boundary.md.
sdk_add_include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/include
)
sdk_generate_library(ble_fota)
sdk_library_add_sources_ifdef(
    CONFIG_BLUETOOTH_LE_SERVICE_FOTA ${CMAKE_CURRENT_LIST_DIR}/src/ble_fota.c
)
