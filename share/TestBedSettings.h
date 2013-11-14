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
	static int start_time_step; //sec
	static int end_time_step;   //sec
	static int time_step_unit;  //sec
	static int total_time_step;  //sec

	/*
	 * Network Related
	 */
	static double seg_length; //meter
	static int lane_outside_capacity_per_time_step_unit; //vehicles per time_step_unit
	static int lane_inside_capacity_per_time_step_unit; //vehicles per time_step_unit

	/*
	 * Speed Related
	 */
	static double VEHICLE_LENGTH; // m
	static double VEHICLE_OCCUPANCY_LENGTH; // m

	static double MAX_SPEED; // m/s
	static double MIN_SPEED; // m/s
	static double MAX_LANE_DENSITY; //max number of vehicle in a lane

	/*
	 * Demand (OD) related
	 */
	static double loading_freq; //how many time_step_units load once
	static int loading_vehicles; //how many vehicles load once

	/*
	 * Others
	 */
	static bool debug_mode;
	static int remove_speed_frequency;
};

#endif /* TESTBEDSETTINGS_H_ */
