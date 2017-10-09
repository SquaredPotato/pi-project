#ifndef COLUMN_GROUP_HPP
#define COLUMN_GROUP_HPP

#include <array>
#include <vector>
#include <iostream>
#include <boost/serialization/access.hpp>

class objectHandler;

struct pin {
	int wpi;
	int nodeID;
public:
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & wpi & nodeID;
	}
};

class group {
public:
	group();

	void init(int id, std::string name, int mode);

	int addPin(int wpi, int pnodeID, objectHandler handler);
	int removePin(int wpi, int nodeID, int pos);

	int toggle(objectHandler *handler);
	void newState(int state, objectHandler *handler);

	std::vector<pin> get_pins();
	int get_mode();
	std::string get_name();

private:
	int id, mode, state;
	std::string name;

	std::vector<pin> pins;

	//for saving
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, unsigned int version)
	{
		ar & this->id & this->name & this->mode & this->pins & this->state;
	}
};

#endif //COLUMN_GROUP_HPP
