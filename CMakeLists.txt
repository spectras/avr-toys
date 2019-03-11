# AVR Project
#
cmake_minimum_required(VERSION 3.0)
project(avr LANGUAGES C)

##############################################################################
# Options

if(NOT CLOCK)
    set(CLOCK 16000000)
endif()
add_compile_options(-Wall -Wextra -Werror -std=c99)

add_subdirectory(tools)

add_subdirectory(assembly)
add_subdirectory(hello)
add_subdirectory(template)
add_subdirectory(timer)
