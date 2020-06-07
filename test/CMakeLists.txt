cmake_minimum_required(VERSION 3.14)
project(ElectronicCheckbook_tests)

# External tests (outside this directory)
add_test(NAME Runs COMMAND electroniccheckbook)

# include_directories(${lib})
add_executable(ExampleTest ExampleTest.cpp "${libGeneratedDir}/version.h")
target_include_directories(ExampleTest PRIVATE ${libDirs})

# Internal tests
add_test(NAME "ExampleTest" COMMAND ExampleTest)
set_tests_properties(ExampleTest
  PROPERTIES PASS_REGULAR_EXPRESSION "Hello, world!\nVersion \\d*.\\d*"
  )
