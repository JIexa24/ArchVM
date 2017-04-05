cmake_minimum_required(VERSION 2.8) 

add_subdirectory(print)
add_subdirectory(scan)
add_subdirectory(simpleComputer)
add_subdirectory(consoleSC)
add_subdirectory(readKey)
add_subdirectory(bc)
add_subdirectory(cpu)
add_subdirectory(asm)

include_directories(main/include)
add_executable(../bin/simplecomputer main/src/main.c)

target_link_libraries(../bin/simplecomputer CPU Term SimpleComputer Asm 
WriteInt ReadInt BigChars ReadKey)

include_directories(asm/include)
add_executable(../bin/sat asm/src/asm.c asm/src/main.c)
target_link_libraries(../bin/sat CPU Term SimpleComputer WriteInt ReadInt BigChars ReadKey)


