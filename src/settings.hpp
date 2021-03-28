#ifndef COLUMN_SETTINGS_HPP
#define COLUMN_SETTINGS_HPP

#include <iostream>
#include <fstream>
//#include <experimental/filesystem>
#include <filesystem>
#include "objectHandler.hpp"

class group;
class objectHandler;

class settings
{
public:
	explicit settings(std::string nodePath);

	/*! Loads setting into given objects */
	int load(objectHandler handler, std::atomic_bool *stop);
	/*! Saves settings from given objects */
	int save(objectHandler handler);

private:
	// paths to current and old settings
	std::string nPath, onPath = "config/old_config.xml";
};

#endif //COLUMN_SETTINGS_HPP