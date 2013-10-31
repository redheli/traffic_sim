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
#include "VehiclePackage.h"

//class Segment;
class LaneQueue;

class Lane {
public:
	Lane();
	virtual ~Lane();

public:
	void reset_input_output_capacity();

public:
	int lane_id;
//	Segment* the_segment;

	/*
	 * For the new framework
	 */
	std::queue<VehiclePackage*> vehiclePackageQueue;
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
