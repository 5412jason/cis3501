#include <iostream>
#include <iterator>
#include <string>
#include "Logging.h"
#include <stdio.h>

using namespace std;

int main( int argc, const char* argv[]){
  Logging* logger = new Logging();

  cout << logger->openFile("sample.txt") << endl;
  cout << logger->log("This is a test") << endl;
  cout << logger->closeFile() << endl;

  return 1;
}
