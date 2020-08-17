#pragma once
#include <string>
#include <stdexcept>
#include <istream>
#include "parseErrors.h"

namespace echeck {
namespace parser {

class csvTokenizer {
public:
  csvTokenizer(std::istream *input);
  ~csvTokenizer();

  std::string getField();
protected:
  std::istream *input;
  std::string getEscapedField();
  std::string getUnescapedField();
  void unexpectedEOF();
};

};
};