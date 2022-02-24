#include "server.h"

void updateDB(string data,char * echo_message)
{
	// Parsing Data into Vector of Strings
	vector<string> dataStream;
	string item = "";

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i] != ',')
			item = item + data[i];
		else
		{
			dataStream.push_back(item);
			item = "";
		}
	}

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
	connection = mysql_real_connect(&mysql, "localhost", "root", "Adarsh08$", "sysmonitor", 3306, NULL, 0);

	if (connection == NULL)
	{
		strcpy(echo_message, "failed");
		cout << mysql_error(&mysql) << endl;
	}
	else {
		nQueryState = mysql_query(&mysql, ss.str().c_str());

		if (nQueryState != 0) {
			strcpy(echo_message, "failed");
			cout << mysql_error(connection) << endl;
			//return 1;
		}
	}

	mysql_close(&mysql);
}

