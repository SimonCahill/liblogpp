######################################
##      CMAKE TOOLCHAIN FILE        ##
##                                  ##
## This toolchain file contains     ##
## cmake configurations for powerpc ##
## (32-bit BE) toolchains from GNU. ##
######################################

###
# Set system architecture
###
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR powerpc)

###
# Set toolchain locations
# Note: This may very well vary depending
# on YOUR SPECIFIC system configuration.
# You may override these values if necessary.
###
set(toolchain_dir /usr/powerpc-linux-gnu)
set(CMAKE_C_COMPILER ${toolchain_dir}/gcc)
set(CMAKE_CXX_COMPILER ${toolchain_dir}/g++)
set(CMAKE_AR ${toolchain_dir}/ar)
set(CMAKE_LD ${toolchain_dir}/ld)

###
# Some more CMake stuff
###
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
