#ifndef COLUMN_SETTINGS_HPP
#define COLUMN_SETTINGS_HPP

#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/string.hpp>

#include "node.hpp"

class group;

class settings {
public:
	settings(std::string groupPath, std::string nodePath);

	int load(std::map<int, node> *nMap, std::map<int, group> *gMap, bool *master, int *lID);
	int save(std::map<int, node> nMap, std::map<int, group> gMap, bool master, int lID);

private:
	std::string gPath, nPath, ogPath = "/home/pi/projects/pi-project/config/old_groups.cfg", onPath = "/home/pi/projects/pi-project/config/old_nodes.cfg";
};


#endif //COLUMN_SETTINGS_HPP
