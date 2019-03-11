avr-toys
========

Those are some experiments done on an Arduino R3.

Most interesting part is probably the build system, as I use a standard CMake build chain,
not the official tools.

Prerequisites
-------------

    sudo apt-get install cmake gcc-avr binutils-avr avr-libc avrdude

Compiling
---------

    cd build
    cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake -DCMAKE_BUILD_TYPE=MinSizeRel ..
    make

Uploading
---------

    make upload PORT=/dev/tty/ACM0
