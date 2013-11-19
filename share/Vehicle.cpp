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

	position = 0;
//	in_Queue_Time = 0;
	origin_node_id = 0;
	densition_node_id = 0;

	static int seed_vehicle_ID = 0;
	ID = seed_vehicle_ID++;
}

Vehicle::~Vehicle() {
	// TODO Auto-generated destructor stub
}

