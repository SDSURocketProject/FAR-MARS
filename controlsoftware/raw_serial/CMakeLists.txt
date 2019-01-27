cmake_minimum_required (VERSION 2.6)
project (raw_serial)
add_executable(send raw_serial_sender.c)
add_executable(read raw_serial_monitor.c)
