sdk_generate_library(dump_boot_info)
sdk_add_include_directories(Inc)
sdk_library_add_public_include_directories(Inc)
sdk_add_private_include_directories(Inc)
sdk_library_add_sources(
    Src/dump_boot_info.c
)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
sdk_library_depends_on(sdk::soc_driver uart_stdio)
sdk_library_strict_includes()