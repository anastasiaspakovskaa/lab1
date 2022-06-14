#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <codecvt>

using namespace std;

struct employee
{
	int num;
	char name[10];
	double hours;
};

void replace(string& str, const string& from, const string& to) {
	if (from.empty())
		return;
	string::size_type start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

int main(int argc, char* argv[])
{
	string fileName;
	int numberOfRecords;

	cout << "Write name of bin file: ";
	cin >> fileName;
	cout << "Write number of records: ";
	cin >> numberOfRecords;

	string path = argv[0];
	cout << path;
	replace(path, "main.exe", "");

	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	if (CreateProcess((LPCWSTR)wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(path + "creator.exe").c_str(),
		(LPWSTR)wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(path + "creator.exe " + fileName + " " + to_string(numberOfRecords)).c_str(),
		NULL, NULL, FALSE, NULL, NULL, NULL, &si, &piApp))
	{
		WaitForSingleObject(piApp.hProcess, INFINITE);
		CloseHandle(piApp.hThread);
		CloseHandle(piApp.hProcess);
	}
	else {
		cout << "Process creator.exe not start";
		cout << GetLastError();
		return 1;
	}

	fstream file_bin;
	file_bin.open(fileName, ios::in | ios::binary);
	employee emp;
	while (!file_bin.eof()) {

		file_bin.read((char*)&emp, sizeof(emp));
		if (file_bin.eof()) break;
		cout << emp.num << " " << emp.name << " " << emp.hours << "\n";
	}

	file_bin.close();

	string fileNameTxt;
	double salary;

	cout << "\nWrite name of report file: ";
	cin >> fileNameTxt;
	cout << "Write salary: ";
	cin >> salary;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	if (CreateProcess((LPCWSTR)wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(path + "reporter.exe").c_str(),
		(LPWSTR)wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(path + "reporter.exe " + fileName + " " + fileNameTxt + " " + to_string(salary)).c_str(),
		NULL, NULL, FALSE, NULL, NULL, NULL, &si, &piApp))
	{
		WaitForSingleObject(piApp.hProcess, INFINITE);
		CloseHandle(piApp.hThread);
		CloseHandle(piApp.hProcess);
	}
	else {
		cout << "Process reporter.exe not start";
		return 1;
	}

	fstream file_txt;
	file_txt.open(fileNameTxt, ios::in);
	string line;
	if (file_txt.is_open()) {
		while (getline(file_txt, line))
		{
			cout << line << endl;
		}
	}

	file_txt.close();

	return 0;
}