sdk_generate_component_tag()

file(GLOB CPC_SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/src/*.c)

if(CPC_SRC_FILES)
    sdk_generate_library(cpc)

    sdk_add_include_directories(
        inc
        src
    )
    sdk_library_add_public_include_directories(
        inc
        src
    )
    sdk_add_private_include_directories(
        inc
        src
    )

    sdk_library_add_sources(
        src/cpc_crc.c
        src/cpc_dispatcher.c
        src/cpc_drv_secondary_uart_usart.c
        src/cpc_hdlc.c
        src/cpc_system_secondary.c
        src/cpc.c
        src/cpc_timer.c
        src/slist.c
        src/mem_pool.c
        src/cpc_memory.c
    )

    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    if(CONFIG_FREERTOS)
        sdk_library_depends_on(sdk::freertos sdk::soc_driver)
    endif()
    sdk_library_depends_on(log)
    if(CONFIG_BUILD_COMPONENT_SW_TIMER)
        sdk_library_depends_on(sw_timer)
    endif()
    sdk_library_strict_includes()
elseif(EXISTS ${CMAKE_CURRENT_LIST_DIR}/libcpc.a)
    sdk_add_static_library(cpc)
    sdk_add_include_directories(
        inc
    )
    # Strict-include dependents (e.g. openthread_port) resolve `cpc` by name and
    # only see include dirs published on the target. Imported targets are
    # directory-scoped by default, so make it GLOBAL and publish inc.
    set_target_properties(cpc PROPERTIES IMPORTED_GLOBAL TRUE
        IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libcpc.a)
    target_include_directories(cpc INTERFACE ${CMAKE_CURRENT_LIST_DIR}/inc)
else()
    message(FATAL_ERROR "[cpc] No source and no prebuilt lib found!")
endif()
