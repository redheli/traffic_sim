/*
 * LaneQueue.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#include "LaneQueue.h"
#include "TestBedSettings.h"

LaneQueue::LaneQueue() {
	end_queue_VehiclePackage = NULL;

//	the_time_step = TestBedSettings::start_time_step - TestBedSettings::time_step_unit;
	the_accumulated_offset = 0;

	current_queue_length = 0;
	total_onside_vehicles = 0;
	in_queue_vehicles = 0;
	in_moving_vehicles = 0;

}

LaneQueue::~LaneQueue() {
}

