#include "sysinteraction.h"
#define _WIN32_DCOM
# pragma comment(lib, "wbemuuid.lib")



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
static float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
	static unsigned long long _previousTotalTicks = 0;
	static unsigned long long _previousIdleTicks = 0;

	unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
	unsigned long long idleTicksSinceLastTime = idleTicks - _previousIdleTicks;

	float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);

	_previousTotalTicks = totalTicks;
	_previousIdleTicks = idleTicks;
	return ret;
}

static unsigned long long FileTimeToInt64(const FILETIME& ft) { return (((unsigned long long)(ft.dwHighDateTime)) << 32) | ((unsigned long long)ft.dwLowDateTime); }

// Returns 1.0f for "CPU fully pinned", 0.0f for "CPU idle", or somewhere in between
// You'll need to call this at regular intervals, since it measures the load between
// the previous call and the current one.  Returns -1.0 on error.
void SystemInformation::GetCPULoad()
{
	FILETIME idleTime, kernelTime, userTime;
	cpuLoad = GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime) + FileTimeToInt64(userTime)) : -1.0f;
	cpuLoad = cpuLoad * 100;
}


void SystemInformation::getUserName()
{
	char userName[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserNameA(userName, &username_len);
	this->userName = std::string(userName);
}

void SystemInformation::getSystemInfo()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	processorArchitecture = "";
	if (sysInfo.wProcessorArchitecture == 9)
	{
		processorArchitecture = "x64(AMD or Intel)";
	}
	else if (sysInfo.wProcessorArchitecture == 6)
	{
		processorArchitecture = "Intel Itanium-based";
	}
	else if (sysInfo.wProcessorArchitecture == 12)
	{
		processorArchitecture = "ARM64";
	}
	else if (sysInfo.wProcessorArchitecture == 5)
	{
		processorArchitecture = "ARM";
	}
	else if (sysInfo.wProcessorArchitecture == 0)
	{
		processorArchitecture = "x86";
	}
	else
	{
		processorArchitecture = "Unknown architecture";
	}
	//processorLevel = sysInfo.wProcessorLevel;
	processorType = sysInfo.dwProcessorType;
}

void SystemInformation::getSystemIdleTime()
{
	LASTINPUTINFO li = { 0 };
	li.cbSize = sizeof(LASTINPUTINFO);
	GetLastInputInfo(&li);
	idleTime = GetTickCount() - li.dwTime;//in milliseconds
}

/*void SystemInformation::getGPU()
{
	HRESULT hres;
	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres)) return;
	hres = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	if (FAILED(hres)) {
		CoUninitialize();
		return;
	}
	IWbemLocator* pLoc = NULL;
	hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
	if (FAILED(hres)) {
		CoUninitialize();
		return;
	}
	IWbemServices* pSvc = NULL;
	hres = pLoc->ConnectServer(_bstr_t(L"root\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
	if (FAILED(hres)) {
		pLoc->Release();
		CoUninitialize();
		return;
	}
	hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	if (FAILED(hres)) {
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return;
	}
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_VideoController"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
	if (FAILED(hres)) {
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return;
	}
	IWbemClassObject* pclsObj;
	ULONG uReturn = 0;
	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (0 == uReturn)break;
		VARIANT vtProp;
		hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
		GPU.bstrVal = vtProp.bstrVal;
		//wcout << " OS Name : " << vtProp.bstrVal << endl;
		VariantClear(&vtProp);
	}
	pSvc->Release();
	pLoc->Release();
	pEnumerator->Release();
	//pclsObj->Release();
	CoUninitialize();
}*/


void SystemInformation::getHardDiskSpace()
{
	BOOL fResult;
	unsigned __int64 i64FreeBytesToCaller,
		i64TotalBytes,
		i64FreeBytes;
	fResult = GetDiskFreeSpaceEx(L"C:",
		(PULARGE_INTEGER)&i64FreeBytesToCaller,
		(PULARGE_INTEGER)&i64TotalBytes,
		(PULARGE_INTEGER)&i64FreeBytes);
	if (fResult)
	{
		/*printf("\n\nGetDiskFreeSpaceEx reports\n\n");
		printf("Available space to caller = %I64u MB\n",
			i64FreeBytesToCaller / (1024 * 1024));
		printf("Total space               = %I64u MB\n",
			i64TotalBytes / (1024 * 1024));
		printf("Free space on drive       = %I64u MB\n",
		i64FreeBytes / (1024 * 1024));*/
		totalSpace = i64TotalBytes / (1024 * 1024);
		freeSpace = i64FreeBytes / (1024 * 1024);
	}
}
void SystemInformation::getCurrentTime()
{
		auto start = std::chrono::system_clock::now();
		auto legacyStart = std::chrono::system_clock::to_time_t(start);
		char tmBuff[30];
		time_t now = time(0);
		ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);
		this->tmBuff = std::string(tmBuff);
}


std::string SystemInformation::getData()
{
	std::stringstream data;
	fetchHostName();
	data << userId << ",";
	data << hostName << ",";
	data  << userName << ",";
	data << totalRam << ' ' << ",";
	data << freeRam << ' ' << ",";
	data << cpuLoad << ' ' << ",";
	data << processorArchitecture << ",";
	//data << "Processor Level : " << processorLevel << ' ' << "\n";
	data << processorType << ' ' << ",";
	data << idleTime << ' ' << ",";
	data << totalSpace << ",";
	data << freeSpace << ",";
	data << tmBuff << ",";
	data << long(time(0)) << ",";
	//getGPU();
	//data << "GPU : " << GPU.bstrVal << ' ' << "\n";
	//std::wcout << "GPU : " << GPU.bstrVal << ' ' << "\n";
	data << '\n';
	return data.str();
}

std::string SystemInformation::getDataToDisplay()
{
	std::stringstream data;
	data << "User ID: " << userId << " \n";
	data << "HostName: " << hostName << " \n";
	data << "UserName: " << userName << " \n";
	data << "Total Ram: " << totalRam << ' ' << "MB\n";
	data << "Available Ram: " << freeRam << ' ' << "MB\n";
	data << "CPU LOAD: " << cpuLoad << ' ' << "%\n";
	data << "Processor Architecture: " << processorArchitecture << ' ' << "\n";
	//data << "Processor Level : " << processorLevel << ' ' << "\n";
	data << "Processor Type: " << processorType << ' ' << "\n";
	data << "System Idle Time: " << idleTime << ' ' << "ms\n";
	data << "Total Hard Disk Space: " << totalSpace << ' ' << "MB\n";
	data << "Free Hard Disk Space: " << freeSpace << ' ' << "MB\n";
	data << "Current Time: " << tmBuff << ' ' << "\n";
	data << "Time in seconds: " << long(time(0)) << ' ' << "\n";
	//getGPU();
	//data << "GPU : " << GPU.bstrVal << ' ' << "\n";
	//std::wcout << "GPU : " << GPU.bstrVal << ' ' << "\n";
	return data.str();
}


void SystemInformation::fetchAllData()
{
	fetchHostName();
	getUserName();
	fetchTotalRAM();
	fetchAvailRAM();
	GetCPULoad();
	getSystemInfo();
	getSystemIdleTime();
	getHardDiskSpace();
	getCurrentTime();
}


void SystemInformation::setUserId(LPSTR id)
{
	this->userId = std::string(id);
}


