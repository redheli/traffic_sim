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

class LaneQueue
{
public:
	LaneQueue();
	virtual ~LaneQueue();

public:

	double current_queue_length;
	VehiclePackage* end_queue_VehiclePackage;

	double the_accumulated_offset;
	int the_time_step;
};


#endif /* LANEQUEUE_H_ */
