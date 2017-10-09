#ifndef COLUMN_OBJECTHANDLER_HPP
#define COLUMN_OBJECTHANDLER_HPP

#include <vector>
#include <string>
#include "node.hpp"
#include "group.hpp"
#include "settings.hpp"
#include "server.hpp"

class objectHandler
{
public:
	objectHandler();

	int createNode(std::string name, std::string address);
	int createGroup(std::string name, int mode);

	void delNode(int id);
	void delGroup(int id);

	unsigned long numberOfNodes();
	unsigned long numberOfGroups();

	int save_settings(settings *settings);
	int load_settings(settings *settings);

	std::map<int, node> getNodes();
	std::map<int, group> getGroups();

	node* getNode(int id);
	group* getGroup(int id);

	// These are seperate because of usage in the connection class
	unsigned int getFreeGID();
	unsigned int getFreeNID();

	int getlId();
	bool getMaster();
private:
	// maps of nodes and groups
	std::map<int, node>  	nMap;
	std::map<int, group> 	gMap;

	// is this the master bool, and local nodeID
	bool master;
	int lID;
};

#endif //COLUMN_OBJECTHANDLER_HPP
