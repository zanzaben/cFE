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
set(${DEP}_SRC
    src/cfe_msg_ccsdspri.c
    src/cfe_msg_init.c
    src/cfe_msg_msgid_shared.c
    src/cfe_msg_sechdr_checksum.c
    src/cfe_msg_sechdr_fc.c
    src/cfe_msg_sechdr_time.c
)

# Source selection for if CCSDS extended header is included, and MsgId version use
if (MISSION_INCLUDE_CCSDSEXT_HEADER)
    message(STATUS "CCSDS primary and extended header included in message header")
    list(APPEND ${DEP}_SRC
        src/cfe_msg_ccsdsext.c
        src/cfe_msg_initdefaulthdr_priext.c)
    if (MISSION_MSGID_V2)  # MsgId v2 or v1 can be used with extended headers
      message(STATUS "Message Id version 2 in use (MsgId V2)")
      list(APPEND ${DEP}_SRC
           src/cfe_msg_msgid_v2.c)
    else (MISSION_MSGID_V2)
      message(STATUS "Message Id version 1 in use (MsgId V1)")
      list(APPEND ${DEP}_SRC
           src/cfe_msg_msgid_v1.c)
    endif (MISSION_MSGID_V2)
else (MISSION_INCLUDE_CCSDSEXT_HEADER)
    message(STATUS "CCSDS primary header included in message header (not including CCSDS extended header)")
    message(STATUS "Message Id version 1 in use (MsgId V1)")
    list(APPEND ${DEP}_SRC
        src/cfe_msg_initdefaulthdr_pri.c
        src/cfe_msg_msgid_v1.c)
    if (MISSION_MSGID_V2)
        message(FATAL_ERROR "Message Id (MsgId) version 2 can only be used if MISSION_INCLUDE_CCSDSEXT_HEADER is set")
    endif (MISSION_MSGID_V2)
endif (MISSION_INCLUDE_CCSDSEXT_HEADER)

# Source selection for v1 and v2 message header definition

# Module library
add_library(${DEP} STATIC ${${DEP}_SRC})

# Add private include
target_include_directories(${DEP} PRIVATE private_inc)
