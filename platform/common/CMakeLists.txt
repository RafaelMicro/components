# Shared CMSIS for all Rafael SoCs.
#
#   CMSIS/      -> CMSIS_6 (Core/Driver/RTOS2). Header-only and identical across
#                 rt582/rt584, so it is vendored once here instead of per-driver.
#   CMSIS-DSP/  -> CMSIS-DSP (separate upstream repo, own version/license).
#
# CMSIS-Core headers are always on the include path.
sdk_add_include_directories(CMSIS/Core/Include)

# CMSIS-DSP library (opt-in via CONFIG_CMSIS_DSP).
#
# The DSP sources are core-agnostic: CMSIS-DSP auto-selects the SIMD/FPU path
# from the compiler's __ARM_FEATURE_DSP / __ARM_FP, which the toolchain sets via
# -mcpu (cortex-m3 -> scalar C path, cortex-m33 -> DSP SIMD + FPU). No manual
# ARM_MATH_* defines are required for CMSIS-DSP >= 1.15.
if(CONFIG_CMSIS_DSP)
    sdk_generate_library(cmsis_dsp)

    # Public: apps include "arm_math.h". Private: internal build-only headers.
    sdk_add_include_directories(CMSIS-DSP/Include)
    sdk_library_add_public_include_directories(CMSIS-DSP/Include)
    sdk_add_private_include_directories(CMSIS-DSP/Include)
    sdk_add_private_include_directories(CMSIS-DSP/PrivateInclude)
    # CMSIS Core (published bare/unowned at the top of this file) -- needed by
    # this library's own sources.
    sdk_add_private_include_directories(${CMAKE_CURRENT_LIST_DIR}/CMSIS/Core/Include)

    # One consolidation .c per module (each #includes its per-function sources).
    # F16 (half-precision) modules are intentionally omitted: they need __fp16
    # support flags not enabled in this SDK.
    sdk_library_add_sources(
        CMSIS-DSP/Source/BasicMathFunctions/BasicMathFunctions.c
        CMSIS-DSP/Source/BayesFunctions/BayesFunctions.c
        CMSIS-DSP/Source/CommonTables/CommonTables.c
        CMSIS-DSP/Source/ComplexMathFunctions/ComplexMathFunctions.c
        CMSIS-DSP/Source/ControllerFunctions/ControllerFunctions.c
        CMSIS-DSP/Source/DistanceFunctions/DistanceFunctions.c
        CMSIS-DSP/Source/FastMathFunctions/FastMathFunctions.c
        CMSIS-DSP/Source/FilteringFunctions/FilteringFunctions.c
        CMSIS-DSP/Source/InterpolationFunctions/InterpolationFunctions.c
        CMSIS-DSP/Source/MatrixFunctions/MatrixFunctions.c
        CMSIS-DSP/Source/QuaternionMathFunctions/QuaternionMathFunctions.c
        CMSIS-DSP/Source/StatisticsFunctions/StatisticsFunctions.c
        CMSIS-DSP/Source/SupportFunctions/SupportFunctions.c
        CMSIS-DSP/Source/SVMFunctions/SVMFunctions.c
        CMSIS-DSP/Source/TransformFunctions/TransformFunctions.c
        CMSIS-DSP/Source/WindowFunctions/WindowFunctions.c
    )

    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    # No SDK dependencies beyond libc and CMSIS Core (declared above).
    sdk_library_strict_includes()
endif()

# CMSIS-NN library (opt-in via CONFIG_CMSIS_NN).
#
# Self-contained: CMSIS-NN (>= v4.0) needs only CMSIS-Core, not CMSIS-DSP, so this
# does NOT depend on CONFIG_CMSIS_DSP. The kernel path (scalar C vs DSP SIMD) is
# auto-selected from the compiler's __ARM_FEATURE_DSP, set via -mcpu (cortex-m3 ->
# scalar C, cortex-m33 -> DSP-extension SIMD; no Helium/MVE on standard M33). No
# ARM_NN_* / ARM_MATH_* defines are required.
#
# Reserved as the optimized backend for a future TFLM integration.
if(CONFIG_CMSIS_NN)
    sdk_generate_library(cmsis_nn)

    # Public: apps include "arm_nnfunctions.h" (via CMSIS-NN/Include). TFLM's
    # cmsis_nn kernels include "Include/arm_nnfunctions.h", so the CMSIS-NN root
    # (the dir containing Include/) is also exposed to reuse this same copy as
    # TFLM's optimized backend instead of vendoring a second CMSIS-NN.
    sdk_add_include_directories(CMSIS-NN/Include)
    sdk_add_include_directories(CMSIS-NN)
    sdk_library_add_public_include_directories(CMSIS-NN/Include CMSIS-NN)
    sdk_add_private_include_directories(CMSIS-NN/Include CMSIS-NN)

    # One function per .c (no consolidation files upstream) -> glob the module
    # tree. v7.0.0 ships no float16 kernels, so there is nothing to exclude.
    # CONFIGURE_DEPENDS re-globs on every build so a future version bump that
    # adds/removes source files is picked up without a manual re-configure.
    file(GLOB_RECURSE CMSIS_NN_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_LIST_DIR}/CMSIS-NN/Source/*.c)
    sdk_library_add_sources(${CMSIS_NN_SOURCES})

    # Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
    # No SDK dependencies beyond libc -- self-contained, confirmed no CMSIS
    # Core reference (unlike CMSIS-DSP).
    sdk_library_strict_includes()
endif()
