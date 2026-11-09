sdk_generate_library(rt569-rf)
sdk_add_include_directories(include)
sdk_library_add_public_include_directories(include)
sdk_add_private_include_directories(include)
sdk_library_add_sources(
    Src/rf_common_init.c
    Src/rf_mcu.c
    Src/rf_mcu_ahb.c
    Src/rf_mcu_spi.c
    Src/rf_tx_comp.c
)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
# rt569mp_init.h etc (owned by rt569_fw) are behind #if RF_MCU_CHIP_MODEL/
# RF_MCU_CHIP_VER/RF_MCU_FW_TARGET branches; only the 569MP branch resolves to
# a header that exists in this repo (rt569mp_init.h) -- the 569M0 variants
# (rt569mxa_init.h etc) don't exist anywhere, so those branches are dead in
# every current build. ft_sector.h (#if RF_CAL_TYPE & RF_CAL_FT_MODE) is the
# same: dead, not declared.
if(CONFIG_FREERTOS)
    sdk_library_depends_on(sdk::freertos)
endif()
if(CONFIG_BOARD STREQUAL "EVB")
    sdk_library_depends_on(rt582_system)
endif()
sdk_library_depends_on(sdk::soc_driver ruci rt569_fw)
sdk_library_strict_includes()