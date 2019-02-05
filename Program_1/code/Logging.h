#include <iostream>
#include <fstream>

using namespace std;

#ifndef LOGGING_H
#define  LOGGING_H

class Logging {
private:
  string fileName;
  fstream* fileStream;
  bool isOpen;
public:
  Logging();

  string getFileName();
  bool getIsOpen();
  fstream* getFileStream();

  bool openFile(string file);
  bool closeFile();
  bool log(string input);
  //bool log(char input[]);

};
#endif
