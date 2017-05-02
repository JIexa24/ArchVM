cmake_minimum_required(VERSION 2.8) 

set(SOURCE_LIB src/write.c)		# Установка переменной со списком исходников
include_directories(include)
add_library(Write STATIC ${SOURCE_LIB})	
