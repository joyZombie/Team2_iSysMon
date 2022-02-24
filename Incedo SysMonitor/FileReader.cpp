#include "FileReader.h"
#include "FileWriter.h"
#include "Client.h"
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#pragma comment(lib, "User32.lib")

using namespace std;

string FileReader::getFile(string FileName, bool containPath)
{
	ifstream statsFile;
	string data;
	if (containPath)
	{
		statsFile.open(FileName);
	}
	else
	{
		statsFile.open("Data/" + FileName);
	}
	
	while (statsFile.good())
	{
		string currLine;
		getline(statsFile, currLine);
		data += currLine;
	}
	return data;
}

void FileReader::sendRemainingData()
{
	vector<string> files;
	string Directory = "Data";

	FILE* pipe = NULL;
	string pCmd = "dir /B " + string(Directory);
	char buf[256];

	if (NULL == (pipe = _popen(pCmd.c_str(), "rt")))
	{
		cout << "Oops..." << endl;
		return;
	}

	while (!feof(pipe))
	{
		if (fgets(buf, 256, pipe) != NULL)
		{
			files.push_back(string(buf));
		}

	}

	_pclose(pipe);

	vector<string>::const_iterator it = files.begin();
	string Data;
	while (it != files.end())
	{
		int res = 0;
		string name = *it;
		name.pop_back();
		res = SendData(FileReader::getFile(name));
		if (res == 1) FileWriter::deleteFile(name);
		it++;
	}
}