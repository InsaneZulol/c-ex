//* use eof() to simplify the table checking program from *//
//* 23.9 - it makes it possible_to determine which line of a table is the last *//
//* one. Test with empty lines after the table and files that don't end with a *//
//* newline at_all *//

// chapter23_ex09_in1.txt ends with \n on the last line //
// chapter23_ex09_in2.txt has empty lines after the table //
// chapter23_ex09_in3.txt ends wihtout a newline
// chapter23_ex09_in4.txt has an empty line in the middle

#include "pch.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <stdexcept>
#include <exception>
#include <iostream>




template<class T> T from_string(const std::string& s)
{
	std::istringstream is(s);
	T t;
	if (!(is >> t)) std::cout << "bad from_string" << std::endl; {
		return 0;
	}
	return t;
}


int main()
try
{
	std::ifstream in("Text.txt");
	if (!in) std::cerr << "failed to open " << std::endl;

	std::string line;
	int lineno = 0;

	std::regex header("^[\\w ]+(\\t[\\w ]+)*$");
	std::regex row("^[\\w ]+(\\t\\d+)(\\t\\d+)(\\t\\d+)$");

	if (getline(in, line)) {
		std::smatch matches;
		if (!regex_match(line, matches, header)) {
			std::cerr << "no header" << std::endl;
		}
	}

	// column totals:
	int boys = 0;
	int girls = 0;

	// current line values:
	int curr_boy = 0;
	int curr_girl = 0;

	while (getline(in, line)) {  // extract and check data
		++lineno;
		if (line == "") continue;
		std::smatch matches;
		if (!std::regex_match(line, matches, row))
			std::cerr << "bad line " + std::to_string(lineno) << std::endl;

		// check row:
		curr_boy = from_string<int>(matches[1]);
		curr_girl = from_string<int>(matches[2]);
		int curr_total = from_string<int>(matches[3]);
		if (curr_boy + curr_girl != curr_total) std::cerr << "bad row sum" << std::endl;

		boys += curr_boy;
		girls += curr_girl;
	}

	// check columns:
	if (2 * curr_boy != boys)  std::cerr << "boys don't add up " << std::endl;;
	if (2 * curr_girl != girls) std::cerr << "girls don't add up " << std::endl;;
	std::cout << "Checked " << lineno << " lines - all good!\n" << std::endl;;
}
catch (std::exception& e) {
	std::cerr << "error: " << e.what() << std::endl;
	return 1;
}
catch (...) {
	std::cerr << "Oops: unknown exception!\n" << std::endl;
	return 2;
}
