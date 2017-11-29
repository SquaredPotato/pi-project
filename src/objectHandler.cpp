#include "objectHandler.hpp"

#include <utility>

objectHandler::objectHandler()
{
	;
}

void objectHandler::init(volatile int *stop)
{
	this->stop = stop;
	this->lID = this->getFreeNID();
}

int objectHandler::createNode (std::string name, std::string address)
{
	// Find lowest available key
	int i = this->getFreeID(&this->nMap);

	this->nMap[i] = node();
	this->nMap[i].init(std::move(name), i, std::move(address));

	return i;
}

int objectHandler::createGroup (std::string name, int mode)
{
	// Find lowest available key
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
{
//	if (auto it = this->nMap.find(id) != this->nMap.end())
//		this->nMap.erase(it);
	this->nMap.erase(id);
}

void objectHandler::delGroup(int id)
{
//	if (auto it = this->gMap.find(id) != this->gMap.end())
//		this->gMap.erase(it);
	this->gMap.erase(id);
}

void objectHandler::delTrigger(int id)
{
//	if (auto it = this->tMap.find(id) != this->tMap.end())
//		this->tMap.erase(it);
	this->tMap.erase(id);
}

node* objectHandler::getNode(unsigned int id)
{
	return &this->nMap[id];
}

node* objectHandler::getNode(std::string name)
{
	for (unsigned long i = 0; i < this->nMap.size(); i ++)
		if (this->nMap[i].name == name)
			return &this->nMap.at(i);

	return 0;
}

group* objectHandler::getGroup(unsigned int id)
{
	return &this->gMap[id];
}

trigger* objectHandler::getTrigger(unsigned int id)
{
	return &this->tMap[id];
}

unsigned long objectHandler::numberOfNodes()
{
	return this->nMap.size();
}

unsigned long objectHandler::numberOfGroups()
{
	return this->gMap.size();
}

unsigned long objectHandler::numberOfTriggers()
{
	return this->tMap.size();
}

std::map<int, node> objectHandler::getNodes()
{
	return this->nMap;
}

std::map<int, group> objectHandler::getGroups()
{
	return this->gMap;
}

std::map<int, trigger> objectHandler::getTriggers()
{
	return this->tMap;
}

template <typename T>
int objectHandler::getFreeID(std::map<int, T>* map)
{
	int i = 0;

	for (auto it = map->cbegin(), end = map->cend();
			it != end && i == it->first; it ++, ++ i)
	{ }

	return i;
}

int objectHandler::getFreeNID()
{
	return this->getFreeID(&this->nMap);
}

int objectHandler::getFreeGID()
{
	return this->getFreeID(&this->gMap);
}

int objectHandler::getFreeTID()
{
	return this->getFreeID(&this->tMap);
}

int objectHandler::getlId()
{
	return this->lID;
}

bool objectHandler::getMaster()
{
	return this->master;
}