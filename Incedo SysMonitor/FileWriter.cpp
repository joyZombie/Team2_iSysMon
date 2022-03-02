#include "FileWriter.h"
#include <direct.h>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

#pragma warning(disable : 4996)

string FileWriter::putInFile(SystemInformation si)
{
	_mkdir("Data/");
	time_t result = std::time(nullptr);
	string FileName = ctime(&result);
	FileName = FileName.substr(0, FileName.size() - 1);
	FileName = FileName + ".csv";
	FileName.erase(remove(FileName.begin(), FileName.end(), ':'), FileName.end());
	ofstream output;

	output.open("Data/" + FileName, ofstream::out);
	output << si.getData();
	output.close();
	return FileName;
}

void FileWriter::deleteFile(string FileName) {

	char File[50];

	File[0] = 'D';
	File[1] = 'a';
	File[2] = 't';
	File[3] = 'a';
	File[4] = '/';
	int i = 0;
	for (i = 0; i < FileName.size(); i++) {
		File[i + 5] = FileName[i];
	}
	File[i + 5] = '\0';
	int del = remove(File);

}
