cmake_minimum_required (VERSION 2.6)
project (raw_serial)
set(CMAKE_C_FLAGS "-g")
add_executable(read pressuretest.c)
