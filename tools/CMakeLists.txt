# AVR Project
#
cmake_minimum_required(VERSION 3.0)
project(tools LANGUAGES ASM C)

##############################################################################
# Sources

set(tools_SRCS
    src/lcd1602.c
    src/math.c
    src/shiftreg.S
    src/wait.S
)

configure_file("include/config.h.in" "config.h")
include_directories("${PROJECT_BINARY_DIR}")

##############################################################################
# Targets

add_library(tools STATIC ${tools_SRCS})
target_include_directories(tools PUBLIC "include")
