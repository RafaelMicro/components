sdk_generate_library(subg_ctrl)
sdk_add_include_directories(Inc)
sdk_library_add_public_include_directories(Inc)
sdk_add_private_include_directories(Inc)
sdk_library_add_sources(subg_ctrl.c)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
sdk_library_depends_on(sdk::hosal)
sdk_library_strict_includes()