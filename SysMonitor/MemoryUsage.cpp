#include <Windows.h>
#include <iostream>
#include "sysinteraction.h"

using namespace std;


int getTotalRAM()
{
    int ret = 0;
    MEMORYSTATUSEX m;
    m.dwLength = sizeof(m);
    GlobalMemoryStatusEx(&m);
    ret = (int)(m.ullTotalPhys >> 20);
    return ret;
}

int getAvailRAM()
{
    int ret = 0;

    MEMORYSTATUSEX m;
    m.dwLength = sizeof(m);
    GlobalMemoryStatusEx(&m);
    ret = (int)(m.ullAvailPhys >> 20);

    return ret;
}