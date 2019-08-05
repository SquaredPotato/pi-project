#include "trigger.hpp"
#include "objectHandler.hpp"

trigger::trigger()
{   }

void trigger::init(objectHandler *handler, volatile int *stop)
{
	this->stop = stop;
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

	bool cond;
	bool pcond;
	bool gcond;

	// Run loop while the process is running and this trigger is active
	while (!*this->stop && this->detection)
	{
		cond = true;
		pcond = true;
		gcond = true;

		unsigned long numPins = this->ipins.size();
		unsigned long numGroups = this->igroups.size();

		// Evaluate pins
		if (numPins > 0)
		{   cond = this->evalPins(this->ipins, cond);   }

		// Evaluate groups
		if (numGroups > 0)
		{
			if (numGroups > 1)
			{
				// Get state of group 0
				gcond = this->evalPins(this->handler->getGroup(this->igroups[0].id)->getPins(), gcond);

				// Get state of other groups
				for (unsigned int i = 1; i < numGroups; i++)
				{
					pcond = this->evalPins(this->handler->getGroup(this->igroups[i].id)->getPins(), pcond);

					// Check the group's condition
					gcond = this->switchCond(this->igroups[i].condition, gcond, pcond);
				}
			}
			else // The state of the first group will be equal to that as if it wasn't even a group
			{   gcond = this->evalPins(this->handler->getGroup(this->igroups[0].id)->getPins(), gcond);    }
		}

		// Determine final state of trigger
		if (numPins >= 1 && numGroups >= 1)         // When trigger holds both pins and groups
		{   cond = cond && gcond;   }
		else if (numPins >= 1 && numGroups == 0)    // When trigger only holds pins (cond already correct)
		{	;   }
		else if (numPins == 0 && numGroups >= 1)    // When trigger only holds groups
		{   cond = gcond;   }
		else                                        // When trigger is empty
		{   cond = false;   }

		// When input (set at the default of the previous two switches) or the outcome of the logic is true
		if (cond)
		{   this->setOState(HIGH);  }
		else
		{   this->setOState(LOW);   }

		std::this_thread::sleep_for(timeout_ns);
	}
}

void trigger::addPin(int wpi, unsigned int nID)
{
	// get gpin mode, then save gpin to correct vector
	if (this->handler->getNode(nID)->get_mode(wpi) == OUTPUT)
	{
		this->opins.emplace_back(pin());
		this->opins.back().wpi = wpi;
		this->opins.back().id = nID;
	}
	else
	{
		this->ipins.emplace_back(pin());
		this->ipins.back().wpi = wpi;
		this->ipins.back().id = nID;
	}
}

void trigger::addGroup(unsigned int gID)
{
	if (this->handler->getGroup(gID)->getMode() == OUTPUT)
	{
		this->ogroups.emplace_back(tgroup());
		this->ogroups.back().id = gID;
	}
	else
	{
		this->igroups.emplace_back(tgroup());
		this->igroups.back().id = gID;
	}
}

void trigger::setPCond(unsigned int pos, short cond)
{   this->ipins.at(pos).condition = cond;   }

void trigger::setGCond(unsigned int pos, short cond)
{   this->igroups.at(pos).condition = cond; }

void trigger::delPin(int wpi, unsigned int nID)
{
	// TODO: Test this bit
	// Get appropriate vector for pin (in/output vector)
	std::vector<pin>* tmp = this->handler->getNode(nID)->get_mode(wpi) == OUTPUT ? &this->opins : &this->ipins;

	// Delete entry from vector
	for (unsigned int i = 0; i < tmp->size(); i ++)
	{
		if (tmp->at(i).id == nID && tmp->at(i).wpi == wpi)
		{
			tmp->erase(tmp->begin() + i);
			tmp->shrink_to_fit();
		}
	}

//	// Get mode of gpin so that we only search in the correct vector
//	if (this->handler->getNode(nID)->get_mode(wpi) == OUTPUT)
//	{
//		for (unsigned int i = 0; i < this->opins.size(); i ++)
//		{
//			if (this->opins.at(i).id == nID && this->opins.at(i).wpi == wpi)
//			{
//				this->opins.erase(this->opins.begin() + i);
//				this->opins.shrink_to_fit();
//			}
//		}
//	}
//	else
//	{
//		for (unsigned int i = 0; i < this->ipins.size(); i ++)
//		{
//			if (this->ipins.at(i).id == nID && this->ipins.at(i).wpi == wpi)
//			{
//				this->ipins.erase(this->ipins.begin() + i);
//				this->ipins.shrink_to_fit();
//			}
//		}
//	}
}

