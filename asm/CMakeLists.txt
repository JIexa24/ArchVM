cmake_minimum_required(VERSION 2.8)

set(SOURCE_LIB src/asm.c)		# Установка переменной со списком исходников
include_directories(include)
add_library(Asm STATIC ${SOURCE_LIB})
