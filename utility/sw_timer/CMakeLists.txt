sdk_generate_library(sw_timer)
sdk_add_include_directories(include)
sdk_library_add_public_include_directories(include)
sdk_add_private_include_directories(include)
sdk_library_add_sources(
    src/sw_timer.c
)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
sdk_library_depends_on(sdk::freertos log sdk::soc_driver utility)
sdk_library_strict_includes()