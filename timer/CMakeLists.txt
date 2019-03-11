# AVR Project
#
cmake_minimum_required(VERSION 3.0)
project(timer LANGUAGES C)

##############################################################################
# Sources

set(timer_SRCS
    src/main.c
    src/segments.c
    src/timers.c
)

configure_file("include/config.h.in" "config.h")
include_directories("${PROJECT_BINARY_DIR}")

##############################################################################
# Targets

add_avr_executable(${PROJECT_NAME} ${timer_SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_link_libraries(${PROJECT_NAME} tools)
