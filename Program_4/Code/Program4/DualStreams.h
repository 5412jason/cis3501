#pragma once
#include <fstream>
#include <iostream>

using namespace std;

class DualStreams
{
private:
	const char* filename;
	ofstream file_stream;
	bool valid_state;
public:
	DualStreams() {};
	~DualStreams() {};
	DualStreams(const char* file) : valid_state(file_stream) { filename = file; };
	explicit operator bool() const {
		return valid_state;
	}
	template<typename T>
	DualStreams& operator<<(T&& t);
	void clearfile() {
		file_stream.open(filename, ofstream::out | ofstream::trunc);
		file_stream.close();
	};
};

template<typename T>
inline DualStreams & DualStreams::operator<<(T && t)
{
	file_stream = ofstream(filename, ios_base::app);
	if (!valid_state) {
		return *this;
	}
	if (!(cout << t)) {
		valid_state = false;
		return *this;
	}
	if (!(file_stream << t)) {
		valid_state = false;
		cout << "fstream error";
		return *this;
	}
	else {
		file_stream.close();
	}
	return *this;
}
