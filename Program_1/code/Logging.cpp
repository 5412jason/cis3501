#include "Logging.h"
#include <iostream>
#include <fstream>

using namespace std;

Logging::Logging()
{
	fileName = "";
	fileStream = NULL;
}

Logging::~Logging()
{
}

string Logging::getFileName() {
	return fileName;
}

bool Logging::checkOpen() {
	if (fileStream != NULL && fileStream->is_open()) {
		return true;
	}
	else {
		return false;
	}
}

fstream* Logging::getFileStream() {
	return fileStream;
}

bool Logging::openFile(const char file[]) {
	if (!checkOpen()) {
		fileName = file;
		try {
			fstream* output = new fstream();
			output->open(fileName, fstream::app);
			fileStream = output;
			return true;
		}
		catch(const ifstream::failure& e) {
			cout << "[ERROR] Could not open the output file!" << endl;
			return false;
		}
	}
	else {
		return false;
	}
}

bool Logging::closeFile() {
	if (checkOpen()) {
		fileStream->close();
		return true;
	}
	else {
		return false;
	}
}

bool Logging::log(const char input[]) {
	if (checkOpen()) {
		for (int i = 0; i < size_t(input); i++) {
			*fileStream << input[i];
		}
		*fileStream << endl;
		return true;
	}
	else {
		return false;
	}
}