cmake_minimum_required(VERSION 2.8)

set(SOURCE_LIB src/global.c src/sc_memory.c src/sc_command.c src/sc_register.c)
include_directories(include)
add_library(SimpleComputer STATIC ${SOURCE_LIB})
