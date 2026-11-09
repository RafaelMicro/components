sdk_generate_library(rt582_hosal)
sdk_add_include_directories(Inc)
sdk_library_add_public_include_directories(Inc)
if(CONFIG_BOOTLOADER)
sdk_library_add_sources(
    Src/hosal_uart.c
    Src/hosal_wdt.c
) 
else()
if(CONFIG_CRYPTO_SECP256R1_ENABLE)
    sdk_library_add_sources(Src/hosal_crypto_ecjpake.c)
endif()

if(CONFIG_CRYPTO_AES_ENABLE)
sdk_library_add_sources(
    Src/hosal_crypto_aes.c
    Src/hosal_crypto_aes_ccm.c
    Src/hosal_crypto_ecc.c
    Src/hosal_crypto_ctr_drbg.c
    Src/hosal_crypto_hmac_drbg.c
    Src/hosal_crypto_sha256.c
    )
endif()

if(NOT CONFIG_BASIC_EXAMPLE)
    sdk_library_add_sources(
        Src/hosal_rf.c
    )
endif()

sdk_library_add_sources(
    Src/hosal_comparator.c
    Src/hosal_dma.c
    Src/hosal_flash.c 
    Src/hosal_gpio.c
    Src/hosal_i2c_master.c
    Src/hosal_i2s.c
    Src/hosal_pwm.c
    Src/hosal_qspi.c 
    Src/hosal_rtc.c 
    Src/hosal_sadc.c 
    Src/hosal_slow_timer.c
    Src/hosal_swi.c
    Src/hosal_sysctrl.c
    Src/hosal_timer.c
    Src/hosal_uart.c
    Src/hosal_wdt.c
    Src/hosal_lpm.c
    Src/hosal_trng.c
)

if(CONFIG_CRYPTO_AES_ENABLE)
    # hosal_crypto_*.c need rt582_crypto's rt_crypto.h/rt_ecc.h.
    sdk_library_depends_on(rt582_crypto)
endif()
if(NOT CONFIG_BASIC_EXAMPLE)
    # hosal_rf.c reaches across to log (utility), rt582_system (mp_sector.h,
    # EVB only), and the network-layer rt569-rf/ruci -- real, if backwards
    # (layer 5 -> layer 2/3), dependencies.
    if(CONFIG_FREERTOS)
        sdk_library_depends_on(sdk::freertos)
    endif()
    sdk_library_depends_on(log)
    if(CONFIG_BOARD STREQUAL "EVB")
        sdk_library_depends_on(rt582_system)
    endif()
    if(CONFIG_BUILD_COMPONENT_RT569_RF)
        sdk_library_depends_on(rt569-rf)
    endif()
    sdk_library_depends_on(ruci)
endif()
endif()

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
# Applies to both the CONFIG_BOOTLOADER and normal branches above -- the
# shared source files (hosal_uart.c, hosal_wdt.c, ...) need sdk::soc_driver
# either way.
sdk_add_private_include_directories(Inc)
sdk_library_depends_on(sdk::soc_driver)
sdk_library_strict_includes()
