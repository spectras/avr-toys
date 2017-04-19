# AVR Project
#
cmake_minimum_required(VERSION 2.8)
project(avr C)

##############################################################################
# Options

set(CLOCK 16000000ul)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -std=c99")

##############################################################################
# Sources

# Look for header files in build directory (for config.h) and include dir
include_directories("${PROJECT_BINARY_DIR}" "include")

set(avr_SRCS
    src/main.c
)

configure_file("include/config.h.in" "config.h")

##############################################################################
# Targets

add_avr_executable(${CMAKE_PROJECT_NAME} ${avr_SRCS})
target_link_libraries(${CMAKE_PROJECT_NAME} ${avr_DEPS})
