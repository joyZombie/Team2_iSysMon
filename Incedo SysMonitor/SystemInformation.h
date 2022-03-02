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
#include<chrono>
<<<<<<< HEAD
<<<<<<< HEAD
#include <time.h>
=======
>>>>>>> Sending all backlog files.
=======
#include <time.h>
>>>>>>> Added new fields and integrated server

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma once
#define HOSTNAME_SIZE 128

using namespace std;

#pragma comment(lib, "ws2_32.lib")
#pragma once

int SendData(string FileName);

class SystemInformation
{

private:
	std::string userId{};
	std::string hostName{};
	std::string userName{};
	unsigned int totalRam{};
	unsigned int freeRam{};
	float cpuLoad{};
	std::string processorArchitecture{};
	unsigned int processorLevel{};
	unsigned int processorType{};
	UINT idleTime{};
	UINT32 totalSpace{};
	UINT32 freeSpace{};
	std::string tmBuff{};

	void fetchTotalRAM();
	void getUserName();
	void fetchAvailRAM();
	void fetchHostName();
	void GetCPULoad();
	void getSystemInfo();
	void getSystemIdleTime();
	void getHardDiskSpace();
	void getCurrentTime();

public:
	SystemInformation() = default;
	std::string getData();
	std::string getDataToDisplay();
	void fetchAllData();
<<<<<<< HEAD
<<<<<<< HEAD
	void setUserId(LPSTR);
=======

>>>>>>> Sending all backlog files.
=======
	void setUserId(LPSTR);
>>>>>>> Added userID
};
