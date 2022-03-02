#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <vector>
#include <mysql.h>
#include <sstream>
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Added boost library
#include <boost\crc.hpp>

#pragma comment(lib, "User32.lib")
#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable : 4996)

using namespace std;


void updateDB(string data,char * echo_message);
vector<string> dataParser(string data);
void dbConnect(vector<string> dataStream,char* echo_message);
void createDB();
void SelectiveData();
<<<<<<< HEAD
<<<<<<< HEAD
string verifyUserId(string userId);
=======

#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable : 4996)

using namespace std;


void updateDB(string data,char * echo_message);
void createDB();
void SelectiveData();
>>>>>>> Added new fields and integrated server
=======
string verifyUserId(string userId);
>>>>>>> Made primary key and handled verification.
=======
string verifyUserId(string userId);
>>>>>>> Added boost library
