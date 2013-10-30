/*
 * Lane.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#include "Lane.h"
#include "TestBedSettings.h"

Lane::Lane() {
	lane_id = 0;
//	the_segment = NULL;
	queue_status = new LaneQueue();

	inbound_vehicles = NULL;
	outbound_vehicles = NULL;

	outside_capacity_per_time_step_unit = 0;
	inside_capacity_per_time_step_unit = 0;

	empty_space = 0;
	total_onside_vehicles = 0;
	in_queue_vehicles = 0;
	in_moving_vehicles = 0;
}

Lane::~Lane() {
	if (queue_status)
		delete queue_status;
}

void Lane::reset_input_output_capacity() {
	is_blocked = false;
	outside_capacity_per_time_step_unit = TestBedSettings::lane_outside_capacity_per_time_step_unit;
	inside_capacity_per_time_step_unit = TestBedSettings::lane_inside_capacity_per_time_step_unit;
}

