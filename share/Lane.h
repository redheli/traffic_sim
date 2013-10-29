/*
 * Lane.h
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#ifndef LANE_H_
#define LANE_H_

#include "shared_include.h"

#include "LaneQueue.h"
#include "Vehicle.h"

class Segment;
class LaneQueue;

class Lane
{
public:
	Lane();
	virtual ~Lane();

public:
	void reset_input_output_capacity();

public:
	int lane_id;
	Segment* the_segment;

	/*
	 * For the new framework
	 */
	LaneQueue* queue_status;
	Vehicle* inbound_vehicles;
	Vehicle* outbound_vehicles;

	int outside_capacity_per_time_step_unit;
	int inside_capacity_per_time_step_unit;
	double empty_space;

	int total_onside_vehicles;
	int in_queue_vehicles;
	int in_moving_vehicles;

	/*
	 * For the DynaMIT framework
	 */

};

#endif /* LANE_H_ */
