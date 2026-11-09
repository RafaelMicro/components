sdk_generate_library(log)
sdk_add_compile_options(-DLOG_LEVEL=${CONFIG_LOG_LEVEL})
sdk_add_include_directories(.)
sdk_library_add_public_include_directories(.)
sdk_add_private_include_directories(.)
sdk_library_add_sources(log.c)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
# log.h itself (not just log.c) #includes <FreeRTOS.h> when CONFIG_FREERTOS is
# set (see docs/internal/adr/0002-six-layer-dependency-order.md) -- sdk::freertos now
# carries the current example's FreeRTOSConfig.h (sdk_set_freertos_config_directory()).
# That FreeRTOSConfig.h in turn #includes "mcu.h" (soc driver) itself, hence
# the extra sdk::soc_driver dependency here too.
if(CONFIG_FREERTOS)
    sdk_library_depends_on(sdk::freertos sdk::soc_driver)
endif()
sdk_library_strict_includes()