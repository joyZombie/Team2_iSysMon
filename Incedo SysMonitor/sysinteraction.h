#include <iostream>
#include <WinSock2.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <Lmcons.h>
#include <tchar.h>
#include <comdef.h>
#include <Wbemidl.h>
# pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma once
#define HOSTNAME_SIZE 128


#pragma comment(lib, "ws2_32.lib")
#pragma once


class SystemInformation
{

private:
	std::string hostName{};
	std::string userName{};
	unsigned int totalRam{};
	unsigned int freeRam{};
	float cpuLoad{};
	std::string processorArchitecture{};
	unsigned int processorLevel{};
	unsigned int processorType{};
	UINT idleTime{};
	VARIANT GPU{};

	void fetchTotalRAM();
	void getUserName();
	void fetchAvailRAM();
	void fetchHostName();
	void GetCPULoad();
	void getSystemInfo();
	void getSystemIdleTime();
	void getGPU();

public:
	SystemInformation() = default;
	std::string getData();
	void putInFile();

};
