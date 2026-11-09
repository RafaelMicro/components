sdk_generate_library(LzmaDec)
sdk_add_compile_options(-DLOG_LEVEL=${CONFIG_LOG_LEVEL})
sdk_add_include_directories(.)
sdk_library_add_public_include_directories(.)
sdk_add_private_include_directories(.)
sdk_library_add_sources(LzmaDec.c)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
# No SDK dependencies beyond libc.
sdk_library_strict_includes()