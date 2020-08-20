#include <iostream>
#include <string>
#include "version.h"
#include "parser/csvTokenizer.h"
#include "parser/parseErrors.h"

using namespace std;
using namespace echeck::parser;

int main(int arc, char **argv)
{
  csvTokenizer ct(&cin);
  int count = 0;
  while (cin.good()) {
    try {
      string token;
      token = ct.getField();
      cout << count++ << ": " << token << endl;
      int c = cin.peek();
      if (c == '\n') {
        cout << "NL" << endl;
      } else {
        cout << "Peek " << c << ": " << (char) c << endl;
      }
      if (c == '\n' || c == ',') {
        ct.advanceInput();
      }
    } catch (parser_error e) {
      cerr << "ERROR: " << e.what() << endl;
    }
  }
  return 0;
}

