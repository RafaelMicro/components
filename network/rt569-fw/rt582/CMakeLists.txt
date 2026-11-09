sdk_generate_library(rt569_fw)
sdk_add_include_directories(include)
sdk_library_add_public_include_directories(include)
sdk_add_private_include_directories(include)
sdk_library_add_sources(
    Src/rt569mp_fw.c
    Src/rt569mp_init.c
)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
sdk_library_depends_on(sdk::soc_driver rt569-rf)
sdk_library_strict_includes()
