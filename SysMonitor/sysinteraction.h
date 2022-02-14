#include <iostream>
#include <WinSock2.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>

#define HOSTNAME_SIZE 128


#pragma comment(lib, "ws2_32.lib")
#pragma once


class SystemInformation
{
private:
	std::string hostName{};
	unsigned int totalRam{};
	unsigned int freeRam{};

	void fetchTotalRAM();
	void fetchAvailRAM();
	void fetchHostName();

public:
	SystemInformation() = default;
	std::string getData();
	void putInFile();

};
