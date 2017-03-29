cmake_minimum_required(VERSION 2.8) 

set(SOURCE_LIB src/asm.c)		# Установка переменной со списком исходников
include_directories(include)
add_library(Asm STATIC ${SOURCE_LIB})
add_executable(sat src/asm.c src/main.c)
target_link_libraries(sat CPU Term SimpleComputer Asm WriteInt ReadInt BigChars ReadKey)
