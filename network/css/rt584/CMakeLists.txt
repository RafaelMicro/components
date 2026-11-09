sdk_generate_library(css)
sdk_add_include_directories(include)
sdk_library_add_public_include_directories(include)
sdk_add_private_include_directories(include)
sdk_library_add_sources(
    Src/uart_bridge.c
    Src/rfb_sf.c
    Src/dtm_mode.c
)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
if(CONFIG_FREERTOS)
    sdk_library_depends_on(sdk::freertos)
endif()
sdk_library_depends_on(sdk::soc_driver sdk::hosal ruci)
if(CONFIG_BUILD_COMPONENT_RT569_RF)
    sdk_library_depends_on(rt569_rf)
endif()
sdk_library_strict_includes()