#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <vector>
#include <mysql.h>
#include <sstream>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

void updateDB(string data);
void createDB();
void SelectiveData();