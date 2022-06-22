#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <codecvt>
#include "Header.h"

void replace(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty())
		return;
	std::string::size_type start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

int main(int argc, char* argv[])
{
	std::string fileName;
	int numberOfRecords;

	std::cout << "Write name of bin file: ";
	std::cin >> fileName;
	std::cout << "Write number of records: ";
	std:: cin >> numberOfRecords;

	std::string path = argv[0];
	std::cout << path;
	replace(path, "main.exe", "");

	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	if (CreateProcess((LPCWSTR)std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(path + "creator.exe").c_str(),
		(LPWSTR)std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(path + "creator.exe " + fileName + " " + std::to_string(numberOfRecords)).c_str(),
		NULL, NULL, FALSE, NULL, NULL, NULL, &si, &piApp))
	{
		WaitForSingleObject(piApp.hProcess, INFINITE);
		CloseHandle(piApp.hThread);
		CloseHandle(piApp.hProcess);
	}
	else {
		std::cout << "Process creator.exe not start";
		std::cout << GetLastError();
		return 1;
	}

	std::fstream file_bin;
	file_bin.open(fileName, std::ios::in | std::ios::binary);
	employee emp;
	while (!file_bin.eof()) {

		file_bin.read((char*)&emp, sizeof(emp));
		if (file_bin.eof()) break;
		std::cout << emp.num << " " << emp.name << " " << emp.hours << "\n";
	}

	file_bin.close();

	std::string fileNameTxt;
	double salary;

	std::cout << "\nWrite name of report file: ";
	std::cin >> fileNameTxt;
	std::cout << "Write salary: ";
	std::cin >> salary;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	if (CreateProcess((LPCWSTR)std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(path + "reporter.exe").c_str(),
		(LPWSTR)std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(path + "reporter.exe " + fileName + " " + fileNameTxt + " " + std::to_string(salary)).c_str(),
		NULL, NULL, FALSE, NULL, NULL, NULL, &si, &piApp))
	{
		WaitForSingleObject(piApp.hProcess, INFINITE);
		CloseHandle(piApp.hThread);
		CloseHandle(piApp.hProcess);
	}
	else {
		std::cout << "Process reporter.exe not start";
		return 1;
	}

	std::fstream file_txt;
	file_txt.open(fileNameTxt, std::ios::in);
	std::string line;
	if (file_txt.is_open()) {
		while (getline(file_txt, line))
		{
			std::cout << line << std::endl;
		}
	}

	file_txt.close();

	return 0;
}