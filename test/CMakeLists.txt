#############################################
# CMakeLists file for log++                 #
#                                           #
# This file contains the CMake parameters   #
# required for building log++.              #
#############################################

#############################################
#             CROSS COMPILATION             #
#===========================================#
# If you required cross-compilation for     #
# log++, you may or may not find            #
# corresponding toolchain files in the      #
# toolchains directory of this library/     #
# repository.                               #
#############################################

###
# BASIC CMAKE STUFF
###
cmake_minimum_required(VERSION 3.10)

project(logpp_test LANGUAGES CXX VERSION 0.0.1)

###
# Set language version
###
set(CMAKE_CXX_VERSION 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Enable GNU extensions
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS ON)

###
# Set compiler flags
# We want the compiler to be as grumpy and as naggy as your mother IL
# Except when it comes to formatting, the built-in format function causes a warning
# which can safely be ignored.
###
add_compile_options(
    -Wpedantic # Be pedantic about little things
    -Wall # All warnings as errors
    -Wno-format-security # This'll stay our little secret
)

###
# Set include directories
###
include_directories(
    include/ # This is the main include directory
    ../include/
    ../
)

###
# Get logpp
###
if (NOT TARGET logpp)
    message("Adding logpp CMakeLists...")
    # is this a standalone build?
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR}/liblogpp)
endif()

###
# Add translation units
###
file(GLOB_RECURSE FILES ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)

add_executable(${PROJECT_NAME} ${FILES})

target_link_libraries(${PROJECT_NAME} logpp)
