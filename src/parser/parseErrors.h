#pragma once
#include <string>
#include <stdexcept>

namespace echeck {
namespace parser {
  class parser_error : public std::runtime_error {
  public:
    explicit parser_error(const std::string& what_arg)
      : std::runtime_error(what_arg) {;}
    explicit parser_error(const char *what_arg)
      : std::runtime_error(what_arg) {;}
  };

  class token_error : public parser_error {
  public:
    explicit token_error(const std::string& what_arg)
      : parser_error(what_arg) {;}
    explicit token_error(const char *what_arg)
      : parser_error(what_arg) {;}
  };
};
};
