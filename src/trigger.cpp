#include "trigger.hpp"
#include "objectHandler.hpp"

trigger::trigger()
{
}

void trigger::init(objectHandler *handler, volatile int *stop)
{
	this->stop = stop;
	this->handler = handler;

	boost::thread detect_(boost::bind(&trigger::detect, this));
	this->thread = &detect_;
}

void trigger::detect()
{
	std::cout << "detect() loop started" << std::endl;

	bool cond;
	bool pcond;
	bool gcond;

	// Run loop while we are still running and this trigger is active
	while (!*this->stop && this->detection)
	{
		cond = true;
		pcond = true;
		gcond = true;

		unsigned long numPins = this->ipins.size();
		unsigned long numGroups = this->igroups.size();

		// Evaluate pins
		if (numPins > 0)
			cond = this->evalPins(this->ipins, cond);

		// Evaluate groups
		if (numGroups > 0)
		{
			if (numGroups > 1)
			{
				// Get state of group 0
				gcond = this->evalPins(this->handler->getGroup(this->igroups[0].gID)->getPins(), gcond);

				// Get state of other groups
				for (unsigned int i = 1; i < numGroups; i++)
				{
					pcond = this->evalPins(this->handler->getGroup(this->igroups[i].gID)->getPins(), pcond);

					// Check the group's condition
					gcond = this->switchCond(this->igroups[i].condition, gcond, pcond);
				}
			}
			else // The state of the first group will be equal to that as if it wasn't even a group
				gcond = this->evalPins(this->handler->getGroup(this->igroups[0].gID)->getPins(), gcond);
		}

		if (numPins >= 1 && numGroups >= 1)
			cond = cond && gcond;
		else if (numPins >= 1 && numGroups == 0)
			;
		else if (numPins == 0 && numGroups >= 1)
			cond = gcond;
		else
			cond = false;

		// When input (set at the default of the previous two switches) or the outcome of the logic is true
		if (cond)
			this->setOState(HIGH);
		else
			this->setOState(LOW);

		// Sleep(), but different
		boost::this_thread::sleep_for(boost::chrono::milliseconds(this->timeout));
	}
}

void trigger::addPin(int wpi, unsigned int nID)
{
	// get gpin mode, then save gpin to correct vector
	if (this->handler->getNode(nID)->get_mode(wpi) == OUTPUT)
	{
		this->opins.emplace_back(pin());
		this->opins.back().wpi = wpi;
		this->opins.back().nodeID = nID;
	}
	else
	{
		this->ipins.emplace_back(pin());
		this->ipins.back().wpi = wpi;
		this->ipins.back().nodeID = nID;
	}
}

void trigger::addGroup(unsigned int gID)
{
	if (this->handler->getGroup(gID)->getMode() == OUTPUT)
	{

		this->ogroups.emplace_back(tgroup());
		this->ogroups.back().gID = gID;
	}
	else
	{
		this->igroups.emplace_back(tgroup());
		this->igroups.back().gID = gID;
	}
}

void trigger::setPCond(unsigned int pos, short cond)
{
	this->ipins.at(pos).condition = cond;
}

void trigger::setGCond(unsigned int pos, short cond)
{
	this->igroups.at(pos).condition = cond;
}

void trigger::delPin(int wpi, unsigned int nID)
{
	// Get mode of gpin so that we only search in the correct vector
	if (this->handler->getNode(nID)->get_mode(wpi) == OUTPUT)
	{
		for (unsigned int i = 0; i < this->opins.size(); i ++)
		{
			if (this->opins.at(i).nodeID == nID && this->opins.at(i).wpi == wpi)
			{
				this->opins.erase(this->opins.begin() + i);
				this->opins.shrink_to_fit();
			}
		}
	}
	else
	{
		for (unsigned int i = 0; i < this->ipins.size(); i ++)
		{
			if (this->ipins.at(i).nodeID == nID && this->ipins.at(i).wpi == wpi)
			{
				this->ipins.erase(this->ipins.begin() + i);
				this->ipins.shrink_to_fit();
			}
		}
	}
}

void trigger::delGroup(unsigned int gID)
{
	if (this->handler->getGroup(gID)->getMode() == OUTPUT)
	{
		for (unsigned int i = 0; i < this->ogroups.size(); i ++)
		{
			if (this->ogroups.at(i).gID == gID)
			{
				this->ogroups.erase(this->ogroups.begin() + i);
				this->ogroups.shrink_to_fit();
			}
		}
	}
	else
	{
		for (unsigned int i = 0; i < this->igroups.size(); i ++)
		{
			if (this->igroups.at(i).gID == gID)
			{
				this->igroups.erase(this->igroups.begin() + i);
				this->igroups.shrink_to_fit();
			}
		}
	}
}

void trigger::toggleDetect()
{
	if (this->detection) this->detection = false;
	if (!this->detection)
	{
		boost::thread detect(boost::bind(&trigger::detect, this));
		this->detection = true;
	}
}

bool trigger::getDetectState()
{
	return this->detection;
}

bool trigger::evalPins(std::vector<pin> pins, bool cond)
{
	unsigned long numPins = pins.size();

	if (numPins > 1)
	{
		cond = !this->handler->getNode(pins[0].nodeID)->get_digital_input_state(pins[0].wpi);

		for (unsigned int j = 0; j < numPins; j++)
		{
			cond = this->switchCond(pins[j].condition, cond, !this->handler->getNode(this->ipins[j].nodeID)->get_digital_input_state(this->ipins[j].wpi));
		}
	} else if (numPins == 1)
	{
		cond = this->handler->getNode(pins[0].nodeID)->get_digital_input_state(pins[0].wpi) != 0;
	}

	return cond;
}

bool trigger::switchCond(short conditional, bool pcond, bool state)
{
	switch (conditional)
	{
		case AND:
			pcond = (state && pcond);
			break;
		case NAND:
			pcond = (state == 0 || !pcond);
			break;
		case OR:
			pcond = (state || pcond);
			break;
		case NOR:
			pcond = !(state || pcond);
			break;
		case XOR:
			pcond = (state != pcond);
			break;
		case XNOR:
			pcond = ((state != 0) == pcond);
			break;
		default:
			break;
	}

	return pcond;
}

void trigger::setOState(int newState)
{
	for (pin opin : this->opins)
	{
		this->handler->getNode(opin.nodeID)->set_output_state(opin.wpi, newState);
	}
	for (tgroup ogroup : this->ogroups)
	{
		std::vector<pin> gpin(this->handler->getGroup(ogroup.gID)->getPins());
		for (pin opin : gpin)
		{
			this->handler->getNode(opin.nodeID)->set_output_state(opin.wpi, newState);
		}
	}
}