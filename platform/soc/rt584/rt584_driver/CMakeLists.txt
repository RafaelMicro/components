sdk_generate_library(rt584_driver)
sdk_add_include_directories(
    Inc
)
sdk_library_add_public_include_directories(Inc)
sdk_add_private_include_directories(Inc)
# mcu.h re-exports CMSIS Core (core_cm33.h) as part of its own public API.
sdk_library_add_public_include_directories(${CMAKE_SOURCE_DIR}/components/platform/common/CMSIS/Core/Include)
sdk_add_private_include_directories(${CMAKE_SOURCE_DIR}/components/platform/common/CMSIS/Core/Include)
# mcu.h also #includes system_mcu.h, owned by the sibling rt584_system
# library -- added for CONFIG_BOARD=EVB and CONFIG_BOARD=BOOTLOADER
# (soc/CMakeLists.txt: both branches add rt584_system when CONFIG_DRIVER=y).
# The DONGLE branch adds rt584_dongle instead, which does not provide
# system_mcu.h, so that one is left unresolved rather than guessed at.
if((CONFIG_BOARD STREQUAL "EVB") OR (CONFIG_BOARD STREQUAL "BOOTLOADER"))
    sdk_library_depends_on(rt584_system)
endif()

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
# sysfun.c's enter/leave_critical_section() call FreeRTOS scheduler-state APIs
# under #if defined(CONFIG_FREERTOS) -- a real (documented, layer-6 -> layer-4)
# violation, not new; see docs/internal/adr/0002-six-layer-dependency-order.md.
# NOT declared: qspi.c's #include "EPD_1in54.h" under #if EPD_EXAMPLES==1 --
# that macro is never defined anywhere in this repo, so the branch is dead in
# every current build; the header lives only in examples/peripheral/qspi/qspi_epaper/
# and declaring a dependency on it would be backwards (layer 6 -> layer 1).
if(CONFIG_FREERTOS)
    sdk_library_depends_on(sdk::freertos)
endif()
# comm_subsystem_drv.c needs rf_mcu_types.h, owned by the network-layer
# rt569_rf library -- a real, if backwards (layer 6 -> layer 2), dependency.
# Only compiled/needed when CONFIG_BOOTLOADER is unset; CONFIG_BOOTLOADER
# also means CONFIG_CHIP is a *_NONE_OS variant, for which
# components/network/rt569-rf/CMakeLists.txt never adds the subdirectory at
# all -- declaring this unconditionally on CONFIG_BUILD_COMPONENT_RT569_RF
# alone breaks the bootloader-app link (target rt569_rf doesn't exist, so
# CMake falls back to a bare -lrt569_rf).
if(CONFIG_BUILD_COMPONENT_RT569_RF AND NOT CONFIG_BOOTLOADER)
    sdk_library_depends_on(rt569_rf)
endif()
sdk_library_strict_includes()
if(CONFIG_BOOTLOADER)
sdk_library_add_sources(
    Src/bod_comp.c
    Src/dma.c
    Src/gpio.c
    Src/flashctl.c
    Src/sysctrl.c
    Src/dwt.c
    Src/sadc.c
    Src/timer.c
    Src/wdt.c
    Src/sysfun.c 
)
else()
sdk_library_add_sources(
    Src/bod_comp.c
    Src/comm_subsystem_drv.c
    Src/flashctl.c
    Src/gpio.c
    Src/sysctrl.c
    Src/dwt.c
    Src/sysfun.c
    Src/wdt.c
    Src/sadc.c
    Src/otp.c
    Src/lpm.c
    Src/trng.c
)

    if(CONFIG_PERIPHERAL_AUX_COMP)
        message("--       + Peipheral aux_comp ON")
        sdk_library_add_sources(Src/aux_comp.c)
    else()
        message("--       + Peipheral aux_comp OFF")
    endif()

    if(CONFIG_PERIPHERAL_BOD_COMP)
        message("--       + Peipheral bod_comp ON")
        sdk_library_add_sources(Src/bod_comp.c)
    else()
        message("--       + Peipheral bod_comp OFF")
    endif()

    if(CONFIG_PERIPHERAL_DMA)
        message("--       + Peipheral dma ON")
        sdk_library_add_sources(Src/dma.c)
    else()
        message("--       + Peipheral dma OFF")
    endif()

    if(CONFIG_PERIPHERAL_I2C)
        message("--       + Peipheral i2c ON")
        sdk_library_add_sources(
            Src/i2c_master.c
            Src/i2c_slave.c
            )
    else()
        message("--       + Peipheral i2c OFF")
    endif()

    if(CONFIG_PERIPHERAL_I2S)
        message("--       + Peipheral i2s ON")
        sdk_library_add_sources(Src/i2s.c)
    else()
        message("--       + Peipheral i2s OFF")
    endif()

    if(CONFIG_PERIPHERAL_IRM)
        message("--       + Peipheral irm ON")
        sdk_library_add_sources(Src/irm.c)
    else()
        message("--       + Peipheral irm OFF")
    endif()

    if(CONFIG_PERIPHERAL_TIMER)
        message("--       + Peipheral timer ON")
        sdk_library_add_sources(Src/timer.c)
    else()
        message("--       + Peipheral timer OFF")
    endif()

    if(CONFIG_PERIPHERAL_PWM)
        message("--       + Peipheral pwm ON")  
        sdk_library_add_sources(Src/pwm.c)
    else()
        message("--       + Peipheral pwm OFF")
    endif()

    if(CONFIG_PERIPHERAL_RTC)
        message("--       + Peipheral rtc ON")
        sdk_library_add_sources(Src/rtc.c)
    else()
        message("--       + Peipheral rtc OFF")
    endif()

    if(CONFIG_PERIPHERAL_SADC)
        message("--       + Peipheral sadc ON")
        sdk_library_add_sources(Src/sadc.c)
    else()
        message("--       + Peipheral sadc OFF")
    endif()

    if(CONFIG_PERIPHERAL_SWI)
        message("--       + Peipheral swi ON")
        sdk_library_add_sources( Src/swi.c)
    else()
        message("--       + Peipheral swi OFF")
    endif()

endif()
