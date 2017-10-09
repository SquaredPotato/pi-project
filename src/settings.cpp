#include "settings.hpp"

#include <utility>
#include "group.hpp"

settings::settings(std::string groupPath, std::string nodePath)
{
	this->nPath = std::move(nodePath);
	this->gPath = std::move(groupPath);
}

int settings::load(std::map<int, node> *nMap, std::map<int, group> *gMap, bool *master, int *lID)
{
	namespace fs = boost::filesystem;
	if (fs::exists(fs::path(this->nPath)) && fs::exists(fs::path(this->gPath)))
	{
		std::ifstream nodes(this->nPath), groups(this->gPath);
		boost::archive::text_iarchive niarch(nodes), giarch(groups);

		niarch >> *nMap >> *master >> *lID;
		giarch >> *gMap;

		nodes.close();
		groups.close();
		return 1;
	}
	return 0;
}

int settings::save(std::map<int, node> nMap, std::map<int, group> gMap, bool master, int lID) {
	namespace fs = boost::filesystem;

	// make one backup of files
	if (fs::exists (fs::path(this->gPath)) && fs::exists (fs::path(this->nPath)))
	{
		try
		{
			if (fs::exists(this->onPath) && fs::exists(this->ogPath))
			{
				fs::remove(fs::path(this->onPath));
				fs::remove(fs::path(this->ogPath));
			}

			fs::rename(fs::path(this->gPath), fs::path(this->ogPath));
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
		// write maps to file
		std::ofstream nodes(this->nPath);
		std::ofstream groups(this->gPath);

		std::cout << "creating text output archives..." << std::endl;

		boost::archive::text_oarchive noarch(nodes), goarch(groups);

		std::cout << "writing to files..." << std::endl;

		noarch << nMap << master << lID;
		goarch << gMap;

		std::cout << "closing files, saving successful" << std::endl;

	} catch (boost::archive::archive_exception &e)
	{
		std::cerr << "An error occurred while trying to save settings: " << e.what() << std::endl;
		return 0;
	}

	return 1;
}