void trigger::delGroup(unsigned int gID)
{
	// TODO: Test this bit
	// Get appropriate vector for group (in/output vector)
	std::vector<tgroup>* tmp = this->handler->getGroup(gID)->getMode() == OUTPUT ? &this->ogroups : &this->igroups;

	// Delete entry from vector
	for (unsigned int i = 0; i < tmp->size(); i ++)
	{
		if (tmp->at(i).id == gID)
		{
			tmp->erase(tmp->begin() + i);
			tmp->shrink_to_fit();
		}
	}

//	if (this->handler->getGroup(id)->getMode() == OUTPUT)
//	{
//		for (unsigned int i = 0; i < this->ogroups.size(); i ++)
//		{
//			if (this->ogroups.at(i).id == id)
//			{
//				this->ogroups.erase(this->ogroups.begin() + i);
//				this->ogroups.shrink_to_fit();
//			}
//		}
//	}
//	else
//	{
//		for (unsigned int i = 0; i < this->igroups.size(); i ++)
//		{
//			if (this->igroups.at(i).id == id)
//			{
//				this->igroups.erase(this->igroups.begin() + i);
//				this->igroups.shrink_to_fit();
//			}
//		}
//	}
}

void trigger::toggleDetect()
{
	if (this->detection)
	{ this->detection = false;
		std::cout << "Detection disabled" << std::endl;
	}

	if (!this->detection)
	{
		std::thread detect_(&trigger::detect, this);
		this->thread->detach();
		this->thread = &detect_;
		this->detection = true;
		std::cout << "Detection re-enabled" << std::endl;
	}
}

bool trigger::getDetectState()
{   return this->detection; }

bool trigger::evalPins(std::vector<pin> pins, bool cond)
{
	unsigned long numPins = pins.size();

	if (numPins > 1)
	{
		cond = !this->handler->getNode(pins[0].id)->get_digital_input_state(pins[0].wpi);
		pin* tmp;

		for (unsigned int j = 0; j < numPins; j++)
		{
			tmp = &this->ipins[j];
			cond = this->switchCond(pins[j].condition, cond,
			                        !this->handler->getNode(tmp->id)->get_digital_input_state(tmp->wpi));
		}
	}
	else if (numPins == 1)
	{   cond = this->handler->getNode(pins[0].id)->get_digital_input_state(pins[0].wpi) != 0;   }

	return cond;
}

bool trigger::switchCond(short conditional, bool pcond, bool state)
{
	switch (conditional)
	{
		case AND:
		{
			pcond = (state && pcond);
			break;
		}
		case NAND:
		{
			pcond = (state == 0 || !pcond);
			break;
		}
		case OR:
		{
			pcond = (state || pcond);
			break;
		}
		case NOR:
		{
			pcond = !(state || pcond);
			break;
		}
		case XOR:
		{
			pcond = (state != pcond);
			break;
		}
		case XNOR:
		{
			pcond = ((state != 0) == pcond);
			break;
		}
		default:
		{   break;  }
	}

	return pcond;
}

void trigger::setOState(int newState)
{
	for (pin opin : this->opins)
	{   this->handler->getNode(opin.id)->set_output_state(opin.wpi, newState);  }

	for (tgroup ogroup : this->ogroups)
	{
		std::vector<pin> gpin(this->handler->getGroup(ogroup.id)->getPins());
		for (pin opin : gpin)
		{   this->handler->getNode(opin.id)->set_output_state(opin.wpi, newState);  }
	}
}

std::thread* trigger::getThread()
{   return this->thread;    }