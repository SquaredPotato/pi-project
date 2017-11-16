#ifndef COLUMN_SETTINGS_HPP
#define COLUMN_SETTINGS_HPP

#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/string.hpp>

#include "node.hpp"
#include "trigger.hpp"

class group;
class objectHandler;

class settings {
public:
	settings(std::string nodePath);

	/*! Loads setting into given objects */
	int load(std::map<int, node> *nMap, std::map<int, group> *gMap, std::map<int, trigger> *tMap, objectHandler *handler);
	/*! Saves settings from given objects */
	int save(std::map<int, node> nMap, std::map<int, group> gMap, std::map<int, trigger> tMap, objectHandler handler);

private:
	std::string nPath, onPath = "config/old_nodes.xml";
};

#endif //COLUMN_SETTINGS_HPP