sdk_generate_library(utility)
sdk_add_include_directories(Inc)
sdk_add_private_include_directories(Inc)
sdk_library_add_public_include_directories(Inc)
sdk_library_add_sources(fsm.c util_list.c util_string.c util_queue.c util_fcs.c)

# Continuing the library-boundary rework (docs/internal/architecture/lib-dependencies.md).
# No SDK dependencies beyond libc. Public include added later than the rest
# of this file (round 2) because cli needs util_list.h transitively through
# sw_timer.h -- worth being public generally, not just for cli's sake.
sdk_library_strict_includes()