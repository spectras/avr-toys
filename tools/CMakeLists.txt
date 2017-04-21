# AVR Project
#
cmake_minimum_required(VERSION 2.8)
project(tools ASM C)

##############################################################################
# Sources

# Look for header files in build directory (for config.h) and include dir
include_directories("${PROJECT_BINARY_DIR}" "include")

set(tools_SRCS
    src/math.c
)

configure_file("include/config.h.in" "config.h")

##############################################################################
# Targets

add_library(tools STATIC ${tools_SRCS})
target_include_directories(tools PUBLIC "include")
