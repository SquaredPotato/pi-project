#ifndef COLUMN_TRIGGER_HPP
#define COLUMN_TRIGGER_HPP

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
	void setPinCondition(unsigned int pos, conditions cond);
	/*!
	 * \brief Sets pin condition by position in the internal vector to one of \link conds \endlink condtions
	 * \param pos Position in internal map
	 * \param cond Condition, must be one of {@link conds#OR} 's values
	 */
	void setGroupCondition(unsigned int pos, conditions cond);

	/*!
	 * \brief Deletes a pin by wpi and node ID
	 * \param wpi wiringPi index
	 * \param nID node number
	 */
	void deletePin(int wpi, unsigned int nID);
	/*!
	 * \brief Deletes a group by ID
	 * \param gID group ID
	 */
	void deleteGroup(unsigned int gID);

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

	std::vector<tgroup> inputGroups, outputGroups;
	std::vector<pin> inputPins, outputPins;

	bool evaluatePins(std::vector<pin> pins, bool cond);
	bool switchConditions(short conditional, bool pinCondition, bool state);
	void setOutputState(int newState);
};


#endif //COLUMN_TRIGGER_HPP
