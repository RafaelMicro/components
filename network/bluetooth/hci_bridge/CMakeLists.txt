message("\t\t+ hci-bridge")
sdk_generate_library(hci_bridge)
sdk_add_include_directories(include)
sdk_library_add_public_include_directories(include)
sdk_add_private_include_directories(include)
sdk_library_add_sources(src/hci_bridge.c)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
if(CONFIG_FREERTOS)
    sdk_library_depends_on(sdk::freertos)
endif()
sdk_library_depends_on(sdk::hosal log utility)
sdk_library_strict_includes()
