#include "server.h"

<<<<<<< HEAD
vector<string> dataParser(string data)
=======
#pragma comment (lib, "ws2_32.lib")

using namespace std;


void updateDB(string data)
>>>>>>> Sending all backlog files.
{
	vector<string> dataItems;
	string item = "";

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i] != ',')
			item = item + data[i];
		else
		{
			dataItems.push_back(item);
			item = "";
		}
	}

	return dataItems;
}

void dbConnect(vector<string> dataStream, char* echo_message)
{
	// Opening DB Connection
	MYSQL mysql, * connection;
	MYSQL_RES result;
	MYSQL_ROW row;

	int nQueryState = 0;

	// Creating Query Stream for passing as String
	stringstream ss;
	ss << "insert into stats values(";

	for (auto value : dataStream)
	{
		ss << "\'";
		ss << value;
		if(value != dataStream.back())
			ss << "\',";
		else
			ss << "\');";
	}
 
	// DB Code begins here 
	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql, "localhost", "root", "nitish@admin2", "sysmonitor", 3306, NULL, 0);

	if (connection == NULL)
	{
		strcpy(echo_message, "failed");
		cout << mysql_error(&mysql) << endl;
	}
	else {
		mysql_query(&mysql, verifyUserId(dataStream[0]).c_str());

		nQueryState = mysql_query(&mysql, ss.str().c_str());
		
		if (nQueryState != 0) {
			strcpy(echo_message, "failed");
			cout << mysql_error(connection) << endl;
			//return 1;
		}
	}
	mysql_close(&mysql);
}

<<<<<<< HEAD
void updateDB(string data,char * echo_message)
=======
int main()
>>>>>>> Sending all backlog files.
{
	// Parsing Data into Vector of Strings
	vector<string> dataStream;
	int hashPosition = data.find("#");
	string information, hash;

	// Fetching CRC Checksum present as the end of Data
	information = data.substr(0, hashPosition);
	hash = data.substr(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(hashPosition) + 1);

	// Hash verification
	stringstream checkSum;
	boost::crc_32_type  crc;
	crc.process_bytes(information.data(), information.size());
	checkSum << hex << crc.checksum();

	if (hash != checkSum.str())
	{
<<<<<<< HEAD
		cout << "Checksum mismatch...Data Corrupted !!\nAborted the process.\n";
		return;
	}

	dataStream = dataParser(information);
	dbConnect(dataStream, echo_message);
}

=======
		cerr << "Can't Initialize winsock! Quitting" << endl;
		return -1;
	}

	// Initialize do-While Loop to keep socket open until ESC is pressed
	bool exit = false;
	cout << "Initialized server program. Press ESC to exit!" << endl;

	do {

		// Create a socket
		SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
		if (listening == INVALID_SOCKET)
		{
			cerr << "Can't create a socket! Quitting" << endl;
			return -1;
		}

		// Bind the ip address and port to a socket
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(8080);
		hint.sin_addr.S_un.S_addr = INADDR_ANY;

		bind(listening, (sockaddr*)&hint, sizeof(hint));

		// Tell Winsock the socket is for listening 
		listen(listening, SOMAXCONN);

		// Wait for a connection
		sockaddr_in client;
		int clientSize = sizeof(client);
		SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

		char host[NI_MAXHOST];		// Client's remote name
		char service[NI_MAXSERV];	// Service (i.e. port) the client is connect on

		ZeroMemory(host, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
		ZeroMemory(service, NI_MAXSERV);

		cout << "Waiting for client to establish connection ..." << endl;

		if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
		{
			cout << host << " connected on port " << service << endl;
		}
		else
		{
			inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
			cout << host << " connected on port " <<
				ntohs(client.sin_port) << endl;
		}

		// Close listening socket
		closesocket(listening);

		// While loop: accept and echo message back to client
		char buf[4096];

		while (true)
		{
			ZeroMemory(buf, 4096);

			// Wait for client to send data
			int bytesReceived = recv(clientSocket, buf, 4096, 0);
			if (bytesReceived == SOCKET_ERROR)
			{
				cerr << "Error in receiving data. Quitting the process..." << endl;
				break;
			}

			if (bytesReceived == 0)
			{
				cout << "Client disconnected. " << endl;
				break;
			}

			string data = string(buf, 0, bytesReceived);
			updateDB(data);

			// Echo message back to client
			send(clientSocket, buf, bytesReceived + 1, 0);

		}

		// Close the socket
		closesocket(clientSocket);

		Sleep(1000);

		if (GetAsyncKeyState(VK_ESCAPE))
			exit = true;

	} while (!exit);

	// Cleanup winsock
	WSACleanup();

	system("pause");
	return 0;
}


#if 0
int qstate;


int main()
{
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);



	conn = mysql_real_connect(conn, "localhost", "root", "nitish@admin2", "sysmonitor", 3306, NULL, 0);



	if (conn) {
		puts("Successful connection to database!");



		string query = "SELECT * from test1;";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("ID: %s, Name: %s, Value: %s\n", row[0], row[1], row[2]);
			}
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("Connection to database has failed!");
	}


	return 0;
}
#endif
>>>>>>> Sending all backlog files.
