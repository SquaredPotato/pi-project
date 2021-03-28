#ifndef COLUMN_PIN_HPP
#define COLUMN_PIN_HPP

#include <wiringPi.h>
#include <string>
#include <vector>

/*! Conditions for groups and pins in \link #trigger \endlink */
enum conditions
{
	AND,
	NAND,
	OR,
	NOR,
	XOR,
	XNOR
};

/*!
 * \brief pin for usage in \link trigger \endlink
 * \details stores critical info for each pin to determine the output of the trigger
 */
struct pin
{
	int wpi = -1;
	short condition = OR;
	unsigned int id;
public:
};

/*!
 * \brief pin for usage in \ink node \endlink
 * \details stores details such as edge, pull UP DOWN resistor
 */
struct npin
{
	int pin = 0, state = 0, edge = INT_EDGE_SETUP, pulldown = PUD_OFF, pwm = 0;
	std::string name = "";
};

/*!
 * \brief group for usage in \link trigger \endlink
 * \details stores critical info for each group to determine the output of the trigger
 */
struct tgroup
{
	unsigned int id;
	short condition = OR;
	std::vector<pin> gpin = {};
public:
};

#endif //COLUMN_PIN_HPP
