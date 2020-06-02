##################################################################
#
# cFE message module CMake build recipe
#
# This CMakeLists.txt adds source files for
# message module included in the cFE distribution.  Selected
# files are built into a static library that in turn
# is linked into the final executable.
#
# Note this is different than applications which are dynamically
# linked to support runtime loading.  The core applications all
# use static linkage.
#
##################################################################

# Add the basic set of files which are always built
set(MODULE_SRCS
    src/cfe_msg_checksum.c
    src/cfe_msg_fc.c
    src/cfe_msg_time.c
)

add_library(${MODULE_NAME} STATIC ${MODULE_SRCS})

# Add to includes for header dependency resolution across modules
target_include_directories(${MODULE_NAME} PUBLIC inc)
