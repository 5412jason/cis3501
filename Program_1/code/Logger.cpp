#include <iostream>
#include <fstream>
#include <cstddef>
#include <iterator>
#include <string>
#include "Logger.h"

using namespace std;

Logger::Logger() {
	fileName = "";
	fileStream = NULL;
}

string Logger::getFileName() {
	return fileName;
}

bool Logger::getIsOpen() {
	if (fileStream != NULL && fileStream->is_open()) {
		return true;
	}
	else {
		return false;
	}
}
fstream* Logger::getFileStream() {
	return fileStream;
}

bool Logger::openFile(const char file[]) {
	if (!getIsOpen()) {
		fileName = file;
		try {
			std::fstream* output = new std::fstream();
			output->open(fileName, std::fstream::app);
			fileStream = output;
			return true;
		}
		catch (const ifstream::failure& e) {
			cout << "[ERROR] Could not open the output file!" << endl;
			return false;
		}
	}
	else {
		return false;
	}
}

bool Logger::closeFile() {
	if (getIsOpen()) {
		fileStream->close();
		return true;
	}
	else {
		return false;
	}
}

// TODO: Add reference to date and time in the log file
bool Logger::log(const char input[]) {
	if (getIsOpen()) {
		for (int i = 0; i < std::size_t(input); i++) {
			*fileStream << input[i];
		}
		*fileStream << endl;
		return true;
	}
	else {
		return false;
	}
}

/*bool Logger::log(std::string input){
  if (getIsOpen()){
	*fileStream << input << endl;
	cout << input << endl;
	return true;
  }
  else{
	return false;
  }
}*/
