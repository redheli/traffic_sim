/*
 * Vehicle.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: redheli
 */

#include "Vehicle.h"

Vehicle::Vehicle() {
	// TODO Auto-generated constructor stub
	next = NULL;
	previous = NULL;
	path = new LanePath();
}

Vehicle::~Vehicle() {
	// TODO Auto-generated destructor stub
}

