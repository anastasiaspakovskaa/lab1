#include <iostream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <codecvt>

using namespace std;

struct employee
{
	int num;
	char name[10];
	double hours;
};

int main(int argc, char* argv[])
{
	string fileNameBin;
	string fileNameTxt;
	fileNameBin = argv[1];
	fileNameTxt = argv[2];
	double salary = atof(argv[3]);

	fstream file_bin;
	ofstream file_txt;
	file_txt.open(fileNameTxt, ios::out | ios::trunc);

	if (file_txt.is_open()) {
		cout << "\n" << argv[2] << " is open";
	}
	else {
		cout << "\n" << argv[2] << " isn't open" << "\n";
	}

	file_txt << "\n" << "File report «" << fileNameBin << "»\n";

	file_bin.open(fileNameBin, ios::in | ios::binary);

	if (file_bin.is_open()) {
		cout << "\n" << argv[1] << " is open";
	}
	else {
		cout << "\n" << argv[1] << " isn't open";
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
