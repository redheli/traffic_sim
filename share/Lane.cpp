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

//	is_blocked = false;
//	total_onside_vehicles = 0;
//	in_queue_vehicles = 0;
//	in_moving_vehicles = 0;
}

Lane::~Lane() {
	if (queue_status)
		delete queue_status;
}

void Lane::reset_input_output_capacity() {
//	is_blocked = false;
	outside_capacity_per_time_step_unit = TestBedSettings::lane_outside_capacity_per_time_step_unit;
	inside_capacity_per_time_step_unit = TestBedSettings::lane_inside_capacity_per_time_step_unit;
}

void Lane::update_queue_status_when_moving_segment(int time_step_in_queue) {
//	std::cout << "update_queue_status_when_moving_segment:" << this->lane_id << ",time_step_in_queue:" << time_step_in_queue << std::endl;

//	if(time_step_in_queue == 22 && this->lane_id == 2)
//	{
//		int iiii = 2;
//	}

	if (vehiclePackageQueue.size() <= 0)
		return;

	if (queue_status->end_queue_VehiclePackage == NULL) {
		if (vehiclePackageQueue.queueFront->joinTime <= time_step_in_queue) {
			queue_status->end_queue_VehiclePackage = vehiclePackageQueue.queueFront;
			queue_status->in_queue_vehicles = queue_status->end_queue_VehiclePackage->vehicle_size;
			queue_status->current_queue_length = queue_status->end_queue_VehiclePackage->vehicle_size * TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;
			queue_status->in_moving_vehicles -= queue_status->end_queue_VehiclePackage->vehicle_size;
		} else {
			return;
		}
	}

	//
	while (true) {
		if (queue_status->end_queue_VehiclePackage->back != NULL && queue_status->end_queue_VehiclePackage->back->joinTime <= time_step_in_queue) {
			queue_status->end_queue_VehiclePackage = queue_status->end_queue_VehiclePackage->back;

			queue_status->in_queue_vehicles += queue_status->end_queue_VehiclePackage->vehicle_size;
			queue_status->current_queue_length += queue_status->end_queue_VehiclePackage->vehicle_size * TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;
			queue_status->in_moving_vehicles -= queue_status->end_queue_VehiclePackage->vehicle_size;
		} else {
			break;
		}

//		if (TestBedSettings::debug_mode)
//			std::cout << "update_queue_status_when_moving_segment" << std::endl;
	}
}

