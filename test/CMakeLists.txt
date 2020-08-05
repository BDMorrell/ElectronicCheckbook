cmake_minimum_required(VERSION 3.14)
project(ElectronicCheckbook_tests)

add_subdirectory(testInput)

# External tests (outside this directory)
add_test(NAME Runs COMMAND electroniccheckbook)

# GoogleTest tests:
set(SOURCES_TEST
  test.cpp
)

set(HEADERS_TEST
  "${libGeneratedDir}/version.h"
)

add_executable(ec_tests ${SOURCES_TEST} ${HEADERS_TEST})

target_include_directories(ec_tests PRIVATE ${libDirs})

target_link_libraries(ec_tests gtest_main)

add_test(NAME GeneralTests COMMAND ec_tests)

