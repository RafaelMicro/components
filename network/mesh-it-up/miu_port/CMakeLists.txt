# ========================================
# miu_port: auto-detect source or prebuilt lib
# ========================================

message("\t+ Configuring miu_port library")

# Select prebuilt lib by IC family
if((${CONFIG_CHIP} STREQUAL "RT581") OR (${CONFIG_CHIP} STREQUAL "RT582") OR (${CONFIG_CHIP} STREQUAL "RT583"))
    set(MIU_PORT_LIB_SUBDIR "rt58x")
elseif((${CONFIG_CHIP} STREQUAL "RT584H") OR (${CONFIG_CHIP} STREQUAL "RT584HA4") OR
       (${CONFIG_CHIP} STREQUAL "RT584L") OR (${CONFIG_CHIP} STREQUAL "RF1301"))
    set(MIU_PORT_LIB_SUBDIR "rt584")
else()
    message(FATAL_ERROR "[miu_port] Unsupported chip: ${CONFIG_CHIP}")
endif()

set(MIU_PORT_LIB_FILE ${CMAKE_CURRENT_LIST_DIR}/lib/libmiu_port_${MIU_PORT_LIB_SUBDIR}_lib.a)

# Check if source exists
file(GLOB MIU_PORT_SRC_FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/*.c
    ${CMAKE_CURRENT_LIST_DIR}/utils/*.c
    ${CMAKE_CURRENT_LIST_DIR}/crypto/*.c
)

if(MIU_PORT_SRC_FILES)
    message(STATUS "[miu_port] Source files found → build from source")

    # === Build library from source ===
    sdk_generate_library(miu_port_lib)
    set_target_properties(miu_port_lib PROPERTIES OUTPUT_NAME "miu_port_${MIU_PORT_LIB_SUBDIR}_lib")

    # Include headers
    sdk_add_include_directories(
        include
    )
    sdk_library_add_public_include_directories(include)
    sdk_add_private_include_directories(include)

    # === Source Files (hidden after build) ===
    sdk_library_add_sources(
        src/miu_alarm.c
        src/miu_crypto.c
        src/miu_diag.c
        src/miu_entropy.c
        src/miu_freertos.c
        src/miu_logging.c
        src/miu_misc.c
        src/miu_radio.c
        src/miu_settings.c
        src/miu_uart.c
        src/miu_ext_mem.c
    )

    sdk_library_add_sources(
        utils/mac_frame.cpp
        utils/mac_frame_gen.c
        utils/soft_source_match_table.c
    )

    sdk_library_add_sources(
        crypto/aes_alt.c
        crypto/ecjpake_alt.c
        crypto/sha256_alt.c
    )

    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    # mbedtls's own include path is injected via a plain (non-sdk_*)
    # add_compile_options() in components/network/thread/CMakeLists.txt, so it
    # bypasses sdk_intf_includes entirely and needs no declaration here.
    #
    # miu_openthread's own include paths, and the generated miu_bin_version.h,
    # are published bare/unowned by the parent components/network/mesh-it-up/
    # CMakeLists.txt (same pattern as OpenThread's bare paths for
    # openthread_port) -- no real CMake target to depend on, so declared
    # directly. miu_port is a direct subdirectory of mesh-it-up, so its own
    # binary dir is one level below mesh-it-up's.
    sdk_add_private_include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/../miu_openthread/include/openthread
        ${CMAKE_CURRENT_LIST_DIR}/../miu_openthread/include/openthread/platform
        ${CMAKE_CURRENT_LIST_DIR}/../miu_openthread/src/core
        ${CMAKE_CURRENT_LIST_DIR}/../miu_openthread/src/core/config
        ${CMAKE_CURRENT_LIST_DIR}/../miu_openthread/src
        ${CMAKE_CURRENT_BINARY_DIR}/..
    )
    if(CONFIG_FREERTOS)
        sdk_library_depends_on(sdk::freertos)
    endif()
    sdk_library_depends_on(sdk::soc_driver sdk::hosal log lmac15p4 utility)
    if(CONFIG_BUILD_COMPONENT_SUBG_CTRL)
        sdk_library_depends_on(subg_ctrl)
    endif()
    if(CONFIG_BUILD_COMPONENT_ENHANCED_FLASH_DATASET)
        sdk_library_depends_on(EnhancedFlashDataset)
    endif()
    if(CONFIG_BUILD_COMPONENT_CLI)
        sdk_library_depends_on(cli)
    endif()
    sdk_library_strict_includes()

else()
    if(EXISTS ${MIU_PORT_LIB_FILE})
        get_filename_component(MIU_PORT_LIB_FILE_ABS ${MIU_PORT_LIB_FILE} ABSOLUTE)
        message(STATUS "[miu_port] Prebuilt lib found → use prebuilt lib: ${MIU_PORT_LIB_FILE_ABS}")

        add_library(miu_port_lib INTERFACE IMPORTED GLOBAL)
        set_target_properties(miu_port_lib PROPERTIES
            INTERFACE_LINK_OPTIONS "-Wl,--whole-archive;${MIU_PORT_LIB_FILE_ABS};-Wl,--no-whole-archive"
        )
        sdk_add_include_directories(include)
    else()
        message(FATAL_ERROR "[miu_port] ERROR: No source and no lib found!")
    endif()
endif()
