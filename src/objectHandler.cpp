#include "objectHandler.hpp"

objectHandler::objectHandler()
=default;

void objectHandler::init(volatile int *stop)
{
	this->stop = stop;
	this->lID = this->getFreeNID();
}

int objectHandler::createNode (std::string name, std::string address)
{
	int i = this->getFreeID(&this->nMap);

	this->nMap[i] = node();
	this->nMap[i].init(std::move(name), i, std::move(address));

	return i;
}

int objectHandler::createGroup (std::string name, int mode)
{
	int i = this->getFreeID(&this->gMap);

	this->gMap.insert(std::make_pair(i, group()));
	this->gMap[i].init(i, std::move(name), mode, this);

	return i;
}

int objectHandler::createTrigger(std::string name)
{
	int i = this->getFreeID(&this->tMap);

	this->tMap.insert(std::make_pair(i, trigger()));

	this->tMap[i].init(this, this->stop);

	return i;
}

void objectHandler::delNode(int id)
{   this->nMap.erase(id);   }

void objectHandler::delGroup(int id)
{   this->gMap.erase(id);   }

void objectHandler::delTrigger(int id)
{   this->tMap.erase(id);   }

node* objectHandler::getNode(unsigned int id)
{   return &this->nMap[id]; }

node* objectHandler::getNode(std::string name)
{
	for (auto & i : this->nMap)
	{
		if (i.second.name == name)
		{   return &i.second; }
	}

	return nullptr;
}

group* objectHandler::getGroup(unsigned int id)
{   return &this->gMap[id]; }

trigger* objectHandler::getTrigger(unsigned int id)
{   return &this->tMap[id]; }

unsigned long objectHandler::numNodes()
{   return this->nMap.size();   }

unsigned long objectHandler::numGroups()
{   return this->gMap.size();   }

unsigned long objectHandler::numTriggers()
{   return this->tMap.size();   }

std::map<int, node> objectHandler::getNodes()
{   return this->nMap;  }

std::map<int, group> objectHandler::getGroups()
{   return this->gMap;  }

std::map<int, trigger> objectHandler::getTriggers()
{   return this->tMap;  }

unsigned int objectHandler::getFreeNID()
{   return this->getFreeID(&this->nMap);    }

unsigned int objectHandler::getFreeGID()
{   return this->getFreeID(&this->gMap);    }

unsigned int objectHandler::getFreeTID()
{   return this->getFreeID(&this->tMap);    }

template <typename T>
unsigned int objectHandler::getFreeID(std::map<int, T> *map)
{
	unsigned int i = 0;

	for (auto it = map->cbegin(), end = map->cend();
			it != end && i == it->first; it ++, ++ i)
	{ }

	return i;
}

int objectHandler::getlId()
{   return this->lID;   }

bool objectHandler::getMaster()
{   return this->master;    }