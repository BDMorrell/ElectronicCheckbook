set(SOURCES_MAIN
  main.cpp
  basicField.cpp
  stringField.cpp
)

set(HEADERS_MAIN
  "${libGeneratedDir}/version.h"
  basicField.h
  stringField.h
  table.h
)

add_executable(electroniccheckbook ${SOURCES_MAIN} ${HEADERS_MAIN})
target_include_directories(electroniccheckbook PRIVATE ${libDirs})

