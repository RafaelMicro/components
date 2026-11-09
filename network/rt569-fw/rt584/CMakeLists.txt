sdk_generate_library(rt569_fw)
sdk_add_include_directories(include)
sdk_library_add_public_include_directories(include)
sdk_add_private_include_directories(include)
sdk_library_add_sources(
    Src/rt569s_fw.c
    Src/rt569s_init.c
)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
sdk_library_depends_on(sdk::soc_driver rt569_rf)
sdk_library_strict_includes()
