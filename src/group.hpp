#ifndef COLUMN_GROUP_HPP
#define COLUMN_GROUP_HPP

#include <array>
#include <vector>
#include <iostream>
#include "pin.cpp"

class objectHandler;

/*!
 * \brief Class that allows the user to group pins together
 * \class group
 */
class group {
public:
	group();

	/*!
	 * \brief Initalizes the group
	 * \param id The id to be assinged to this group
	 * \param name The name to be assinged to this group
	 * \param mode This groups mode, can be either INPUT or OUTPUT
	 * \param handler Pointer to object handler in which the group is saved
	 */
	void init(unsigned int id, std::string name, int mode, objectHandler *handler);
	/*!
	 * \brief Sets pointer to new objectHandler
	 * @param handler pointer to new objectHandler
	 */
	void setHandler(objectHandler *handler);

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
	 * \return Whether the removal has been successfull, !0 if successfull
	 */
	int removePin(int wpi, int nodeID);
	/*!
	 * \brief Removes a pin from the group
	 * \param pos Position of the pin in the internal map
	 * \return Whether the removal has been successfull, !0 if successfull
	 */
	int removePin(unsigned int pos);

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
};

#endif //COLUMN_GROUP_HPP
