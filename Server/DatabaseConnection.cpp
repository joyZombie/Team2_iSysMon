#include "server.h"

vector<string> dataParser(string data)
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
	connection = mysql_real_connect(&mysql, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0);

	if (connection == NULL)
	{
		strcpy(echo_message, UPDATE_FAILED);
		cout << mysql_error(&mysql) << endl;
	}
	else {
		mysql_query(&mysql, verifyUserId(dataStream[0]).c_str());

		nQueryState = mysql_query(&mysql, ss.str().c_str());
		
		if (nQueryState != 0) {
			strcpy(echo_message, UPDATE_FAILED);
			cout << mysql_error(connection) << endl;
			//return 1;
		}
	}
	mysql_close(&mysql);
}

void updateDB(string data,char * echo_message)
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
		strcpy(echo_message, UPDATE_FAILED);
		cout << "Checksum mismatch...Data Corrupted !!\nAborted the process.\n";
		return;
	}

	dataStream = dataParser(information);
	dbConnect(dataStream, echo_message);
}

