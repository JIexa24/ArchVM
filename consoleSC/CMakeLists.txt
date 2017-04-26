cmake_minimum_required(VERSION 2.8) 

set(SOURCE_LIB src/term.c include/term.h)		# Установка переменной со списком исходников
include_directories(include)
add_library(Term STATIC ${SOURCE_LIB})
