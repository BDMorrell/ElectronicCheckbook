cmake_minimum_required(VERSION 3.14)
project(ElectronicCheckbook VERSION 0.1)

# Requirements
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Configuration
if ((CMAKE_BUILD_TYPE Debug) OR (NOT CMAKE_BUILD_TYPE)) # if debug or not specified
  option(BUILD_TESTING "Should there be tests?" ON)
endif()

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) AND BUILD_TESTING)
  set(ElectronicCheckbook_BUILD_TESTING ON)
endif()

# Code locations
set(libBaseDir "${PROJECT_SOURCE_DIR}/lib" )
set(libGeneratedDir "${PROJECT_BINARY_DIR}/lib")
set(libDirs ${libBaseDir} ${libGeneratedDir})

# Code generation
configure_file("${libBaseDir}/version.h.in" "${libGeneratedDir}/version.h")

# Source compiling
add_subdirectory(src)

# Testing
if(ElectronicCheckbook_BUILD_TESTING)
  include(CTest)
  add_subdirectory(test)
endif()
