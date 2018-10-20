#include "pch.h"
#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <exception>

// 12: File_handle class with a constructor that takes
// a string argument (the file name), opens the file in the constructor and
// closes it in the destructor

class File_handle {
	FILE* file;
	std::string fname;
public:
	File_handle(const std::string& fileName, const std::string& fileMode) : file(0), fname(fileName) {
		std::cout << " Opening file " << fname << std::endl;
		errno = fopen_s(&file,fileName.c_str(), fileMode.c_str());
		if (errno > 0) std::cout << " Failed to open " << fname << std::endl;
	}
	~File_handle(){
		std::cout << " Closing file " << fname << std::endl;
		int i = fclose(file);
		if (i != 0) std::cerr << "Failed to close " << fname << std::endl;
	}
	FILE* getfile() { return file; } // return handle
};

int main()
{
	try {
		File_handle readfile("Text.txt", "r");
		int c; // note: int, not char, required to handle EOF
		while ((c = std::fgetc(readfile.getfile()) != EOF)) { // standard C I/O file reading loop
			std::putchar(c);
		}
	}
	catch (std::exception& e) {
		std::cerr << "exception: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "exception\n" << std::endl;
	}
}