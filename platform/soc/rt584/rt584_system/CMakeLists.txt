sdk_generate_library(rt584_system)

if(CONFIG_RF1301)
sdk_set_linker_script(${CMAKE_CURRENT_LIST_DIR}/ldscripts/rf1301.ld)
endif()

if(CONFIG_RT584H)
sdk_set_linker_script(${CMAKE_CURRENT_LIST_DIR}/ldscripts/rt584H.ld)
endif()

if(CONFIG_RT584HA4)
sdk_set_linker_script(${CMAKE_CURRENT_LIST_DIR}/ldscripts/rt584HA4.ld)
endif()

if(CONFIG_RT584L)
sdk_set_linker_script(${CMAKE_CURRENT_LIST_DIR}/ldscripts/rt584L.ld)
endif()

sdk_add_include_directories(Include)
sdk_library_add_public_include_directories(Include)
sdk_add_private_include_directories(Include)

if(CONFIG_BOOTLOADER)
sdk_library_add_sources(
    Src/system_mcu.c
    Src/mp_sector.c
)
else()
sdk_library_add_sources(
    Startup/startup.c
    Src/system_mcu.c
    Src/mp_sector.c
)
endif()

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
# system_mcu.c/mp_sector.c need mcu.h/flashctl.h/gpio.h/sysctrl.h/sysfun.h,
# owned by the sibling rt584_driver -- a genuine mutual dependency (see
# rt584_driver's own depends_on(rt584_system) for the reverse direction).
# CMake supports cyclic PUBLIC links between static libraries for usage-
# requirement (include) propagation; verified empirically via real build.
sdk_library_depends_on(rt584_driver)
sdk_library_strict_includes()


