#ifndef COLUMN_TRIGGER_HPP
#define COLUMN_TRIGGER_HPP

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <thread>
#include <chrono>
#include <map>
#include <pthread.h>
#include <vector>
#include "globals.hpp"
#include "node.hpp"
#include "group.hpp"
#include "pin.cpp"

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
	void init(objectHandler *handler);
	/*!
	 * \brief Adds a pin by wiringPi numbering scheme ID, and the node ID the pin belongs to
	 * \param wpi wiringPi index
	 * \param nID node number
	 */
	void addPin(int wpi, unsigned int nID);
	/*!
	 * \brief Adds a group by group ID
	 * \param gID group ID
	 */
	void addGroup(unsigned int gID);

	/*!
	 * \brief Sets pin condition by position in the internal vector to one of \link #conds \endlink condtions
	 * \param pos Position in internal map
	 * \param cond Condition, must be one of \link #conds \endlink 's values
	 */
	void setPCond(unsigned int pos, short cond);
	/*!
	 * \brief Sets pin condition by position in the internal vector to one of \link conds \endlink condtions
	 * \param pos Position in internal map
	 * \param cond Condition, must be one of {@link conds#OR} 's values
	 */
	void setGCond(unsigned int pos, short cond);

	/*!
	 * \brief Deletes a pin by wpi and node ID
	 * \param wpi wiringPi index
	 * \param nID node number
	 */
	void delPin(int wpi, unsigned int nID);
	/*!
	 * \brief Deletes a group by ID
	 * \param gID group ID
	 */
	void delGroup(unsigned int gID);

	/*! \brief Turns the trigger on or of */
	void toggleDetect();
	/*! \brief Returns whether the trigger is currently running */
	bool getDetectState();

	std::thread* getThread();

	std::string name;
private:
	void detect();
	int timeout = 50;

	bool detection = true;
	objectHandler *handler;
	std::thread *thread;

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
