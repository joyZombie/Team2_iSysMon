#include "server.h"

void SelectiveData() {
	stringstream selective;
	selective << "select * from stats where user_id = 'abc123' order by time_sec desc limit 5;";
	
}
string verifyUserId(string userId)
{
	stringstream ss;
	ss << "INSERT IGNORE INTO users VALUES ('" << userId << "');";
	return ss.str();
}