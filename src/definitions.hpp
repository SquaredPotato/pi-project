#ifndef COLUMN_DEFINITIONS_H
#define COLUMN_DEFINITIONS_H

// Port used for tcp connections to other instances
#define TCP_PORT 13370

// Includes
#include <iostream>
#include <wiringPi.h>
#include <cstdio>
#include <map>
#include <memory>
#include <boost/thread.hpp>

#include "globalObjects.hpp"
#include "strings.hpp"

// Function declarations
void poll_loop(objectHandler &handler);
void run_test();

// Global variables
volatile int stop = 0;

#endif //COLUMN_DEFINITIONS_H