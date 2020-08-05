#pragma once
#include <string>

namespace echeck {
  class basicField {
  public:
    basicField *fromString(std::string stringValue);
    virtual ~basicField() {;}

    virtual std::string toString() const = 0;
  };
};

