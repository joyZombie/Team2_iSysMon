#include "server.h"

void SelectiveData() {
	stringstream selective;
	selective << "select * from stats where user_id = 'abc123' order by time_sec desc limit 5;";
	
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Made primary key and handled verification.
}
string verifyUserId(string userId)
{
	stringstream ss;
	ss << "INSERT IGNORE INTO users VALUES ('" << userId << "');";
	return ss.str();
<<<<<<< HEAD
=======
>>>>>>> Added query for reference
=======
>>>>>>> Made primary key and handled verification.
}