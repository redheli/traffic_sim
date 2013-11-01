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

//class Segment;
class LaneQueue;

class Lane {
public:
	Lane();
	virtual ~Lane();

public:
	void reset_input_output_capacity();

	void update_queue_status_when_moving_segment(int time_step_in_queue);

public:
	int lane_id;
//	Segment* the_segment;

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
	double empty_space;

	/*
	 * For the DynaMIT framework
	 */

};

#endif /* LANE_H_ */
