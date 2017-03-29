cmake_minimum_required(VERSION 2.8) 

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm")

add_subdirectory(print)
add_subdirectory(scan)
add_subdirectory(simpleComputer)
add_subdirectory(consoleSC)
add_subdirectory(readKey)
add_subdirectory(bc)
add_subdirectory(cpu)
add_subdirectory(asm)

include_directories(main/include)
add_executable(../bin/simpleсomputer main/src/main.c)

target_link_libraries(../bin/simpleсomputer CPU Term SimpleComputer Asm WriteInt ReadInt BigChars ReadKey)

include_directories(asm/include)
add_executable(../bin/sat asm/src/asm.c asm/src/main.c)
target_link_libraries(../bin/sat CPU Term SimpleComputer WriteInt ReadInt BigChars ReadKey)


