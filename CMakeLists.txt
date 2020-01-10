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

project(logpp LANGUAGES CXX VERSION 0.0.1)

###
# Set language version
###
set(CMAKE_CXX_VERSION 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Enable GNU extensions
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS ON)

###
# This is the part where you get to decide whether you
# want a static or shared library
###
set(BUILD_STATIC True)

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
)

###
# Add translation units
###
file(GLOB_RECURSE FILES ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)

if(${BUILD_STATIC})
    add_library(${PROJECT_NAME} STATIC ${FILES})
else()
    add_library(${PROJECT_NAME} SHARED ${FILES})
endif()

###
# Export header files
###
target_include_directories(${PROJECT_NAME} PUBLIC include)
