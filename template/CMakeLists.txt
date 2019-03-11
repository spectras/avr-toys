# AVR Project
#
cmake_minimum_required(VERSION 3.0)
project(template LANGUAGES C)

##############################################################################
# Sources


set(project_SRCS
    src/main.c
)

configure_file("include/config.h.in" "config.h")
include_directories("${PROJECT_BINARY_DIR}")

##############################################################################
# Targets

add_avr_executable(${PROJECT_NAME} ${project_SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE "include")
