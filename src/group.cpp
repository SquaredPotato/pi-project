#include "group.hpp"
#include "objectHandler.hpp"

group::group ()
{ }

void group::init(int id, std::string name, int mode)
{
	this->id = id;
	this->mode = mode;
	this->name = name;
	this->state = 0;
}

int group::addPin (int wpi, int pnodeID, objectHandler handler)
{
	if (handler.getNode (pnodeID)->get_mode (wpi) == this->mode)
	{
		this->pins.emplace_back(pin());
		this->pins.back().nodeID = pnodeID;
		this->pins.back().wpi = wpi;
		return 1;
	}

	// If adding pin was unsuccessful
	std::cerr << "Tried to add pin " << wpi << " from node " << pnodeID << " with the wrong mode (" << handler.getNode (pnodeID)->get_mode (wpi) << " instead of " << this->mode << ")" << std::endl;
	return 0;
}

int group::removePin (int wpi, int nodeID, int pos)
{
	// Select selection method (by pin data or position in vector)
	if (wpi != -1 && nodeID != -1)
	{
		// Search for correct entry in vector
		for (int i = 0; i < this->pins.size(); i ++)
		{
			if (this->pins[i].wpi == wpi && this->pins[i].nodeID == nodeID)
			{
				std::cout << "pin" << i << " removed from group " << this->id << std::endl;
				this->pins.erase(this->pins.begin() + i);
				this->pins.shrink_to_fit();
				return 1;
			}
		}
	}
	else if (pos != -1)
	{
		this->pins.erase(this->pins.begin() + pos);
		std::cout << "pin" << pos << " removed from group " << this->id << std::endl;
		return 1;
	}

	std::cout << "Wrong arguments used when removing pin from group " << this->id << std::endl;
	return 0;
}

int group::toggle(objectHandler *handler)
{
	if (this->state == 1)
	{
		this->state = 0;
	}
	else
	{
		this->state = 1;
	}

	for (auto &pin : this->pins)
		handler->getNode(pin.nodeID)->set_output_state(pin.wpi, this->state);

	return this->state;
}

void group::newState(int newState, objectHandler *handler)
{
	this->state = newState;

	for (int i = 0; i < this->pins.size(); i ++)
		handler->getNode(pins.at(i).nodeID)->set_output_state(this->pins.at(i).wpi, newState);
}

std::vector<pin> group::get_pins ()
{
	return this->pins;
}

int group::get_mode ()
{
	return this->mode;
}


std::string group::get_name ()
{
	return this->name;
}