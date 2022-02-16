#include "sysinteraction.h"
#include <direct.h>

using namespace std;

#pragma warning(disable : 4996)

void SystemInformation::putInFile()
{

	string FileName = "Data/Stats.csv";

	ofstream output;
	output.open(FileName, ofstream::out);
	output << getData();
	output.close();
}