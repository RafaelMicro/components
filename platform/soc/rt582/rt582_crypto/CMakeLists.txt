sdk_generate_library(rt582_crypto)
sdk_add_include_directories(Inc)
sdk_library_add_public_include_directories(Inc)
sdk_add_private_include_directories(Inc)
if(CONFIG_CRYPTO_SECP256R1_ENABLE)
    sdk_library_add_sources(rt_ecjpake.c)
endif()
sdk_library_add_sources(
    rt_aes.c
    rt_crypto_util.c
    rt_crypto.c
    rt_hmac_drbg.c
    rt_sha256.c
)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
if(CONFIG_FREERTOS)
    sdk_library_depends_on(sdk::freertos)
endif()
sdk_library_depends_on(sdk::soc_driver)
sdk_library_strict_includes()