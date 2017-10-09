#ifndef COLUMN_NODE_HPP
#define COLUMN_NODE_HPP

#include <wiringPi.h>
#include <boost/asio.hpp>
#include <array>
#include <boost/serialization/access.hpp>
//#include "I2CDevice.hpp"
#include "connection.hpp"

// Global because structs can't be accessed from cpp files when in class field
// (No idea why, I'd rather have it inside the class.)
struct node_pin {
	int p, s, e, ud, pw;
	std::string name;
	template<class Archive>
	void serialize(Archive & ar, unsigned int version)
	{
		ar & p & s & e & ud & pw & name;
	}
};

class node {
public:
	node();
	friend class boost::serialization::access;

	void init(std::string name, int id, std::string address);

	void delPin(unsigned long wpi);

	void add_input(unsigned long wpi, int edge, int pUpDown, std::string name);
	void add_output(int wpi, int state, std::string name);
	void add_pwm_output(int wpi, unsigned int pwmr, int pwmc, int pwmm, int pwm);
//	void add_soft_pwm();
//	void add_pwm_tone_output(); //impossible with wPi library?
//	void add_soft_tone_output();

	void set_output_state(int wpi, int state);
	void set_pwm(int wpi, int pwm);
	void set_pwmr(int wpi, unsigned int pwmr);
	void set_pwmc(int pwmc);
	void set_pwmm(int mode);

	void toggle_pwm(int wpi);
	void toggle_output_state(int wpi);

	int get_output_state(int wpi);
	int get_digital_input_state(int wpi);
	int get_mode(int wpi);
	int get_edge(int wpi);
	int get_node_id();
	std::string get_address();
private:
	//identity of object
	std::string name, location;
	int id;

	/*\
	|*|  pm: pwm mode
	|*|  pc: pwm clock
	|*|  pr: pwm range
	|*|  pw: pwm percentage, I think
	|*|
	|*|  p: pin number according to wpi scheme
	|*|  s: state of said pin
	|*|  e: edge (for setting up triggers, unimplemented as of now)
	|*|  ud: upDown resistor
	|*|
	|*|  I2C devices left unimplemented for now
	\*/

	int pm, pc;
	std::array<node_pin, 40> pins;
	unsigned int pr;

	// Setting archive
	template<class Archive>
	void serialize(Archive & ar, unsigned int version)
	{
		ar & this->id & this->name & this->location & this->pr & this->pins;
	}
};


#endif //COLUMN_NODE_HPP
