#ifndef COLUMN_NODE_HPP
#define COLUMN_NODE_HPP

#include <wiringPi.h>
#include <boost/asio.hpp>
#include <array>
#include <map>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include "pin.cpp"
//#include "I2CDevice.hpp

class node
{
public:
	node();
	friend class boost::serialization::access;

	/*!
	 * \brief Initialises the node
	 * \param name Name for the node
	 * \param id ID of the node, given by the \link #objectHandler \endlink
	 * \param address IP Address, for us in later implentation
	 */
	void init(std::string name, unsigned int id, std::string address);

	/*! Re-initalizes node, needed if settings are loaded after a reboot */
	void reInit ();
	/*! Deletes a pin using the wiringPi scheme index */
	void delPin(int wpi);

	/*!
	 * \brief Adds an input pin to this node
	 * \param wpi Pin index according to the wiringPi numbering scheme
	 * \param edge Whether an interrupt should occur at rising, falling or either edge
	 * \param pUpDown Whether the input should be connected to the pull UP, DOWN or no resistor at all
	 * \param name Name of the pin
	 */
	void add_input(int wpi, int edge, int pUpDown, std::string name);
	/*!
	 * \brief Adds an output pin to this node
	 * \param wpi wpi Pin index according to the wiringPi numbering scheme
	 * \param state Initial state, either HIGH or LOW
	 * \param name Name of the pin
	 */
	void add_output(int wpi, int state, std::string name);
	void add_pwm_output(int wpi, unsigned int pwmr, int pwmc, int pwmm, int pwm);
//	void add_soft_pwm();
//	void add_pwm_tone_output(); //impossible with wPi library?
//	void add_soft_tone_output();

	/*! Sets output to either HIGH or LOW to pin wpi */
	void set_output_state(int wpi, int state);
	void set_pwm(int wpi, int pwm);
	void set_pwmr(int wpi, unsigned int pwmr);
	void set_pwmc(int pwmc);
	void set_pwmm(int mode);

	void toggle_pwm(int wpi);
	void toggle_output_state(int wpi);

	/*! Returns HIGH or LOW depending saved state */
	int get_output_state(int wpi);
	/*! Returns HIGH or LOW depending on input state */
	int get_digital_input_state(int wpi);
	/*! Returns whether the pin is in INPUT, OUTPUT or PWM_OUTPUT mode */
	int get_mode(int wpi);
	/*! Returns the edge on which the pin event should trigger */
	int get_edge(int wpi);
	/*! Returns node ID of this node */
	int get_node_id();
	/*! Returns ip address of this node */
	std::string get_address();

	std::string name;
private:
	//identity of object
	std::string location;
	unsigned int id;

	/*\
	|*|  pm: pwm mode
	|*|  pc: pwm clock
	|*|  pr: pwm range
	|*|  pw: pwm percentage / stored in pin.cpp::npin
	|*|
	|*|  p: pin mode
	|*|  s: state of said gpin
	|*|  e: edge (for setting up triggers, unimplemented as of now)
	|*|  ud: upDown resistor
	\*/

	int pm, pc;
	unsigned int pr = 0;
	std::map<int, npin> pins;

	// Setting archive
	template<class Archive>
	void serialize(Archive & ar, unsigned int version)
	{
		ar  & boost::serialization::make_nvp("id", id)
			& boost::serialization::make_nvp("name", name)
			& boost::serialization::make_nvp("location", location)
			& boost::serialization::make_nvp("pr", pr)
			& boost::serialization::make_nvp("pins", pins);
	}
};


#endif //COLUMN_NODE_HPP
