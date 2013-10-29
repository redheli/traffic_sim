/*
 * TestBedSettings.h
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#ifndef TESTBEDSETTINGS_H_
#define TESTBEDSETTINGS_H_

#include "shared_include.h"

class TestBedSettings {
public:

	/*
	 * Time Related
	 */
	static const int start_time_step; //sec
	static const int end_time_step;   //sec
	static const int time_step_unit;  //sec
	static const int total_time_step;  //sec

	/*
	 * Network Related
	 */
	static const double seg_length; //meter
	static const int lane_outside_capacity_per_time_step_unit; //vehicles per time_step_unit
	static const int lane_inside_capacity_per_time_step_unit; //vehicles per time_step_unit

	/*
	 * Speed Related
	 */
	static const double VEHICLE_LENGTH; // m
	static const double VEHICLE_OCCUPANCY_LENGTH; // m

	static const double MAX_SPEED; // m/s
	static const double MIN_SPEED; // m/s
	static const double MAX_LANE_DENSITY; //max number of vehicle in a lane

	/*
	 * Demand (OD) related
	 */
	static const int loading_freq; //how many time_step_units load once
	static const int loading_vehicles; //how many vehicles load once

	/*
	 * Others
	 */
	static const bool debug_mode;
};

#endif /* TESTBEDSETTINGS_H_ */
