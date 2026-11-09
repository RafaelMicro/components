sdk_generate_library(version_info)
sdk_add_compile_options(-DLOG_LEVEL=${CONFIG_LOG_LEVEL})
sdk_add_include_directories(.)
sdk_library_add_public_include_directories(.)
sdk_add_private_include_directories(.)
sdk_library_add_sources(version_info.c)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
sdk_library_depends_on(fota_define)
sdk_library_strict_includes()