cmake_minimum_required(VERSION 2.8)

set(SOURCE_LIB src/readInt.c)	
include_directories(include)
add_library(ReadInt STATIC ${SOURCE_LIB})
