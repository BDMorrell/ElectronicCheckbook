cmake_minimum_required(VERSION 3.14)
project(ElectronicCheckbook_tests)

# Build googletest dependency
mark_as_advanced(
  BUILD_GMOCK BUILD_GTEST INSTALL_GTEST
  gmock_build_tests gtest_build_samples gtest_build_tests
  gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)
set(BUILD_GMOCK OFF CACHE BOOL "Builds the googlemock subproject")
set(INSTALL_GTEST OFF CACHE BOOL "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)")
add_subdirectory("${externalDir}/googletest" "googletest")

include(GoogleTest)

set(SOURCES_TEST
  test.cpp
  csvTokenizerTest.cpp
)

set(HEADERS_TEST
  "${libGeneratedDir}/version.h"
)

add_executable(tests ${SOURCES_TEST} ${HEADERS_TEST})
target_include_directories(tests PRIVATE ${libDirs} ${sourceDir})
target_link_libraries(tests gtest_main echeck_parser)

gtest_discover_tests(tests)

