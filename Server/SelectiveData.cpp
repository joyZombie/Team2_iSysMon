#include "server.h"

void SelectiveData() {
	stringstream selective;
	selective << "select * from stats where user_id = 'abc123' order by time_sec desc limit 5;";
	
}