#include "sysinteraction.h"
#include <direct.h>
#include <ctime>
using namespace std;

#pragma warning(disable : 4996)

string SystemInformation::putInFile()
{
	time_t result = std::time(nullptr);
	string FileName = ctime(&result);
	FileName = FileName.substr(0, FileName.size() - 1);
	FileName = FileName + ".csv";
	FileName.erase(remove(FileName.begin(), FileName.end(), ':'), FileName.end());
	ofstream output;

	output.open("Data/" + FileName, ofstream::out);
	output << getData();
	output.close();
	return FileName;
}