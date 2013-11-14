/*
 * Vehicle.h
 *
 *  Created on: Oct 29, 2013
 *      Author: redheli
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "shared_include.h"

//#include "Segment.h"

#include <vector>

class Segment;

class Vehicle {
public:
	Vehicle();
	virtual ~Vehicle();
public:
	int ID;
	double position; // position on the lane

	Vehicle *next;
	Vehicle *previous;

	/*
	 * need path to know next segment
	 */
	std::vector<Segment*> path;

	int origin_node_id;
	int densition_node_id;

	/*
	 * used in the new framework
	 */
//	int joinTime; // move to vehicle package
//	int in_Queue_Time; // move to vehicle package
};

#endif /* VEHICLE_H_ */
