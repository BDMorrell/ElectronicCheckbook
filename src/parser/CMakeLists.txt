set(SOURCES_SUBPARSER
  csvTokenizer.cpp
)

set(HEADERS_SUBPARSER
  csvTokenizer.h
)

add_library(echeck_parser ${SOURCES_SUBPARSER} ${HEADERS_SUBPARSER})

