cmake_minimum_required(VERSION 2.8) 

set(SOURCE_LIB src/change.c src/command.c src/cpu.c src/global.c src/print.c src/read.c src/timer.c)		# Установка переменной со списком исходников
include_directories(include)
add_library(CPU STATIC ${SOURCE_LIB})
