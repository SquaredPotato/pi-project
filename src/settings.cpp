#include "settings.hpp"

settings::settings(std::string nodePath)
{   this->nPath = std::move(nodePath);  }

int settings::load(objectHandler handler, std::atomic_bool *stop)
{
//	namespace fs = boost::filesystem;
	namespace fs = std::filesystem;

	try
	{
		if (fs::exists(fs::path(this->nPath)))
		{
			std::ifstream is(this->nPath.c_str());

			// De-activate any active detect threads
			for (std::pair<const int, trigger> &a : handler.tMap)
			{
				if (a.second.getDetectState())
				{
					a.second.toggleDetect();
				}
			}

			// Clear maps to prevent segfault
			handler.tMap.clear();
			handler.gMap.clear();
			handler.nMap.clear();

			std::cout << "Settings.cpp: " << handler.getTriggers().size();

			boost::archive::xml_iarchive xiarch(is);

			// Load settings from file
			xiarch >> boost::serialization::make_nvp("handler", handler);

			std::cout << "Settings.cpp: " << handler.getTriggers().size();

			handler.init(stop);

			std::cout << "Settings.cpp: " << handler.getTriggers().size();

			// Re-initialize nodes and corresponding pins
			std::cout << "loading nodes" << std::endl;
			for (unsigned int i = 0; i < handler.getFreeNID(); i ++)
			{   handler.getNode(i)->reInit();  }

			// Re-init groups
			std::cout << "loading groups" << std::endl;
			for (unsigned int i = 0; i < handler.getFreeGID(); i ++)
			{   handler.getGroup(i)->setHandler(&handler);  }

			// Re-enable triggers
			std::cout << "loading triggers" << std::endl;
			for (unsigned int i = 0; i < handler.getFreeTID(); i ++)
			{   handler.getTrigger(i)->init(&handler);    }

			std::cout << "loaded settings" << std::endl;
		}
		else
		{   std::cout << "Error: File does not exist" << std::endl; }
	}
	catch (boost::archive::archive_exception &e)
	{
		std::cerr << "Error: loading settings failed: " << e.what() << std::endl;
		return 0;
	}

	return 1;
}

int settings::save(objectHandler handler)
{
//		namespace fs = boost::filesystem;
	namespace fs = std::filesystem;

	// make one backup of files
	if (fs::exists (fs::path(this->nPath)))
	{
		try
		{
			if (fs::exists(this->onPath))
			{   fs::remove(fs::path(this->onPath)); }

			fs::rename(fs::path(this->nPath), fs::path(this->onPath));
		}
		catch (fs::filesystem_error &e)
		{
			std::cerr << "An error occurred while trying rename old config files: " << e.what() << std::endl;
			return 0;
		}
	}

	try
	{
		std::cout << "creating output filestreams..." << std::endl;
		// write maps to files
		std::ofstream nodes(this->nPath);
//		fs::ofstream nodes(this->nPath);
		boost::archive::xml_oarchive noarch(nodes);

		noarch << boost::serialization::make_nvp("handler", handler);
		// This is apparently necessary because boost doesn't correctly close its xml
		nodes << "</boost_serialization>\n";

		nodes.close();
	}
	catch (boost::archive::archive_exception &e)
	{
		std::cerr << "An error occurred while trying to save settings: " << e.what() << std::endl;
		return 0;
	}
	return 1;
}