#ifndef COLUMN_GROUP_HPP
#define COLUMN_GROUP_HPP

#include <array>
#include <vector>
#include <iostream>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include "pin.hpp"

class objectHandler;

/*!
 * \brief Class that allows the user to group pins together
 * \class group
 */
class group {
public:
	group();

	/*!
	 * \brief Initalizes the group, only to be called by the objectHandler unless you know what you are doing
	 * \param id The id to be assinged to this group
	 * \param name The name to be assinged to this group
	 * \param mode This groups mode, can be either INPUT or OUTPUT
	 * \param handler Pointer to object handler in which the group is saved
	 */
	void init(int id, std::string name, int mode, objectHandler *handler);

	/*!
	 * \brief Adds a pin to the group
	 * \details This also automatically checks whether the pin is in the same mode as the group
	 * \param wpi The wiringPi numbering scheme index of the pin to be added
	 * \param pnodeID The nodeID of the pin to added
	 * \return Whether the addition has been succesfull, !0 if succesfull
	 */
	int addPin(int wpi, unsigned int pnodeID);
	/*!
	 * \brief Removes a pin from the group
	 * \param wpi The wiringPi numbering scheme index of the pin to be removed
	 * \param nodeID The nodeID of the pin to be removed
	 * \param pos If you know the position of the pin in the internal map, set the others to null
	 * \return Whether the removal has been succesfull, !0 if succesfull
	 */
	int removePin(int wpi, int nodeID, unsigned int pos);

	/*! Toggles the entire group if it's in OUTPUT mode */
	int toggle();
	/*! Sets a new state for the entire group if it's in OUTPUT mode */
	void newState(int state);

	/*! Returns a map with all pins in this group */
	std::vector<pin> getPins();
	/*! Returns whether this group is in OUTPUT or INPUT mode */
	int getMode();

	std::string name;
private:
	int id, mode, state;
	objectHandler* handler;

	std::vector<pin> pins;

	//for saving
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, unsigned int version)
	{
		ar  & boost::serialization::make_nvp("id", id)
			& boost::serialization::make_nvp("name", name)
			& boost::serialization::make_nvp("mode", mode)
			& boost::serialization::make_nvp("pins", pins)
			& boost::serialization::make_nvp("state", state);
	}
};

#endif //COLUMN_GROUP_HPP
