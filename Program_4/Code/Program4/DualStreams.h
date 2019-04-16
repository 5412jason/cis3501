/*!
 * Author: Jason Hogan
 * Description: Developed for CIS 3501 program #4. Generates a graph based on datasets inputted and finds the hamiltonian cycle.
 * 
 */

#pragma once
#include <fstream>
#include <iostream>

using namespace std;

/*!
 * Designed to mimic std::cout functionality.
 * Writes data to both the cout stream and the specified file output stream.
 * 
 */
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

	/*!
	 * Overloads the "<<" operator to allow for DualStreams to function as a single stream.
	 * 
	 */
	void clearfile() {
		file_stream.open(filename, ofstream::out | ofstream::trunc);
		file_stream.close();
	};
};

/*!
 * Template funciton that is used to write the data to the cout stream and the file stream
 * Due to multiple instances of the file being open at once, it has to reopen the file on each call to DualStreams.
 * 
 * \param t
 * \return 
 */
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
	file_stream.close();
	return *this;
}
