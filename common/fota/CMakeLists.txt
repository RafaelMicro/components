sdk_generate_library(fota_define)

sdk_add_include_directories(Include)
sdk_library_add_public_include_directories(Include)
sdk_add_private_include_directories(Include)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
# Header-only (no .c sources beyond the auto-injected lib_version_info.c,
# which needs no extra include per round 8's finding) -- no other SDK
# dependencies.
sdk_library_strict_includes()






