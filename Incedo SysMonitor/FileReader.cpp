#include "sysinteraction.h"
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#pragma comment(lib, "User32.lib")

string SystemInformation::getFile()
{
	vector<string> files;
	string Directory = "Data";

	FILE* pipe = NULL;
	string pCmd = "dir /B /S " + string(Directory);
	char buf[256];

	if (NULL == (pipe = _popen(pCmd.c_str(), "rt")))
	{
		cout << "Oops..." << endl;
		return "Hello\n";
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

		ifstream StatsFile;

		string path = *it;
		replace(path.begin(), path.end(), '\\', '/');
		
		int path_size = path.size();
		path = path.substr(0, path_size - 1);
		StatsFile.open(path);

		while (StatsFile.good()) {
			string Line;
			getline(StatsFile, Line, ',');
			Data += Line;

		}
		it++;
	}
	
	return Data;
}