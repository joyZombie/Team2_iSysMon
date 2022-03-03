#include "FileWriter.h"
#include <direct.h>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

#pragma warning(disable : 4996)

#define DIR "Data/"

string FileWriter::putInFile(SystemInformation si)
{
	int resDir = _mkdir(DIR);
	time_t result = std::time(nullptr);
	string FileName = ctime(&result);
	FileName = FileName.substr(0, FileName.size() - 1);
	FileName = FileName + ".csv";
	FileName.erase(remove(FileName.begin(), FileName.end(), ':'), FileName.end());
	ofstream output;

	output.open(DIR + FileName, ofstream::out);
	output << si.getData();
	output.close();
	return FileName;
}

void FileWriter::deleteFile(string FileName) {

	char File[50];

	File[0] = DIR[0];
	File[1] = DIR[1];
	File[2] = DIR[2];
	File[3] = DIR[3];
	File[4] = DIR[4];
	int i = 0;
	for (i = 0; i < FileName.size(); i++) {
		File[i + 5] = FileName[i];
	}
	File[i + 5] = '\0';
	int del = remove(File);

}
