sdk_generate_component_tag(libc)

file(GLOB LIBC_SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/src/*.c)

if(LIBC_SRC_FILES)
    sdk_generate_library(libc)
    sdk_add_include_directories(.)
    sdk_library_add_public_include_directories(.)
    sdk_add_private_include_directories(.)
    sdk_library_add_sources(
        src/assert.c
        src/syscalls.c
    )

    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    # assert.c/syscalls.c #include <FreeRTOS.h> unconditionally (not guarded by
    # CONFIG_FREERTOS in source) -- if this library is ever built without
    # CONFIG_FREERTOS, that's a pre-existing break, not one introduced here.
    if(CONFIG_FREERTOS)
        # FreeRTOSConfig.h (reached via sdk::freertos) itself #includes "mcu.h" --
        # same chain documented on log's CMakeLists.
        sdk_library_depends_on(sdk::freertos sdk::soc_driver)
    endif()
    sdk_library_strict_includes()
elseif(EXISTS ${CMAKE_CURRENT_LIST_DIR}/liblibc.a)
    sdk_add_static_library(libc)
else()
    message(FATAL_ERROR "[libc] No source and no prebuilt lib found!")
endif()
