# AVR Project
#
cmake_minimum_required(VERSION 2.8)
project(avr C)

##############################################################################
# Options

set(CLOCK 16000000)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -std=c99")

add_subdirectory(tools)

add_subdirectory(assembly)
add_subdirectory(template)
add_subdirectory(timer)
