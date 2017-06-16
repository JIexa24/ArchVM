cmake_minimum_required(VERSION 2.8)

set(SOURCE_LIB src/readkey.c include/readkey.h)	
include_directories(include)
add_library(ReadKey STATIC ${SOURCE_LIB})
