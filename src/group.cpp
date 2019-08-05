#include "group.hpp"

#include <utility>
#include "objectHandler.hpp"

group::group ()
=default;

void group::init(int id, std::string name, int mode, objectHandler *handler)
{
	this->id = id;
	this->mode = mode;
	this->name = std::move(name);
	this->state = 0;
	this->handler = handler;
}

void group::setHandler(objectHandler *handler)
{   this->handler = handler;    }

int group::addPin(int wpi, unsigned int pnodeID)
{
	if (this->handler->getNode (pnodeID)->get_mode (wpi) == this->mode)
	{
		this->pins.emplace_back(pin());
		this->pins.back().id = pnodeID;
		this->pins.back().wpi = wpi;

		return 1;
	}

	// If adding gpin was unsuccessful
	std::cerr << "Tried to add gpin " << wpi << " from node " << pnodeID << " with the wrong mode ("
	          << this->handler->getNode (pnodeID)->get_mode (wpi) << " instead of " << this->mode << ")" << std::endl;

	return 0;
}

int group::removePin(int wpi, int nodeID, unsigned int pos)
{
	// Select selection method (by gpin data or position in vector)
	if (wpi != -1 && nodeID != -1)
	{
		// Search for correct entry in vector
		for (unsigned int i = 0; i < this->pins.size(); i ++)
		{
			if (this->pins[i].wpi == wpi && this->pins[i].id == (unsigned int) nodeID)
			{
				std::cout << "gpin" << i << " removed from group " << this->id << std::endl;
				this->pins.erase(this->pins.begin() + i);
				this->pins.shrink_to_fit();
				return 1;
			}
		}
	}
	else if (pos != NULL)
	{
		this->pins.erase(this->pins.begin() + pos);
		std::cout << "gpin" << pos << " removed from group " << this->id << std::endl;
		return 1;
	}

	std::cout << "Wrong arguments used when removing gpin from group " << this->id << std::endl;
	return 0;
}

int group::toggle()
{
	if (this->mode == OUTPUT)
	{
		if (this->state == 1)
		{   this->state = 0;    }
		else
		{   this->state = 1;    }

		for (auto &pin : this->pins)
		{   this->handler->getNode(pin.id)->set_output_state(pin.wpi, this->state); }

		return this->state;
	}
	else
	{   std::cout << "Tried to toggle group which is in INPUT mode" << std::endl;   }

	return -1;
}

void group::newState(int newState)
{
	this->state = newState;

	for (unsigned int i = 0; i < this->pins.size(); i ++)
	{   this->handler->getNode(pins.at(i).id)->set_output_state(this->pins.at(i).wpi, newState);    }
}

std::vector<pin> group::getPins()
{   return this->pins;  }

int group::getMode()
{   return this->mode;  }