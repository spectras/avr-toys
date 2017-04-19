# Arduino Uno R3

include(CMakeForceCompiler)

set(AVR_MCU atmega328p)
set(AVR_PART atmega328p)
set(AVR_PROGRAMMER arduino)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

find_program(CMAKE_C_COMPILER avr-gcc)
find_program(CMAKE_CXX_COMPILER avr-g++)
find_program(CMAKE_AVR_UPLOADER avrdude)

add_compile_options(-ffunction-sections -mmcu=${AVR_MCU} -mrelax)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2 -frename-registers -DNDEBUG" CACHE STRING "")

set(CMAKE_PREFIX_PATH /usr/lib/avr)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(AVR_UPLOAD_FLAGS ${AVR_UPLOAD_FLAGS} -qq -c ${AVR_PROGRAMMER} -p ${AVR_PART} -P \${PORT} CACHE STRING "")
if (${AVR_UPLOAD_BAUD})
    list(APPEND AVR_UPLOAD_FLAGS -b ${AVR_BAUD})
endif()

function(add_avr_executable NAME)
    add_executable(${NAME} ${ARGN})
    set_target_properties(${NAME} PROPERTIES LINK_FLAGS "-mmcu=${AVR_MCU} -Wl,--relax,--gc-sections")

    add_custom_command(
        OUTPUT ${NAME}.main
        COMMAND ${CMAKE_OBJCOPY} -j .text -j .data -O ihex ${NAME} ${NAME}.main
        DEPENDS ${NAME}
        COMMENT "Extracting main sections into ${NAME}.main"
    )
    add_custom_command(
        OUTPUT ${NAME}.eeprom
        COMMAND ${CMAKE_OBJCOPY} -O ihex -j .eeprom --change-section-lma .eeprom=0 --no-change-warnings ${NAME} ${NAME}.eeprom
        DEPENDS ${NAME}
        COMMENT "Extracting eeprom section into ${NAME}.eeprom"
    )
    add_custom_target(upload-${NAME}
        COMMAND ${CMAKE_AVR_UPLOADER} ${AVR_UPLOAD_FLAGS} -U flash:w:${NAME}.main:i -U eeprom:w:${NAME}.eeprom:i
        DEPENDS ${NAME}.main ${NAME}.eeprom
        COMMENT "Uploading ${NAME} to ${AVR_PART} microcontroller"
    )
endfunction(add_avr_executable)
