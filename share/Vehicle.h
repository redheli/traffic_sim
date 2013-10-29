/*
 * Vehicle.h
 *
 *  Created on: Oct 29, 2013
 *      Author: redheli
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "Segment.h"

#include <vector>

class Vehicle {
public:
	Vehicle();
	virtual ~Vehicle();
public:
	int ID;
	int joinTime;
	Vehicle *next;
	Vehicle *previous;
	std::vector<Segment*> path;
	int in_Queue_Time;
};

#endif /* VEHICLE_H_ */
