#include "pch.h"
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <exception>
#include <fstream>
#include <algorithm>
// read file of whitespace - separated numbers, output
// them in order, one value per line. if a value occurs more than once, write
// the count of its occurrences on its line.
//
// example: "7 5 5 7 3 117 5" should give
//  3
//  5   3
//  7   2
//  117
int main()
try {

	std::string fname = "Text.txt";
	std::ifstream ifs(fname.c_str());
	if (!ifs) std::cerr << "can't open input file " << fname << std::endl;
	int n;
	std::vector<int> numbers;
	while (ifs >> n)
		numbers.push_back(n);
	std::sort(numbers.begin(), numbers.end());
	int counter = 1;
	for (int i = 0; i < numbers.size(); ++i) {
		if (i == 0 || numbers[i] != numbers[i - 1]) {
			if (counter > 1) std::cout << "\t" << counter;
			std::cout << std::endl;
			counter = 1;
			std::cout << numbers[i];
		}
		else ++counter;
	}
}
catch (std::exception& e) {
	std::cerr << "exception: " << e.what() << std::endl;
}
catch (...) {
	std::cerr << "exception\n";
}