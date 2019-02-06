#include <string>
#include "Logging.h"
#include "tStack.h"

using namespace std;

// main method for testing stuff
int main(int argc, const char* argv[]) {
	Logging* logger = new Logging();

	cout << logger->openFile("sample.txt") << endl;

	tStack<char> test;

	test.push('a');
	test.push('b');
	test.push('c');

	while (test.isEmpty() == false) {
		logger->log("Value: " + test.top());
		test.pop();
	}

	std::cout << logger->closeFile() << std::endl;
	return 1;
}