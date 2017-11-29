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
#include <boost/serialization/binary_object.hpp>

#include "objectHandler.hpp"

class group;
class objectHandler;

class settings
{
public:
	settings(std::string nodePath);

	/*! Loads setting into given objects */
	int load(objectHandler *handler);
	/*! Saves settings from given objects */
	int save(objectHandler handler);

private:
	std::string nPath, onPath = "config/old_nodes.xml";
};

#endif //COLUMN_SETTINGS_HPP