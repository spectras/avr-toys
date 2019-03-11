# AVR Project
#
cmake_minimum_required(VERSION 3.0)
project(assembly LANGUAGES ASM)

##############################################################################
# Sources

set(project_SRCS
    src/main.S
)

configure_file("include/config.h.in" "config.h")
include_directories("${PROJECT_BINARY_DIR}")

##############################################################################
# Targets

add_avr_executable(${PROJECT_NAME} ${project_SRCS})
target_link_libraries(${PROJECT_NAME} ${project_DEPS})
