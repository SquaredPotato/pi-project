#ifndef COLUMN_MYSQL_HPP
#define COLUMN_MYSQL_HPP

#include <string>
#include <sstream>

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class mysql {
public:
	mysql(std::string server, std::string username, std::string password, std::string dbname);

	// Pin operations
	void input (std::string name, int num, int nodeID, int edge, int upDown);
	void output (std::string name, int num, int nodeID, int state);
	void PWMOutput (std::string name, int num, int nodeID, int pwm, int pwmMode, int pwmRange, int pwmCLock);
	void deletePin (int num, int nodeID);

	// Node and group operations
	void addGroup (std::string name, int groupID, int mode);
	void addNode (std::string name, int nodeID, std::string address);
	void deleteGroup (int groupID);
	void deleteNode (int nodeID);

private:
	sql::ResultSet* query (std::string query);

	std::string username, password, dbname, server;

	sql::Driver *driver;

};


#endif //COLUMN_MYSQL_HPP
