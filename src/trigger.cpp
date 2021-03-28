#include "trigger.hpp"
#include "objectHandler.hpp"

trigger::trigger()
{   }

void trigger::init(objectHandler *handler)
{
	this->handler = handler;

	std::thread detect_(&trigger::detect, this);
	this->thread = &detect_;
	this->thread->detach();
}

void trigger::detect()
{
	std::cout << "detect() loop started" << std::endl;
	std::chrono::nanoseconds timeout_ns (std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::milliseconds(this->timeout)));

	bool condition;
	bool pinCondition;
	bool groupCondition;

	// Run loop while the process is running and this trigger is active
	while (!STOP && this->detection)
	{
        condition = true;
        pinCondition = true;
        groupCondition = true;

		unsigned long numPins = this->inputPins.size();
		unsigned long numGroups = this->inputGroups.size();

		// Evaluate pins
		if (numPins > 0)
		{ condition = this->evaluatePins(this->inputPins, condition);   }

		// Evaluate groups
		if (numGroups > 0)
		{
			if (numGroups > 1)
			{
				// Get state of group 0
				groupCondition = this->evaluatePins(this->handler->getGroup(this->inputGroups[0].id)->getPins(), groupCondition);

				// Get state of other groups
				for (unsigned int i = 1; i < numGroups; i++)
				{
                    pinCondition = this->evaluatePins(this->handler->getGroup(this->inputGroups[i].id)->getPins(), pinCondition);

					// Check the group's condition
					groupCondition = this->switchConditions(this->inputGroups[i].condition, groupCondition, pinCondition);
				}
			}
			else // The state of the first group will be equal to that as if it wasn't even a group
			{ groupCondition = this->evaluatePins(this->handler->getGroup(this->inputGroups[0].id)->getPins(), groupCondition);    }
		}

		// Determine final state of trigger
		if (numPins >= 1 && numGroups >= 1)         // When trigger holds both pins and groups
		{ condition = condition && groupCondition;   }
		else if (numPins >= 1 && numGroups == 0)    // When trigger only holds pins (condition already correct)
		{	;   }
		else if (numPins == 0 && numGroups >= 1)    // When trigger only holds groups
		{ condition = groupCondition;   }
		else                                        // When trigger is empty
		{ condition = false;   }

		// When input (set at the default of the previous two switches) or the outcome of the logic is true
		if (condition)
		{ this->setOutputState(HIGH);  }
		else
		{ this->setOutputState(LOW);   }

		std::this_thread::sleep_for(timeout_ns);
	}

	this->detection = false;
}

void trigger::addPin(int wpi, unsigned int nID)
{
	// get gpin mode, then save gpin to correct vector
	if (this->handler->getNode(nID)->get_mode(wpi) == OUTPUT)
	{
		this->outputPins.emplace_back(pin());
		this->outputPins.back().wpi = wpi;
		this->outputPins.back().id = nID;
	}
	else
	{
		this->inputPins.emplace_back(pin());
		this->inputPins.back().wpi = wpi;
		this->inputPins.back().id = nID;
	}
}

void trigger::addGroup(unsigned int gID)
{
	if (this->handler->getGroup(gID)->getMode() == OUTPUT)
	{
		this->outputGroups.emplace_back(tgroup());
		this->outputGroups.back().id = gID;
	}
	else
	{
		this->inputGroups.emplace_back(tgroup());
		this->inputGroups.back().id = gID;
	}
}

void trigger::setPinCondition(unsigned int pos, conditions cond)
{   this->inputPins.at(pos).condition = cond;   }

void trigger::setGroupCondition(unsigned int pos, conditions cond)
{   this->inputGroups.at(pos).condition = cond; }

void trigger::deletePin(int wpi, unsigned int nID)
{
	// Get appropriate vector for pin (in/output vector) based on pin mode registered in node
	std::vector<pin>* tmp = this->handler->getNode(nID)->get_mode(wpi) == OUTPUT ? &this->outputPins : &this->inputPins;

	// Delete entry from vector
	for (unsigned int i = 0; i < tmp->size(); i ++)
	{
		if (tmp->at(i).id == nID && tmp->at(i).wpi == wpi)
		{
			try
			{
				tmp->erase(tmp->begin() + i);
				tmp->shrink_to_fit();
			} catch (std::out_of_range &e)
			{
				std::cerr << "tried to remove " << wpi << ", " << nID << ", didn't work. Out of range" << std::endl;
			}
		}
	}
}

void trigger::deleteGroup(unsigned int gID)
{
	// Get appropriate vector for group (in/output vector) based on group mode
	std::vector<tgroup>* tmp = this->handler->getGroup(gID)->getMode() == OUTPUT ? &this->outputGroups : &this->inputGroups;

	// Delete entry from vector
	for (unsigned int i = 0; i < tmp->size(); i ++)
	{
		if (tmp->at(i).id == gID)
		{
			tmp->erase(tmp->begin() + i);
			tmp->shrink_to_fit();
		}
	}
}

void trigger::toggleDetect()
{
	if (this->detection)
	{ this->detection = false;
		std::cout << "Detection disabled" << std::endl;
	}
	else
	{
		std::thread detect_(&trigger::detect, this);
		this->thread = &detect_;
		this->thread->detach();
		this->detection = true;
		std::cout << "Detection re-enabled" << std::endl;
	}
}

bool trigger::getDetectState()
{   return this->detection; }

bool trigger::evaluatePins(std::vector<pin> pins, bool cond)
{
	unsigned long numPins = pins.size();

	if (numPins > 1)
	{
		cond = !this->handler->getNode(pins[0].id)->get_digital_input_state(pins[0].wpi);
		pin* tmp;

		for (unsigned int j = 0; j < numPins; j++)
		{
			tmp = &this->inputPins[j];
			cond = this->switchConditions(pins[j].condition, cond,
                                          !this->handler->getNode(tmp->id)->get_digital_input_state(tmp->wpi));
		}
	}
	else if (numPins == 1)
	{   cond = this->handler->getNode(pins[0].id)->get_digital_input_state(pins[0].wpi) != 0;   }

	return cond;
}

bool trigger::switchConditions(short conditional, bool pinCondition, bool state)
{
	switch (conditional)
	{
		case AND:
		{
            pinCondition = (state && pinCondition);
			break;
		}
		case NAND:
		{
            pinCondition = (state == 0 || !pinCondition);
			break;
		}
		case OR:
		{
            pinCondition = (state || pinCondition);
			break;
		}
		case NOR:
		{
            pinCondition = !(state || pinCondition);
			break;
		}
		case XOR:
		{
            pinCondition = (state != pinCondition);
			break;
		}
		case XNOR:
		{
            pinCondition = ((state != 0) == pinCondition);
			break;
		}
		default:
		{   break;  }
	}

	return pinCondition;
}

void trigger::setOutputState(int newState)
{
	for (pin opin : this->outputPins)
	{   this->handler->getNode(opin.id)->set_output_state(opin.wpi, newState);  }

	for (const tgroup& ogroup : this->outputGroups)
	{
		std::vector<pin> gpin(this->handler->getGroup(ogroup.id)->getPins());
		for (pin opin : gpin)
		{   this->handler->getNode(opin.id)->set_output_state(opin.wpi, newState);  }
	}
}

std::thread* trigger::getThread()
{   return this->thread;    }