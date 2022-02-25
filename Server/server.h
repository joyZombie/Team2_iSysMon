#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <vector>
#include <mysql.h>
#include <sstream>
#include <boost\crc.hpp>

#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable : 4996)

using namespace std;


void updateDB(string data,char * echo_message);
void createDB();
void SelectiveData();
string verifyUserId(string userId);
