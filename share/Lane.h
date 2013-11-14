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
#include "advance_utils/VehiclePackage.h"
#include "advance_utils/VehiclePackageQueue.h"

class Segment;
class LaneQueue;

class Lane {
public:
	Lane();
	virtual ~Lane();

public:
	void reset_input_output_capacity();

	void update_queue_status_when_moving_segment(int time_step_in_queue);

	void update_queue_status_after_moving_segment(int time_step);

public:
	int lane_id;
	Segment* the_segment;

	/*
	 * For the new framework
	 */
	VehiclePackageQueue vehiclePackageQueue;
	LaneQueue* queue_status;

	/*
	 * used by seg 1 & seg 2 only
	 */
//	bool is_blocked;

	/*
	 * xy: I will not use these 2 variables
	 */
	Vehicle* inbound_vehicles;
	Vehicle* outbound_vehicles;

	int outside_capacity_per_time_step_unit;
	int inside_capacity_per_time_step_unit;

	int capacity_ratio;
	double empty_space;

	/*
	 * For the DynaMIT framework
	 */
	std::queue<Vehicle*> queue_veh; // store vh in queue
	double queue_length;
	std::queue<Vehicle*> move_veh; // store moving vh
};

#endif /* LANE_H_ */
