#pragma once
#include <string>
#include "basicField.h"

namespace echeck {
  class stringField : public basicField {
  public:
    stringField(std::string &);
    ~stringField();

    std::string toString() const override;
  private:
    std::string value;
  };
};

