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

	in_Queue_Time = 0;

	static int seed_vehicle_ID = 0;
	ID = seed_vehicle_ID++;
}

Vehicle::~Vehicle() {
	// TODO Auto-generated destructor stub
}

