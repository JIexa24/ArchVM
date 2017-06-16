cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
project(ArchVM)

add_subdirectory(print)
add_subdirectory(scan)
add_subdirectory(simpleComputer)
add_subdirectory(consoleSC)
add_subdirectory(readKey)
add_subdirectory(bc)
add_subdirectory(cpu)
add_subdirectory(asm)
add_subdirectory(basic)
add_subdirectory(hardDrive)

include_directories(main/include)
add_executable(../bin/simplecomputer main/src/main.c)
target_link_libraries(../bin/simplecomputer CPU Term SimpleComputer Asm Basic
Write ReadInt BigChars ReadKey)

include_directories(asm/include)
add_executable(../bin/sat asm/src/main.c)
target_link_libraries(../bin/sat Asm CPU Term SimpleComputer Write ReadInt
                      BigChars ReadKey)

include_directories(basic/include)
add_executable(../bin/sbt basic/src/main.c)
target_link_libraries(../bin/sbt Asm CPU Term SimpleComputer Write ReadInt
                      BigChars ReadKey Basic)

include_directories(hardDrive/include)
add_executable(../bin/hard hardDrive/src/main.c)
target_link_libraries(../bin/hard HardDrive Write ReadInt)

enable_testing()
add_subdirectory(tests)
