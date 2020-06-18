find_package (Python3 COMPONENTS Interpreter)

if(${Python3_FOUND})
  execute_process(WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" COMMAND "${Python3_EXECUTABLE}" simpleTable.py "-D" "${CMAKE_CURRENT_BINARY_DIR}")
endif()
