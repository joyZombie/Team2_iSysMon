SysMonitor
A central monitoring system built using basic client-server model to collect system information from multiple nodes over a network. This system information is being sent periodically to a server to update about its state with following parameters:

* __System-name__

* __RAM usage__

* __CPU utilization__

* __System Idle window__

* __HardDisk utilization__

* __Processor Information etc.__


# Folder structure
<pre>
📦Incedo SysMonitor
 ┣ 📦Client
	┗ 📜Client.h 
 ┣ 📦SystemInteraction
	┣ 📜FileReader.h
        ┣ 📜FileWriter.h
        ┣ 📜SystemInformation.h
 	┗ 📜Timer.h
 ┣ 📜framework.h
 ┣ 📜Incedo SysMonitor.h
 ┣ 📜targetver.h
 ┣ 📜Resource.h
 ┣ 📜Client.cpp
 ┣ 📜FileReader.cpp
 ┣ 📜FileWriter.cpp
 ┣ 📜Incedo SysMonitor.cpp
 ┣ 📜SystemInformation.cpp
 ┣ 📜Timer.cpp

📦Server
 ┣ 📜server.h
 ┣ 📜CreateDB.cpp
 ┣ 📜DatabaseConnection.cpp
 ┣ 📜Selective Data.cpp
 ┗ 📜server.cpp
</pre> 

## STEPS TO USE:

* RUN THE SERVER.EXE FILE
* RUN THE CLIENT.EXE FILE
* ENTER THE UNIQUE CLIENT IDENTIFIER(PRIMARY KEY).
* ENTER THE USERID, WHOSE INFORMATION YOU WANT TO SEE.

Now, You are ready to sneak through some interesting system stats.

#### PROJECT CONTRIBUTORS:-
- ##### System Interaction Team
  - Hashmeet Singh
  - Adarsh Kumar
  - Nitish Kumar
- ##### Socket Programming Team
  - Ashutosh Tripathi
  - Yatharth Sharma
- ##### Database Team
  - Piyush Priyadarshi
