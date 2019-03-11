# AVR Project
#
cmake_minimum_required(VERSION 3.0)
project(hello LANGUAGES C)

##############################################################################
# Sources

set(hello_SRCS
    src/main.c
)

configure_file("include/config.h.in" "config.h")
include_directories("${PROJECT_BINARY_DIR}")

##############################################################################
# Targets

add_avr_executable(${PROJECT_NAME} ${hello_SRCS})
target_link_libraries(${PROJECT_NAME} tools)
