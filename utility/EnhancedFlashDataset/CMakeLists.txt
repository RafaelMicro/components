message("  + EnhancedFlashDataset")

sdk_generate_library(EnhancedFlashDataset)

sdk_add_include_directories(
    Inc
)
sdk_library_add_public_include_directories(Inc)
sdk_add_private_include_directories(Inc)

sdk_library_add_sources(
    Src/efd_iap.c
    Src/efd_kv.c
    Src/efd_log.c
    Src/efd_port.c
    Src/efd_utils.c
    Src/EnhancedFlashDataset.c
)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
# efd_def.h -> log.h -> <FreeRTOS.h>; reachable now that log declares its own
# sdk::freertos dependency (components/utility/log/CMakeLists.txt), which
# propagates here via `log`'s PUBLIC link.
sdk_library_depends_on(sdk::soc_driver log)
sdk_library_strict_includes()