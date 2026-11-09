sdk_generate_library(rt582_system)

if((${CONFIG_CHIP} STREQUAL "RT582") OR (${CONFIG_CHIP} STREQUAL "RT581"))
sdk_set_linker_script(${CMAKE_CURRENT_LIST_DIR}/ldscripts/rt582.ld)
endif()

if(${CONFIG_CHIP} STREQUAL "RT583")
sdk_set_linker_script(${CMAKE_CURRENT_LIST_DIR}/ldscripts/rt583.ld)
endif()
add_definitions(-D__STARTUP_CLEAR_BSS)
sdk_add_include_directories(Include)
sdk_library_add_public_include_directories(Include)
sdk_add_private_include_directories(Include)

if(CONFIG_BOOTLOADER)
    sdk_library_add_sources(
        Src/system_mcu.c
    )
else()
    sdk_library_add_sources(
        Startup/startup.S
        Src/system_mcu.c
        Src/mp_sector.c
    )
endif()

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
# system_mcu.c/mp_sector.c need mcu.h etc, owned by the sibling rt582_driver --
# genuine mutual dependency, see rt582_driver's own depends_on(rt582_system).
sdk_library_depends_on(rt582_driver)
sdk_library_strict_includes()
