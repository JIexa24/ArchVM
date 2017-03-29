cmake_minimum_required(VERSION 2.8) 

set(SOURCE_LIB src/bc.c)		# Установка переменной со списком исходников
include_directories(include)
add_library(BigChars STATIC ${SOURCE_LIB})
