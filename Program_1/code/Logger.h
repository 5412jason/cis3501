#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class Logger {
private:
	string fileName;
	fstream* fileStream;
	bool isOpen;
public:
	Logger();

	string getFileName();
	bool getIsOpen();
	fstream* getFileStream();

	bool openFile(const char file[]);
	bool closeFile();
	//bool log(string input);
	bool log(const char input[]);

};
