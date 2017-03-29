cmake_minimum_required(VERSION 2.8) 

set(SOURCE_LIB src/writeInt.c)		# Установка переменной со списком исходников
include_directories(include)
add_library(WriteInt STATIC ${SOURCE_LIB})	
