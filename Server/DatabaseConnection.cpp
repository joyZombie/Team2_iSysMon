#if 0

#include <iostream>
#include <mysql.h>
#include<sstream>
using namespace std;
int main()
{
	MYSQL mysql, * connection;
	MYSQL_RES result;
	MYSQL_ROW row;
	int nQueryState = 0;
	int Id = 0;
	string Name;
	int score;



	cout << "Enter the Id ";
	cin >> Id;



	cout << "Enter the Name ";
	cin >> Name;



	cout << "Enter the Score ";
	cin >> score;



	stringstream ss;
	ss << "insert into test1 values(";
	ss << Id;
	ss << ",\'";
	ss << Name;
	ss << "\',";
	ss << score;
	ss << ");";



	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql, "localhost", "root", "nitsh@admin2", "SysMonitor", 3306, NULL, 0);



	if (connection == NULL)
	{
		cout << mysql_error(&mysql) << endl;
	}
	else {
		nQueryState = mysql_query(&mysql, ss.str().c_str());



		if (nQueryState != 0) {
			cout << mysql_error(connection) << endl;
			return 1;
		}
	}



	mysql_close(&mysql);
	return 0;
}

#endif