#ifndef COLUMN_TRIGGER_HPP
#define COLUMN_TRIGGER_HPP

#include <boost/thread.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <map>
#include <vector>
#include "node.hpp"
#include "group.hpp"
#include "pin.hpp"

class objectHandler;

class trigger
{
public:
	trigger();
	/*!
	 * \brief Initializes the trigger, needed for easy map adding
	 * \param handler ObjectHandler, required for getting pin information
	 * \param stop Stops the internal thread when the program stops
	 */
	void init(objectHandler *handler, volatile int *stop);
	/*! Adds a pin by wiringPi numbering scheme ID, and the node ID the pin belongs to */
	void addPin(int wpi, unsigned int nID);
	/*! Adds a group by group ID */
	void addGroup(unsigned int gID);

	/*!
	 * \brief Sets pin condition by position in the internal vector to one of \link #conds \endlink condtions
	 * \param pos Position in internal map
	 * \param cond Condition, must be one of \link #conds \endlink 's values
	 */
	void setPCond(unsigned int pos, short cond);
	/*!
	 * \brief Sets pin condition by position in the internal vector to one of \link #conds \endlink condtions
	 * \param pos Position in internal map
	 * \param cond Condition, must be one of \link #conds \endlink 's values
	 */
	void setGCond(unsigned int pos, short cond);

	/*! Deletes a pin by wpi and node ID */
	void delPin(int wpi, unsigned int nID);
	/*! Deletes a group by ID */
	void delGroup(unsigned int gID);

	/*! Turns the trigger on or of */
	void toggleDetect();
	/*! Returns whether the trigger is currently running */
	bool getDetectState();

	std::string name;
private:
	void detect();
	volatile int *stop;
	int timeout = 100;
	bool detection = true;
	objectHandler *handler;
	boost::thread *thread;

	std::vector<tgroup> igroups, ogroups;
	std::vector<pin> ipins, opins;

	bool evalPins(std::vector<pin> pins, bool cond);
	bool switchCond(short conditional, bool pcond, bool state);
	void setOState(int newState);

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, unsigned int version)
	{
		ar  & boost::serialization::make_nvp("timeout", timeout)
			& boost::serialization::make_nvp("detection", detection)
			& boost::serialization::make_nvp("igroups", igroups)
			& boost::serialization::make_nvp("ogroups", ogroups)
			& boost::serialization::make_nvp("ipins", ipins)
			& boost::serialization::make_nvp("opins", opins);
	}
};


#endif //COLUMN_TRIGGER_HPP
