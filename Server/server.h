#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <vector>
#include <mysql.h>
#include <sstream>
#include <boost\crc.hpp>
#include <ctime>
#include <fstream>
#include <direct.h>
#include <sstream>

#pragma comment(lib, "User32.lib")
#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable : 4996)

using namespace std;

#define PASSWORD "nitish@admin2"
#define DATABASE "sysmonitor"
#define PORT 3306
#define USER "root"
#define HOST "localhost"
#define UPDATE_FAILED "failed"
#define UPDATED_SUCCESSFULLY "updated"

void updateDB(string data,char * echo_message);
vector<string> dataParser(string data);
void dbConnect(vector<string> dataStream,char* echo_message);
void createDB();
void SelectiveData();
string verifyUserId(string userId);
void logger(string message);
