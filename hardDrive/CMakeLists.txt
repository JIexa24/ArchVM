cmake_minimum_required(VERSION 2.8) 

set(SOURCE_LIB src/hardDrive.c src/functions.c)		# Установка переменной со списком исходников
include_directories(include)
add_library(HardDrive STATIC ${SOURCE_LIB})
