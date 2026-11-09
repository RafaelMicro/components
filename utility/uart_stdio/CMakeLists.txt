sdk_generate_library(uart_stdio)
sdk_add_include_directories(Inc)
sdk_library_add_public_include_directories(Inc)
sdk_add_private_include_directories(Inc)
sdk_library_add_sources(
   uart_stdio.c
   debug.c
   sscanf.c
   vsscanf.c
   strntoumax.c
)

# Pilot for the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
# uart_stdio only needs these two -- everything else in the 500+-path global
# include pool stays invisible to it. (cli was the original pilot choice but
# was reverted: it directly uses FreeRTOS tasks, and FreeRTOS.h transitively
# needs FreeRTOSConfig.h, which is owned per-example, not by any library --
# making cli strict would require touching every example that builds it.)
sdk_library_depends_on(sdk::soc_driver sdk::hosal)
sdk_library_strict_includes()