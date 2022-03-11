#include "server.h"

#define FILE "Server.log"

void logger(string message) {

	//int resDir = _mkdir(DIR);
	time_t result = std::time(nullptr);
	stringstream ss;
	string DateTime = ctime(&result);
	DateTime = DateTime.substr(0, DateTime.size() - 1);
	DateTime += ":> ";
	DateTime += message;

	ofstream output;
	output.open( FILE, std::ios_base::app);
	output << DateTime;
	output.close();
	//return FileName;
}