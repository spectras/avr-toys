# AVR Project
#
cmake_minimum_required(VERSION 2.8)
project(template C)

##############################################################################
# Sources

# Look for header files in build directory (for config.h) and include dir
include_directories("${PROJECT_BINARY_DIR}" "include")

set(project_SRCS
    src/main.c
)

configure_file("include/config.h.in" "config.h")

##############################################################################
# Targets

add_avr_executable(${PROJECT_NAME} ${project_SRCS})
target_link_libraries(${PROJECT_NAME} ${project_DEPS})
