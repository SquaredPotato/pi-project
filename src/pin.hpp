#ifndef COLUMN_PIN_HPP
#define COLUMN_PIN_HPP

#include <boost/serialization/nvp.hpp>
#include <wiringPi.h>

/*! Conditions for groups and pins in \link #trigger \endlink */
enum conds {
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
struct pin {
	int wpi = -1;
	short condition = OR;
	unsigned int nodeID;
public:
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar  & boost::serialization::make_nvp("wpi", wpi)
			& boost::serialization::make_nvp("condition", condition)
			& boost::serialization::make_nvp("nodeID", nodeID);
	}
};

/*!
 * \brief pin for usage in \ink node \endlink
 * \details stores details such as edge, pull UP DOWN resistor
 */
struct npin {
	int p = 0, s = 0, e = INT_EDGE_SETUP, ud = PUD_OFF, pw = 0;
	std::string name = "";
	template<class Archive>
	void serialize(Archive & ar, unsigned int version)
	{
		ar  & boost::serialization::make_nvp("pin", p)
			& boost::serialization::make_nvp("state", s)
			& boost::serialization::make_nvp("edge", e)
			& boost::serialization::make_nvp("updown", ud)
			& boost::serialization::make_nvp("pwm", pw)
			& boost::serialization::make_nvp("name", name);
	}
};

/*!
 * \brief group for usage in \link trigger \endlink
 * \details stores critical info for each group to determine the output of the trigger
 */
struct tgroup {
	unsigned int gID;
	short condition = OR;
	std::vector<pin> gpin = {};
public:
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar  & boost::serialization::make_nvp("gID", gID)
			& boost::serialization::make_nvp("condition", condition);
	}
};

#endif //COLUMN_PIN_HPP
