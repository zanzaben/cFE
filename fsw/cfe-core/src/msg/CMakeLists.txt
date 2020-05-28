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
set(CFE_ALL_MODULE_SRCS ${CFE_ALL_MODULE_SRCS}
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_msg_checksum.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_msg_fc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cfe_msg_time.c
    PARENT_SCOPE
)
