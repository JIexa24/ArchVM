cmake_minimum_required(VERSION 2.8)

set(SOURCE_LIB src/basic.c)		# Установка переменной со списком исходников
include_directories(include)
add_library(Basic STATIC ${SOURCE_LIB})
