#include "objectHandler.hpp"

#include <utility>

objectHandler::objectHandler ()
= default;

int objectHandler::createNode (std::string name, std::string address)
{
	// Find lowest available key
	unsigned int i = this->getFreeNID();

	this->nMap[i] = node();
	this->nMap[i].init(std::move(name), i, std::move(address));

	return i;
}

int objectHandler::createGroup (std::string name, int mode)
{
	// Find lowest available key
	unsigned int i = this->getFreeGID();

	this->gMap.insert(std::make_pair(i, group()));
	this->gMap[i].init(i, std::move(name), mode);

	return i;
}

void objectHandler::delNode(int id)
{
	if (auto it = this->nMap.find(id) != this->nMap.end())
		this->nMap.erase(it);
}

void objectHandler::delGroup(int id)
{
	if (auto it = this->gMap.find(id) != this->gMap.end())
		this->gMap.erase(it);
}

node* objectHandler::getNode(int id)
{
	return &this->nMap[id];
}

group* objectHandler::getGroup(int id)
{
	return &this->gMap[id];
}

unsigned long objectHandler::numberOfNodes()
{
	return this->nMap.size();
}

unsigned long objectHandler::numberOfGroups()
{
	return this->gMap.size();
}

int objectHandler::save_settings(settings *set)
{
	return set->save(this->nMap, this->gMap, this->master, this->lID);
}

int objectHandler::load_settings(settings *set)
{
	return set->load(&this->nMap, &this->gMap, &this->master, &this->lID);
}

std::map<int, node> objectHandler::getNodes()
{
	return this->nMap;
}

std::map<int, group> objectHandler::getGroups()
{
	return this->gMap;
}

unsigned int objectHandler::getFreeNID()
{
	// Find lowest available key
	unsigned int i = 0;

	for (auto it = this->nMap.cbegin(), end = this->nMap.cend();
	     it != end && i == it->first; ++it, ++i)
	{ }

	return i;
}

unsigned int objectHandler::getFreeGID()
{
	unsigned int i = 0;

	for (auto it = this->gMap.cbegin(), end = this->gMap.cend();
	     it != end && i == it->first; ++it, ++i)
	{ }

	return i;
}

int objectHandler::getlId()
{
	return this->lID;
}

bool objectHandler::getMaster()
{
	return this->master;
}