#include <iostream>
#include "mysql.hpp"

mysql::mysql (std::string server, std::string username, std::string password, std::string dbname) {
	this->server	= server;
	this->username	= username;
	this->password	= password;
	this->dbname	= dbname;

	this->driver = get_driver_instance ();
}

sql::ResultSet* mysql::query (std::string query) {
	try {
		sql::Connection *con = this->driver->connect (this->server, this->username, this->password);
		sql::Statement *stmt;
		sql::ResultSet *res;

		con->setSchema (this->dbname);

		stmt = con->createStatement ();
		res = stmt->executeQuery (query);

		delete con;
		delete stmt;

		return res;
	} catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
}

void mysql::input (std::string name, int num, int nodeID, int edge, int upDown) {
	std::ostringstream stmt;
	stmt << "INSERT INTO `pin`(`name`, `num`, `nodeID`, `edge`, `upDown`) VALUES (" << name << ", " << num << ", " << nodeID << ", " << edge << ", " << upDown << ");";
	this->query (stmt.str ());
}

void mysql::output (std::string name, int num, int nodeID, int state) {
	std::ostringstream stmt;
	stmt << "INSERT INTO `pin`(`name`, `num`, `nodeID`, `state`) VALUES (" << name << ", " << num << ", " << nodeID << ", " << state << ");";
	this->query (stmt.str ());
}

void mysql::PWMOutput (std::string name, int num, int nodeID, int pwm, int pwmMode, int pwmRange, int pwmCLock) {
	std::ostringstream stmt;
	stmt << "INSERT INTO `pin`(`name`, `num`, `nodeID`, `pwm`, `pwmMode`, `pwmRange`, `pwmClock`) VALUES (" << name << ", " << num << ", " << nodeID << ", " << pwm << ", " << pwmMode << ", " << pwmRange << ", " << pwmCLock << ");";
	this->query (stmt.str ());
}

void mysql::deletePin (int num, int nodeID) {
	std::ostringstream stmt;
	stmt << "DELETE FROM `pin` WHERE `num` = " << num << "AND `nodeID` = " << nodeID << ";";
	this->query (stmt.str ());
}

void mysql::addGroup (std::string name, int groupID, int mode) {
	std::ostringstream stmt;
	stmt << "INSERT INTO `group`(`name`, `groupID`, `mode`) VALUES (" << name << ", " << groupID << ", " << mode << ");";
	this->query (stmt.str ());
}

void mysql::addNode (std::string name, int nodeID, std::string address) {
	std::ostringstream stmt;
	stmt << "INSERT INTO `node`(`name`, `nodeID`, `address`) VALUES (" << name << ", " << nodeID << ", " << address << ");";
	this->query (stmt.str ());
}

void mysql::deleteGroup (int groupID) {
	std::ostringstream stmt;
	stmt << "DELETE FROM `group` WHERE `groupID` = " << groupID << ";";
	this->query (stmt.str ());
}

void mysql::deleteNode (int nodeID) {
	std::ostringstream stmt;
	stmt << "DELETE FROM `node` WHERE `nodeID` = " << nodeID << ";";
	this->query (stmt.str ());
}