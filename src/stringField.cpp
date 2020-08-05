#include "stringField.h"
using namespace std;
using namespace echeck;

stringField::stringField(string &firstValue)
{
  value = firstValue;
}

stringField::~stringField()
{
  ;
}

string stringField::toString() const
{
  return value;
}

