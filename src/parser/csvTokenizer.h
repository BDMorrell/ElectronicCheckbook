#pragma once
#include <string>
#include <stdexcept>
#include <istream>
#include <vector>
#include "parseErrors.h"

namespace echeck {
namespace parser {

class csvTokenizer {
public:
  csvTokenizer(std::istream *input);
  ~csvTokenizer();

  std::vector<std::string> getRow();
  std::string getField(); // may throw
  void advanceInput();
protected:
  std::istream *input;
  std::string getEscapedField();
  std::string getUnescapedField();
  [[noreturn]] void unexpectedEOF();
  char handleCRLF();
};

};
};

