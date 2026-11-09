# sdk_generate_component_tag()
if (CONFIG_HOSAL_SOC_IDLE_SLEEP)
sdk_generate_library(zboss_port_rfd)
else()
sdk_generate_library(zboss_port_ffd)
endif()

sdk_add_include_directories(
    include
)
sdk_add_private_include_directories(
    include
    ${CMAKE_CURRENT_LIST_DIR}/../zboss/include
    ${CMAKE_CURRENT_LIST_DIR}/../zboss/include/ha
    ${CMAKE_CURRENT_LIST_DIR}/../zboss/include/zcl
)

sdk_library_add_sources(
    src/zb_crypto.c
    src/zb_freertos.c
    src/zb_nvram.c
    src/zb_powersaving.c
    src/zb_radio.c
    src/zb_serial.c
    src/zb_timer.c
)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
# zboss/include's own paths are published bare by the parent
# components/network/zigbee/CMakeLists.txt (same pattern as OpenThread's own
# paths for openthread_port) -- declared directly above since there's no real
# CMake target to depends_on() for them.
sdk_library_depends_on(sdk::soc_driver sdk::hosal log lmac15p4 fota_define utility)
if(CONFIG_FREERTOS)
    sdk_library_depends_on(sdk::freertos)
endif()
sdk_library_strict_includes()

if (CONFIG_HOSAL_SOC_IDLE_SLEEP)
    add_definitions(
        -DZB_ED_ROLE
        -DZB_USE_SLEEP
    )
else()
endif()