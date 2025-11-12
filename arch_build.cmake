###########################################################
#
# CS App platform build setup
#
# This file is evaluated as part of the "prepare" stage
# and can be used to set up prerequisites for the build,
# such as generating header files
#
###########################################################

# The list of header files that control the app configuration
set(CS_PLATFORM_CONFIG_FILE_LIST
  cs_msgids.h
)

generate_configfile_set(${CS_PLATFORM_CONFIG_FILE_LIST})