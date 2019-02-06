#include <iostream>
#include <fstream>

using namespace std;
class Logging
{
private:
	string fileName;
	fstream* fileStream;

public:
	Logging();
	~Logging();

	string getFileName();
	bool checkOpen();
	fstream* getFileStream();

	bool openFile(const char file[]);
	bool closeFile();
	bool log(const char input[]);
};

