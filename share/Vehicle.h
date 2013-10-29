/*
 * Vehicle.h
 *
 *  Created on: Oct 29, 2013
 *      Author: redheli
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "shared_include.h"

#include "Segment.h"

#include <vector>

class Vehicle {
public:
	Vehicle();
	virtual ~Vehicle();
public:
	int ID;

	Vehicle *next;
	Vehicle *previous;

	/*
	 * Path is not saved, because in the small network, the path is hardcoded.
	 */
	int origin_node_id;
	int densition_node_id;

	/*
	 * used in the new framework
	 */
	int joinTime;
	int in_Queue_Time;
};

#endif /* VEHICLE_H_ */
