#include <iostream>
#include "version.h"

using namespace std;

int main(int argc, char **argv)
{
  cout << "Hello, world!" << endl;
  cout << "Version " << ElectronicCheckbook_VERSION_MAJOR << "." << ElectronicCheckbook_VERSION_MINOR << endl;
  return 0;
}
