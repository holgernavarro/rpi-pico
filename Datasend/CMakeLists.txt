cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(datasend_project C CXX ASM)
#---------------------------------------------
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
#---------------------------------------------
pico_sdk_init()
#---------------------------------------------
add_executable(datasend
  datasend.c
)
#---------------------------------------------
pico_enable_stdio_usb(datasend 1)#①
pico_enable_stdio_uart(datasend 1)#②
#---------------------------------------------
pico_add_extra_outputs(datasend)
#---------------------------------------------
target_link_libraries(datasend pico_stdlib hardware_adc)