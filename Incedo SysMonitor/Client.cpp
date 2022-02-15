#include "sysinteraction.h"
#include <iostream>
#include <WS2tcpip.h>

using namespace std;

void SendData()
{
	SystemInformation si;
	string ipaddress = "127.0.0.1";			// ip address of the server
	int port = 8080;						// listening port # on the server
	
	// initialize winsock
	wsadata data;
	word ver = makeword(2, 2);
	int wsresult = wsastartup(ver, &data);
	if (wsresult != 0)
	{
		cerr << "can't start winsock, err #" << wsresult << endl;
		return 0;
	}
	
	// create socket
	socket sock = socket(af_inet, sock_stream, 0);
	if (sock == invalid_socket)
	{
		cerr << "can't create socket, err #" << wsagetlasterror() << endl;
		wsacleanup();
		return 0;
	}
	
	// fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = af_inet;
	hint.sin_port = htons(port);
	inet_pton(af_inet, ipaddress.c_str(), &hint.sin_addr);
	
	// connect to server
	int connresult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connresult == socket_error)
	{
		cerr << "can't connect to server, err #" << wsagetlasterror() << endl;
		closesocket(sock);
		wsacleanup();
		return 0;
	}
	else
	{
		cout << "connection established to server." << endl;
	}
	
	
	// this needs modification to work for client side data fetching. modify as needed.
	// stored data for passing to the server only one time. further modification can add more robustness
	char buf[4096];
	string userinput;
	userinput = si.getdata();
	if (userinput.size() > 0)				// make sure the user has typed in something
	{
		// send the text
		int sendresult = send(sock, userinput.c_str(), userinput.size() + 1, 0);
		if (sendresult != socket_error)
		{
			// waiting for response
			zeromemory(buf, 4096);
			int bytesreceived = recv(sock, buf, 4096, 0);
			if (bytesreceived > 0)
			{
				// echo client response to console
				cout << "server> " << string(buf, 0, bytesreceived) << endl;
			}
		}
	}
	
	// shut down everything
	closesocket(sock);
	wsacleanup();
	cout << "sent data & disconnected from server" << endl;
	system("pause");
}

