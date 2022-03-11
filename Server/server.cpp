#include "server.h"

int main()
{
	char echo_message[8] = "";
	// Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		logger("Can't Initialize winsock! Stopping...",Error);
		cerr << "Can't Initialize winsock! Quitting" << endl;
		return -1;
	}
	
	// Initialize do-While Loop to keep socket open until ESC is pressed
	bool exit = false;
	cout << "Initialized server program. Press ESC to exit!" << endl;
	

	do {

		// Create a socket
		logger("Server listening, waiting for client to establish connection....\n",Information);
		SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
		if (listening == INVALID_SOCKET)
		{
			logger("Can't create a socket! Stopping...\n",Error);
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
			logger("Connection established.\n",Information);
			cout << host << " connected on port " << service << endl;
		}
		else
		{
			logger("Connection established.\n",Information);
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
				logger("Error in receiving data. Stopping the process...\n",Error);
				cerr << "Error in receiving data. Quitting the process..." << endl;
				break;
			}

			if (bytesReceived == 0)
			{
				logger("Client Disconnected.\n",Information);
				cout << "Client disconnected. " << endl;
				break;
			}

			string data = string(buf, 0, bytesReceived);
			logger("Recieved Data from client: " + data+"\n",Information);
			strcpy(echo_message, UPDATED_SUCCESSFULLY);

			updateDB(data,echo_message);
			cout << data << endl;
			// Echo message back to client
			send(clientSocket, echo_message, bytesReceived + 1, 0);

		}

		// Close the socket
		closesocket(clientSocket);

		logger("Socket Closed.\n",Information);
		
		Sleep(1000);

		if (GetAsyncKeyState(VK_ESCAPE))
			exit = true;

	} while (!exit);

	// Cleanup winsock
	WSACleanup();

	system("pause");
	return 0;
}
