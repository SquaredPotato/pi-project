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
		pinMode(a.first, a.second.pin);

		switch (a.second.pin)
		{
			case INPUT:
			{
				pullUpDnControl(a.first, a.second.pulldown);
				break;
			}
			case OUTPUT:
			{
				digitalWrite(a.first, a.second.state);
				break;
			}
			case PWM_OUTPUT:
			{
				pwmSetClock(this->pwm_clock);
				pwmSetMode(this->pwm_mode);
				pwmSetRange(this->pr);
				pwmWrite(a.first, a.second.pwm);
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
	tmp.edge = edge;
	tmp.pulldown = pUpDown;
	tmp.name = name;

	this->pins.insert(std::pair<int, npin>(wpi, tmp));

	pinMode (wpi, INPUT);
	pullUpDnControl (wpi, pUpDown);
}

void node::add_output (int wpi, int state, std::string name)
{
	npin tmp;
	tmp.pin = OUTPUT;
	tmp.name = name;
	tmp.state = state;

	this->pins.insert(std::pair<int, npin>(wpi, tmp));

	pinMode (wpi, OUTPUT);
	digitalWrite (wpi, state);
}

void node::add_pwm_output (int wpi, unsigned int pwmr, int pwmc, int pwmm, int pwm)
{
	npin tmp;

	tmp.pin = PWM_OUTPUT;
	tmp.pwm = pwm;

	this->pins.insert(std::pair<int, npin>(wpi, tmp));

	this->pwm_clock = pwmc;        // PWM clock
	this->pr = pwmr;        // PWM range
	this->pwm_mode = pwmm;        // PWM mode

	pwmSetMode (pwmm);
	pwmSetClock (pwmc);
	pwmSetRange (pwmr);
	pwmWrite (wpi, pwm);
}

void node::set_output_state (int wpi, int state)
{
	digitalWrite (wpi, state);
	this->pins.at(wpi).state = state;
}

void node::toggle_pwm (int wpi)
{
	if (this->pins.at(wpi).pin == PWM_OUTPUT)
	{
		this->pins.at(wpi).pin = OUTPUT;
		pinMode (wpi, OUTPUT);
	}
	else
	{
		pwmSetMode (this->pwm_mode);
		pwmSetClock (this->pwm_clock);
		pwmSetRange (this->pr);
		pwmWrite (wpi, this->pins.at(wpi).pwm);
		this->pins.at(wpi).pin = PWM_OUTPUT;
	}
}

void node::toggle_output_state (int wpi)
{
	if (this->pins.at(wpi).state == HIGH)
	{
		this->pins.at(wpi).state = LOW;
		digitalWrite (wpi, LOW);
	}
	else
	{
		this->pins.at(wpi).state = HIGH;
		digitalWrite (wpi, HIGH);
	}
}

void node::set_pwm (int wpi, int pwm)
{
	this->pins.at(wpi).pwm = pwm;
	pwmWrite (wpi, pwm);
}

void node::set_pwmc (int pwmc)
{
	this->pwm_clock = pwmc;
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
	return this->pins.at(wpi).state;
}

int node::get_digital_input_state (int wpi)
{
	return this->pins.at(wpi).state = digitalRead (wpi);
}

int node::get_mode (int wpi)
{
	return this->pins.at(wpi).pin;
}

int node::get_edge (int wpi)
{
	return this->pins.at(wpi).edge;
}

int node::get_node_id()
{
	return this->id;
}

std::string node::get_address()
{
	return this->location;
}