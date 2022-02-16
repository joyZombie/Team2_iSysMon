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
	else
	{
		processorArchitecture = "Unknown Processor";
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

void SystemInformation::getGPU()
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
}

std::string SystemInformation::getData()
{
	std::stringstream data;
	fetchHostName();
	data << "HostName: " << hostName << " \n";
	getUserName();
	data << "UserName: " << userName << " \n";
	fetchTotalRAM();
	data << "Total Ram: " << totalRam << ' ' << "MB\n";
	fetchAvailRAM();
	data << "Available Ram: " << freeRam << ' ' << "MB\n";
	GetCPULoad();
	data << "CPU LOAD : " << cpuLoad << ' ' << "%\n";
	getSystemInfo();
	data << "Processor Architecture : " << processorArchitecture << ' ' << "\n";
	//data << "Processor Level : " << processorLevel << ' ' << "\n";
	data << "Processor Type : " << processorType << ' ' << "\n";
	getSystemIdleTime();
	data << "System Idle Time : " << idleTime << ' ' << "ms\n";
	getGPU();
	data << "GPU : " << GPU.bstrVal << ' ' << "\n";
	//std::wcout << "GPU : " << GPU.bstrVal << ' ' << "\n";
	return data.str();
}



void SystemInformation::putInFile()
{
	std::ofstream output;
	output.open("Stats.txt", std::ofstream::out);
	output << getData();
	output.close();
}