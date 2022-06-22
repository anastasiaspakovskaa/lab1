#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <codecvt>
#include "D:\unik\OS\lab1\main\Header.h"

int main(int argc, char* argv[])
{
	std::string fileNameBin;
	std::string fileNameTxt;
	fileNameBin = argv[1];
	fileNameTxt = argv[2];
	double salary = atof(argv[3]);

	std::fstream file_bin;
	std::ofstream file_txt;
	file_txt.open(fileNameTxt, std::ios::out | std::ios::trunc);

	if (file_txt.is_open()) {
		std::cout << "\n" << argv[2] << " is open";
	}
	else {
		std::cout << "\n" << argv[2] << " isn't open" << "\n";
	}

	file_txt << "\n" << "File report «" << fileNameBin << "»\n";

	file_bin.open(fileNameBin, std::ios::in | std::ios::binary);

	if (file_bin.is_open()) {
		std::cout << "\n" << argv[1] << " is open";
	}
	else {
		std::cout << "\n" << argv[1] << " isn't open";
	}

	employee emp;

	while (!file_bin.eof()) {

		file_bin.read((char*)&emp, sizeof(emp));

		if (file_bin.eof()) {
			break;
		}

		file_txt << emp.num << " " << emp.name << " " << emp.hours << " " << (emp.hours * salary) << "\n";
	}

	file_bin.close();
	file_txt.close();

	return 0;
}
