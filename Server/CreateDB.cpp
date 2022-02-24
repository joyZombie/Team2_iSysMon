#include "server.h"

void createDB() {
	stringstream create_db,use_db,create_table;
	create_db << "create database sysmonitor;";
	use_db << "use sysmonitor;";
	create_table << "create table stats(user_id varchar(64),host_name varchar(64), user_name varchar(64),total_ram varchar(64), available_ram varchar(64),cpu_load varchar(64),architecture varchar(64),processor_type varchar(64),idle_time varchar(64),total_hdd varchar(64),available_hdd varchar(64),date_time varchar(64), time_sec varchar(64));";

}
