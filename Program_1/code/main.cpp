#include <iostream>
#include <iterator>
#include <string>
#include "Logging.h"
#include "Stack.h"
#include <stdio.h>

// main method for testing stuff
int main( int argc, const char* argv[]){
  Logging* logger = new Logging();

  cout << logger->openFile("sample.txt") << endl;

  Stack<char> test;

  test.push('a');
  test.push('b');
  test.push('c');

  while (test.isEmpty() == false){
    logger->log("Value: " + test.top());
    test.pop();
  }

  std::cout << logger->closeFile() << std::endl;
  return 1;
}
