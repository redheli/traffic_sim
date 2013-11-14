/*
 * Lane.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#include "Lane.h"
#include "TestBedSettings.h"
#include "Segment.h"

Lane::Lane() {
	lane_id = 0;
	the_segment = NULL;
	queue_status = new LaneQueue();

	inbound_vehicles = NULL;
	outbound_vehicles = NULL;

	outside_capacity_per_time_step_unit = 0;
	inside_capacity_per_time_step_unit = 0;

	empty_space = 0;

	capacity_ratio = 1;

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
	outside_capacity_per_time_step_unit = TestBedSettings::lane_outside_capacity_per_time_step_unit * this->capacity_ratio;
	inside_capacity_per_time_step_unit = TestBedSettings::lane_inside_capacity_per_time_step_unit * this->capacity_ratio;
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

			queue_status->the_accumulated_offset = this->the_segment->who_can_pass_offset;
		}
		else {
			return;
		}
	}
	else
	{
		queue_status->the_accumulated_offset += this->the_segment->hash_table_speed->get_time_speed(time_step_in_queue);
	}

	//
	while (true) {
		if (queue_status->end_queue_VehiclePackage->back != NULL && queue_status->end_queue_VehiclePackage->back->joinTime <= time_step_in_queue) {
			queue_status->end_queue_VehiclePackage = queue_status->end_queue_VehiclePackage->back;

			queue_status->in_queue_vehicles += queue_status->end_queue_VehiclePackage->vehicle_size;
			queue_status->current_queue_length += queue_status->end_queue_VehiclePackage->vehicle_size * TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;
			queue_status->in_moving_vehicles -= queue_status->end_queue_VehiclePackage->vehicle_size;
		}
		else {
			break;
		}

//		if (TestBedSettings::debug_mode)
//			std::cout << "update_queue_status_when_moving_segment" << std::endl;
	}

	int temp_t = queue_status->end_queue_VehiclePackage->joinTime;
	while(temp_t < time_step_in_queue)
	{
//		std::cout << "It does happen" << std::endl;
		queue_status->the_accumulated_offset += this->the_segment->hash_table_speed->get_time_speed(temp_t);
		temp_t += TestBedSettings::time_step_unit;
	}
}

void Lane::update_queue_status_after_moving_segment(int time_step) {

//	if (time_step == 48) {
//		int iii = 1;
//	}

	while (true) {
		if (queue_status->end_queue_VehiclePackage == NULL) {
			break;
		}
		else if (queue_status->end_queue_VehiclePackage->back != NULL) {

			int old_time_step = queue_status->end_queue_VehiclePackage->joinTime;
			int new_time_step = queue_status->end_queue_VehiclePackage->back->joinTime;
			double current_offset = queue_status->the_accumulated_offset;

			for (int i = old_time_step; i < new_time_step; i += TestBedSettings::time_step_unit) {
				current_offset -= the_segment->hash_table_speed->get_time_speed(i) * TestBedSettings::time_step_unit;
			}

			//put in the queue end
			if (current_offset + queue_status->current_queue_length >= the_segment->seg_length) {
				queue_status->end_queue_VehiclePackage = queue_status->end_queue_VehiclePackage->back;
				queue_status->in_queue_vehicles += queue_status->end_queue_VehiclePackage->vehicle_size;
				queue_status->current_queue_length += queue_status->end_queue_VehiclePackage->vehicle_size * TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;
				queue_status->in_moving_vehicles -= queue_status->end_queue_VehiclePackage->vehicle_size;
				queue_status->the_accumulated_offset = current_offset;
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
}

