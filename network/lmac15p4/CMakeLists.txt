file(GLOB LMAC15P4_SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*.c)

if(LMAC15P4_SRC_FILES)
    sdk_generate_library(lmac15p4)
    sdk_add_include_directories(Inc)
    sdk_library_add_public_include_directories(Inc)
    sdk_add_private_include_directories(Inc)
    sdk_library_add_sources(lmac15p4.c)

    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    if(CONFIG_FREERTOS)
        sdk_library_depends_on(sdk::freertos)
    endif()
    sdk_library_depends_on(sdk::hosal log)
    sdk_library_strict_includes()
elseif(EXISTS ${CMAKE_CURRENT_LIST_DIR}/liblmac15p4.a)
    sdk_add_static_library(lmac15p4)
    sdk_add_include_directories(Inc)
    # Strict-include dependents (e.g. zboss_port) resolve `lmac15p4` by name and
    # only see include dirs published on the target. Imported targets are
    # directory-scoped by default, so make it GLOBAL and publish Inc.
    set_target_properties(lmac15p4 PROPERTIES IMPORTED_GLOBAL TRUE
        IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/liblmac15p4.a)
    target_include_directories(lmac15p4 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/Inc)
else()
    message(FATAL_ERROR "[lmac15p4] No source and no prebuilt lib found!")
endif()
