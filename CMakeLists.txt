cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_firmware)
pico_sdk_init()

add_executable(pico_firmware main.cpp)
target_link_libraries(pico_firmware pico_stdlib hardware_i2c)
pico_add_extra_outputs(pico_firmware)
