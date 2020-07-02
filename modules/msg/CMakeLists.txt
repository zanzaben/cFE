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
    src/cfe_msg_ccsdspri.c
    src/cfe_msg_init.c
    src/cfe_msg_msgid_shared.c
    src/cfe_msg_msgid_v1.c
    src/cfe_msg_sechdr_checksum.c
    src/cfe_msg_sechdr_fc.c
    src/cfe_msg_sechdr_time.c
)

# Source selection for if CCSDS extended header is included
if (MISSION_INCLUDE_CCSDSEXT_HEADER)
    list(APPEND MODULE_SRCS
        src/cfe_msg_ccsdsext.c
        src/cfe_msg_initdefaulthdr_v2.c)
else (MISSION_INCLUDE_CCSDSEXT_HEADER)
    list(APPEND MODULE_SRCS
        src/cfe_msg_initdefaulthdr_v1.c)
endif (MISSION_INCLUDE_CCSDSEXT_HEADER)

# Module library
add_library(${DEP} STATIC ${MODULE_SRCS})

# Add private include
target_include_directories(${DEP} PRIVATE private_inc)
