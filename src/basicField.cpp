#include "basicField.h"
#include "stringField.h"
using namespace std;
using namespace echeck;

basicField *basicField::fromString(string stringValue)
{
  return new stringField(stringValue);
}

