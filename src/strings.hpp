#ifndef COLUMN_STRINGS_HPP
#define COLUMN_STRINGS_HPP

#include <string>

// Strings for console 'menu'
std::string strt = "Main Menu:\n"
				   "0: stop\n"
				   "1: Add node\n"
				   "2: Add input\n"
				   "3: Add output\n"
				   "4: Save settings\n"
				   "5: Load settings\n"
				   "6: Add group\n"
				   "7: Add Trigger\n"
				   "8: Add pin to Trigger\n",
			nID  = "Enter nodeID: \n",
			wiPi = "Enter wiringPi number: \n",
			eNam = "Enter name:\n",
			pupd = "Enter preferred pullUpDown resistor: (No resistor: 0, Down resistor: 1, Up resistor 2)\n",
			iedg = "Enter interrupt edge: (default: 0, falling: 1, rising: 2, both: 3)\n",
			gID  = "Enter groupID:\n",
			tID  = "Enter triggerID:\n",
			eMod = "Enter group mode:\n";



#endif //COLUMN_STRINGS_HPP
