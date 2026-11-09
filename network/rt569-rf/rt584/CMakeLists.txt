sdk_generate_library(rt569_rf)
sdk_add_include_directories(include)
sdk_library_add_public_include_directories(include)
sdk_add_private_include_directories(include)
sdk_library_add_sources(
    Src/rf_common_init.c
    Src/rf_mcu.c
    Src/rf_mcu_ahb.c
    Src/rf_mcu_spi.c
    Src/rf_tx_comp.c
    Src/rf_test.c
    Src/rf_aes_ccm.c
)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
# rt569s_init.h (RF_MCU_CHIP_MODEL == RF_MCU_CHIP_569S) is the only chip-model
# branch that resolves to a header that exists in this repo; the 569M0 branch
# is dead in every current build, not declared.
if(CONFIG_FREERTOS)
    sdk_library_depends_on(sdk::freertos)
endif()
if(CONFIG_BOARD STREQUAL "EVB")
    sdk_library_depends_on(rt584_system)
endif()
sdk_library_depends_on(sdk::soc_driver ruci rt569_fw)
sdk_library_strict_includes()