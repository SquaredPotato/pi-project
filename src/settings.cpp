#include "settings.hpp"

#include <utility>


settings::settings(std::string nodePath)
{
	this->nPath = std::move(nodePath);
}

int settings::load(objectHandler *handler)
{
	namespace fs = boost::filesystem;

	try
	{
		if (fs::exists(fs::path(this->nPath)))
		{
			std::ifstream nodes(this->nPath);
			boost::archive::xml_iarchive niarch(nodes);

			std::cout << "loading settings..." << std::endl;

			niarch >> boost::serialization::make_nvp("handler", *handler);

			std::cout << "loaded settings" << std::endl;
		}
		else
		{
			std::cout << "Error: File does not exist" << std::endl;
		}
	} catch (boost::archive::archive_exception &e)
	{
		std::cerr << "Error: loading settings failed: " << e.what() << std::endl;
		return 0;
	}

	return 1;
}

int settings::save(objectHandler handler)
{
	namespace fs = boost::filesystem;

	// make one backup of files
	if (fs::exists (fs::path(this->nPath)))
	{
		try
		{
			if (fs::exists(this->onPath))
			{
				fs::remove(fs::path(this->onPath));
			}

			fs::rename(fs::path(this->nPath), fs::path(this->onPath));

		} catch (fs::filesystem_error &e)
		{
			std::cerr << "An error occurred while trying rename old config files: " << e.what() << std::endl;
			return 0;
		}
	}

	try
	{
		std::cout << "creating output filestreams..." << std::endl;
		// write maps to fileds
		std::ofstream nodes(this->nPath);

		std::cout << "creating xml output archive..." << std::endl;

		boost::archive::xml_oarchive noarch(nodes);

		std::cout << "writing to files..." << std::endl;

		noarch << boost::serialization::make_nvp("handler", handler);

		// This is apparently necessary because boost doesn't correctly close itself
		nodes << "</boost_serialization>\n";

		std::cout << "closing files, saving successful" << std::endl;
	} catch (boost::archive::archive_exception &e)
	{
		std::cerr << "An error occurred while trying to save settings: " << e.what() << std::endl;
		return 0;
	}
	return 1;
}