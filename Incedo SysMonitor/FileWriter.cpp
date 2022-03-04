#include "FileWriter.h"
#include <direct.h>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

#pragma warning(disable : 4996)

//#define DIR "Data/"
#define FILENAME_SIZE 128

string FileWriter::putInFile(SystemInformation si)
{
	int resDir = _mkdir(DIR.c_str());
	time_t result = std::time(nullptr);
	string FileName = ctime(&result);
	FileName = FileName.substr(0, FileName.size() - 1);
	FileName = FileName + ".csv";
	FileName.erase(remove(FileName.begin(), FileName.end(), ':'), FileName.end());
	ofstream output;

	output.open(DIR + "/" + FileName, ofstream::out);
	output << si.getData();
	output.close();
	return FileName;
}

void FileWriter::deleteFile(string FileName) {

	char* File = new char[FILENAME_SIZE];
	int len = DIR.length() + 1;
	strncpy(File, (DIR + "/").c_str(), len);
	int i = 0;
	for (i = 0; i < FileName.size(); i++) {
		File[i + len] = FileName[i];
	}
	File[i + len] = '\0';
	int del = remove(File);
	delete[] File;

}

string FileWriter::DIR = "";
