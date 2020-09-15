#include "node.hpp"
#include <utility>
#include <iostream>

node::node()
=default;

void node::init(std::string name, unsigned int id, std::string address)
{
	this->name = std::move(name);
	this->id = id;
	this ->location = std::move(address);
}

void node::reInit ()
{
	for (std::pair<int, npin> a : this->pins)
	{
		pinMode(a.first, a.second.p);

		switch (a.second.p)
		{
			case INPUT:
			{
				pullUpDnControl(a.first, a.second.ud);
				break;
			}
			case OUTPUT:
			{
				digitalWrite(a.first, a.second.s);
				break;
			}
			case PWM_OUTPUT:
			{
				pwmSetClock(this->pc);
				pwmSetMode(this->pm);
				pwmSetRange(this->pr);
				pwmWrite(a.first, a.second.pw);
				break;
			}
			default:
			{	break;  }
		}
	}
}

void node::delPin(int wpi)
{
	this->pins.erase(wpi);

	// Reset gpin to defaults
	digitalWrite(wpi, LOW);
	pinMode(wpi, INPUT);
	pullUpDnControl(wpi, PUD_OFF);
}

void node::add_input(int wpi, int edge, int pUpDown, std::string name)
{
	npin tmp;
	tmp.e = edge;
	tmp.ud = pUpDown;
	tmp.name = name;

	this->pins.insert(std::pair<int, npin>(wpi, tmp));

	pinMode (wpi, INPUT);
	pullUpDnControl (wpi, pUpDown);
}

void node::add_output (int wpi, int state, std::string name)
{
	npin tmp;
	tmp.p = OUTPUT;
	tmp.name = name;
	tmp.s = state;

	this->pins.insert(std::pair<int, npin>(wpi, tmp));

	pinMode (wpi, OUTPUT);
	digitalWrite (wpi, state);
}

void node::add_pwm_output (int wpi, unsigned int pwmr, int pwmc, int pwmm, int pwm)
{
	npin tmp;

	tmp.p = PWM_OUTPUT;
	tmp.pw = pwm;

	this->pins.insert(std::pair<int, npin>(wpi, tmp));

	this->pc = pwmc;        // PWM clock
	this->pr = pwmr;        // PWM range
	this->pm = pwmm;        // PWM mode

	pwmSetMode (pwmm);
	pwmSetClock (pwmc);
	pwmSetRange (pwmr);
	pwmWrite (wpi, pwm);
}

void node::set_output_state (int wpi, int state)
{
	digitalWrite (wpi, state);
	this->pins.at(wpi).s = state;
}

void node::toggle_pwm (int wpi)
{
	if (this->pins.at(wpi).p == PWM_OUTPUT)
	{
		this->pins.at(wpi).p = OUTPUT;
		pinMode (wpi, OUTPUT);
	}
	else
	{
		pwmSetMode (this->pm);
		pwmSetClock (this->pc);
		pwmSetRange (this->pr);
		pwmWrite (wpi, this->pins.at(wpi).pw);
		this->pins.at(wpi).p = PWM_OUTPUT;
	}
}

void node::toggle_output_state (int wpi)
{
	if (this->pins.at(wpi).s == HIGH)
	{
		this->pins.at(wpi).s = LOW;
		digitalWrite (wpi, LOW);
	}
	else
	{
		this->pins.at(wpi).s = HIGH;
		digitalWrite (wpi, HIGH);
	}
}

void node::set_pwm (int wpi, int pwm)
{
	this->pins.at(wpi).pw = pwm;
	pwmWrite (wpi, pwm);
}

void node::set_pwmc (int pwmc)
{
	this->pc = pwmc;
	pwmSetClock (pwmc);
}

void node::set_pwmr (int wpi, unsigned int pwmr)
{
	this->pr = pwmr;
	pwmSetRange (pwmr);
}

void node::set_pwmm (int mode)
{
	pwmSetMode (mode);
}

int node::get_output_state (int wpi)
{
	return this->pins.at(wpi).s;
}

int node::get_digital_input_state (int wpi)
{
	return this->pins.at(wpi).s = digitalRead (wpi);
}

int node::get_mode (int wpi)
{
	return this->pins.at(wpi).p;
}

int node::get_edge (int wpi)
{
	return this->pins.at(wpi).e;
}

int node::get_node_id()
{
	return this->id;
}

std::string node::get_address()
{
	return this->location;
}