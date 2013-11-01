/*
 * LaneQueue.h
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#ifndef LANEQUEUE_H_
#define LANEQUEUE_H_

#include "shared_include.h"

/*
 * forward declaration
 */
class VehiclePackage;

class LaneQueue {
public:
	LaneQueue();
	virtual ~LaneQueue();

public:

	//queue status
	double current_queue_length;
	VehiclePackage* end_queue_VehiclePackage;

	//offset
//	double the_accumulated_offset;
//	int the_time_step;

	//vehicles
	int total_onside_vehicles;
	int in_queue_vehicles;
	int in_moving_vehicles;
};

#endif /* LANEQUEUE_H_ */
