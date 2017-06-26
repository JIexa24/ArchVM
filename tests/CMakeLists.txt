cmake_minimum_required(VERSION 2.8)

set(SOURCE_LIB src/main_ctest.c src/testsSC_ctest.c src/testsAsm_ctest.c
    src/testsBasic_ctest.c)
set(CTEST_HEAD ../thirdparty/ctest.h)

include_directories(include)

add_executable(../../tests/bin/tests_ctest ${SOURCE_LIB} ${CTEST_HEAD})
target_link_libraries(../../tests/bin/tests_ctest Basic Asm CPU Term SimpleComputer Write ReadInt
                      BigChars ReadKey)

add_test(NAME tests_ctest COMMAND ../../tests/bin/tests_ctest)
