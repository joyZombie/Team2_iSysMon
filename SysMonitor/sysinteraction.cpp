#include "sysinteraction.h"
 

void SystemInformation::fetchTotalRAM()
{
	MEMORYSTATUSEX m;
	m.dwLength = sizeof(m);
	GlobalMemoryStatusEx(&m);
	totalRam = (int)(m.ullTotalPhys >> 20);
}

void SystemInformation::fetchAvailRAM()
{
	MEMORYSTATUSEX m;
	m.dwLength = sizeof(m);
	GlobalMemoryStatusEx(&m);
	freeRam = (int)(m.ullAvailPhys >> 20);
}

void SystemInformation::fetchHostName() 
{
	char hostName[HOSTNAME_SIZE] = "";
	WSADATA wsaData;
	auto res = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (res == 0) {
		gethostname(hostName, HOSTNAME_SIZE);
	}
	WSACleanup();
	this->hostName = std::string(hostName);
}

std::string SystemInformation::getData()
{
	std::stringstream data;
	fetchHostName();
	data << "HostName: " << hostName << " \n";
	fetchTotalRAM();
	data << "Total Ram: " << totalRam << ' ' << "MB\n";
	fetchAvailRAM();
	data << "Available Ram: " << freeRam << ' ' << "MB\n";
	return data.str();
}



void SystemInformation::putInFile()
{
	std::ofstream output;
	output.open("Stats.txt", std::ofstream::out);
	output << getData();
	output.close();
}