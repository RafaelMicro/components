sdk_generate_library(cli)
sdk_add_include_directories(Inc)
sdk_library_add_public_include_directories(Inc)
sdk_add_private_include_directories(Inc)
sdk_library_add_sources(
    cli.c
    shell.c
)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
# Originally reverted (see docs/internal/adr/0002-six-layer-dependency-order.md) because
# <FreeRTOS.h> needs FreeRTOSConfig.h, owned per-example -- now reachable via
# sdk::freertos (sdk_set_freertos_config_directory(), extension.cmake).
# (No sdk::soc_driver: cli.c's #include "mcu.h" was dead code, removed during
# the include audit -- cli.c never actually used it.)
sdk_library_depends_on(uart_stdio sdk::freertos)
if(CONFIG_BUILD_COMPONENT_SW_TIMER)
    # cli.c's #include "sw_timer.h" pulls in "util_list.h" (owned by
    # utility), which sw_timer itself doesn't re-declare since it isn't
    # strict.
    sdk_library_depends_on(sw_timer utility)
endif()
sdk_library_strict_includes()