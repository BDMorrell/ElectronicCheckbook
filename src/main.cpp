#include <iostream>
#include <string>
#include <vector>
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
      vector<string> row = ct.getRow();
      int i;
      for (i = 0; i < row.size(); i++) {
        cout << count << "," << i << ": " << row[i] << endl;
      }
    } catch (parser_error e) {
      cerr << "ERROR: " << e.what() << endl;
    }
  }
  return 0;
}

