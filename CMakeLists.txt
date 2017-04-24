# AVR Project
#
cmake_minimum_required(VERSION 2.8)
project(avr C)

##############################################################################
# Options

if(NOT CLOCK)
    set(CLOCK 16000000)
endif()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -std=c99")

add_subdirectory(tools)

add_subdirectory(assembly)
add_subdirectory(template)
add_subdirectory(timer)
