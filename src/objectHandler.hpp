#ifndef COLUMN_OBJECTHANDLER_HPP
#define COLUMN_OBJECTHANDLER_HPP

#include <vector>
#include <string>
#include <utility>
#include <boost/any.hpp>
#include "node.hpp"
#include "group.hpp"
#include "trigger.hpp"

/*!
 * \brief Class that stores the nodes, groups and triggers
 * \class objectHandler
 */
class objectHandler
{
public:
	objectHandler();

	/*!
	 * \brief Sets global stop variable
	 * \param stop  Pointer to global stop variable
	 */
	void init(volatile int* stop);

	/*!
	 * \brief Creates and initialises a node
	 * \param name
	 * \param address, the IP address of the node
	 * \return nodeID
	 */
	int createNode(std::string name, std::string address);
	/*!
	 * \brief Creates and initialises a group
	 * \param name
	 * \param mode, either INPUT or OUTPUT
	 * \return groupID
	 */
	int createGroup(std::string name, int mode);
	/*!
	 * \brief Creates and initialises a trigger
	 * \param name
	 * \return triggerID
	 */
	int createTrigger(std::string name);

	/*!
	 * \brief Deletes a node
	 * \param id
	 */
	void delNode(int id);
	/*!
	 * \brief Deletes a group
	 * \param id
	 */
	void delGroup(int id);
	/*!
	 * \brief Deletes a trigger
	 * \param id
	 */
	void delTrigger(int id);

	/*! Returns amount of nodes in this handler */
	unsigned long numNodes();
	/*! Returns amount of groups in this handler */
	unsigned long numGroups();
	/*! Returns amount of triggers in this handler */
	unsigned long numTriggers();

	/*! Returns map with all nodes */
	std::map<int, node> getNodes();
	/*! Returns map with all groups */
	std::map<int, group> getGroups();
	/*! Returns map with all triggers */
	std::map<int, trigger> getTriggers();

	/*! Returns pointer to node by id or name*/
	node* getNode(unsigned int id);
	node* getNode(std::string name);
	/*! Returns pointer to group by id */
	group* getGroup(unsigned int id);
	/*! Returns pointer to trigger by id */
	trigger* getTrigger(unsigned int id);

	// These are seperate because of usage in the connection class
	/*! Returns first available group id */
	unsigned int getFreeGID();
	/*! Returns first available node id */
	unsigned int getFreeNID();
	/*! Returns first available trigger id */
	unsigned int getFreeTID();

	/*! Returns local node id */
	int getlId();
	/*! Returns whether this node is the master or not */
	bool getMaster();
private:
	friend class boost::serialization::access;
	friend class settings;
	friend class connection;

	volatile int *stop;

	template <typename T>
	unsigned int getFreeID(std::map<int, T> *map);

	// maps of nodes and groups
	std::map<int, node>  	nMap;
	std::map<int, group> 	gMap;
	std::map<int, trigger>  tMap;

	// is this the master bool, and local nodeID
	bool master = true;
	int lID;

	template<class Archive>
	void serialize(Archive & ar, unsigned int version)
	{
		ar & boost::serialization::make_nvp("master", master)
		   & boost::serialization::make_nvp("lID", lID)
		   & boost::serialization::make_nvp("nMap", nMap)
		   & boost::serialization::make_nvp("gMap", gMap)
		   & boost::serialization::make_nvp("tMap", tMap);
	}
};

#endif //COLUMN_OBJECTHANDLER_HPP
