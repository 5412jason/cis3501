#include <iostream>
#include <fstream>
#include <iterator>
#include "Logging.h"

Logging::Logging(){
  return;
}

string Logging::getFileName(){
  return fileName;
}

bool Logging::getIsOpen(){
  if (fileStream != NULL && fileStream->is_open()){
    return true;
  }
  else{
    return false;
  }
}
fstream* Logging::getFileStream(){
  return fileStream;
}

bool Logging::openFile(string file){
  if (!getIsOpen()){
    if (file != ""){
      fileName = file;
      try{
        fstream* output = new fstream();
        output->open(fileName, std::fstream::app);
        fileStream = output;
        return true;
      }
      catch (const ifstream::failure& e){
        cout << "[ERROR] Could not open the output file!" << endl;
        return false;
      }
    }
  }
  else {
    return false;
  }
}

bool Logging::closeFile(){
  if(getIsOpen()){
    fileStream->close();
    return true;
  }
  else{
    return false;
  }
}

// TODO: Add reference to date and time in the log file
/*bool Logging::log(char input[]){
  if (getIsOpen()){
    for(int i = 0; i < std::size_t(input); i++){
      *fileStream << input[i];
    }
    *fileStream << endl;
    return true;
  }
  else{
    return false;
  }
}*/

bool Logging::log(string input){
  if (getIsOpen()){
    *fileStream << input << endl;
    return true;
  }
  else{
    return false;
  }
}