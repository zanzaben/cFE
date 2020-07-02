###########################################################
#
# MSG mission build setup
#
# This file is evaluated as part of the "prepare" stage
# and can be used to set up prerequisites for the build, 
# such as generating header files
# 
###########################################################

# Generate the header definition files, use local default for this module)
generate_config_includefile(
    FILE_NAME           "cfe_msg_hdr.h" 
    FALLBACK_FILE       "${CMAKE_CURRENT_LIST_DIR}/mission_inc/default_cfe_msg_hdr.h"
)

generate_config_includefile(
    FILE_NAME           "cfe_msg_sechdr.h"
    FALLBACK_FILE       "${CMAKE_CURRENT_LIST_DIR}/mission_inc/default_cfe_msg_sechdr.h"
)
