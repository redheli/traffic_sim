/*
 * Purpose: A Test-bed for The New Framework
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#include <iostream>

#include "../share/shared_include.h"

#include "../share/TestBedSettings.h"
#include "../share/RoadNetwork.h"
#include "../share/advance_utils/VehiclePackage.h"
#include "../share/TimeTools.h"
#include "../share/Segment.h"
#include "../share/Lane.h"

using namespace std;

static int current_time_step = 0;

/*
 * Functions
 */
int init_simulation(int argc, char* argv[]);
void init_simulation_per_one_time_step();
int simulate_one_time_step();
int load_vehicles_one_time_step();
int close_simulation();

int main(int argc, char* argv[]) {

	init_simulation(argc, argv);

	TimeTools profile;
	profile.start_profiling();

	for (current_time_step = TestBedSettings::start_time_step; current_time_step < TestBedSettings::end_time_step; current_time_step += TestBedSettings::time_step_unit) {
		init_simulation_per_one_time_step();
		simulate_one_time_step();
		load_vehicles_one_time_step();

		if (TestBedSettings::debug_mode) {
			std::cout << "tick: " << current_time_step << std::endl;
			std::cout << "----------------------------------------------" << std::endl;
		}
	}

	profile.end_profiling();
	profile.output();

	close_simulation();

	if (TestBedSettings::debug_mode)
		std::cout << "simulastion exit successfully" << std::endl;

	return 0;
}

int init_simulation(int argc, char* argv[]) {

	//end_time_step, timestep, seg_length, loading_freq, loading_vehicles and debug_mode

	if (argc == 7) {
		TestBedSettings::end_time_step = atoi(argv[1]);
		TestBedSettings::time_step_unit = atoi(argv[2]);
		TestBedSettings::total_time_step = (TestBedSettings::end_time_step - TestBedSettings::start_time_step) / TestBedSettings::time_step_unit;  //sec

		TestBedSettings::seg_length = atoi(argv[3]);
		TestBedSettings::lane_outside_capacity_per_time_step_unit = 1800 * TestBedSettings::time_step_unit / 3600; //vehicles per time_step_unit
		TestBedSettings::lane_inside_capacity_per_time_step_unit = 1800 * TestBedSettings::time_step_unit / 3600; //vehicles per time_step_unit

		TestBedSettings::loading_freq = atof(argv[4]);
		TestBedSettings::loading_vehicles = atoi(argv[5]);

		if (atoi(argv[6]) == 1) {
			TestBedSettings::debug_mode = true;
		}
		else {
			TestBedSettings::debug_mode = false;
		}

		std::cout << "updated paraemters" << std::endl;
	}

	if (TestBedSettings::debug_mode)
		std::cout << "init_simulation" << std::endl;

	RoadNetwork::instance().init_network();

	return 1;
}

void init_simulation_per_one_time_step() {
	RoadNetwork::instance().seg1->reset_simulation_per_time_step();
	RoadNetwork::instance().seg2->reset_simulation_per_time_step();
	RoadNetwork::instance().seg3->reset_simulation_per_time_step();
	RoadNetwork::instance().seg4->reset_simulation_per_time_step();
	RoadNetwork::instance().seg5->reset_simulation_per_time_step();
}

int simulate_one_time_step() {
	if (TestBedSettings::debug_mode)
		std::cout << "simulate_one_time_step: " << std::endl;

	RoadNetwork::instance().seg4->xy_update_time(current_time_step);
	RoadNetwork::instance().seg5->xy_update_time(current_time_step);
	RoadNetwork::instance().seg3->xy_update_time(current_time_step);

	/*
	 * Segment 1 & 2 simulated together
	 */
	RoadNetwork::instance().seg1->xy_simulate_seg1_2_together(current_time_step);

	return 1;
}

int load_vehicles_one_time_step() {
//	if (TestBedSettings::debug_mode)
//		std::cout << "load_vehicles_one_time_step: " << std::endl;

	static int loading_in_who = 0;
	static double left_value = TestBedSettings::start_time_step;

	left_value += TestBedSettings::time_step_unit;

	if (left_value >= TestBedSettings::loading_freq) {
		left_value -= TestBedSettings::loading_freq;

		if (RoadNetwork::instance().seg1->all_lanes[0]->empty_space < TestBedSettings::VEHICLE_OCCUPANCY_LENGTH * TestBedSettings::loading_vehicles
				|| RoadNetwork::instance().seg2->all_lanes[0]->empty_space < TestBedSettings::VEHICLE_OCCUPANCY_LENGTH * TestBedSettings::loading_vehicles) {

//			std::cout << "no space to load_vehicles_one_time_step: 0" << std::endl;

			return 0;
		}

		loading_in_who = 1 - loading_in_who;

//		std::cout << "load_vehicles_one_time_step: 4" << std::endl;

		/*
		 * Currently, there is no constrains on the empty space
		 * Segment 1
		 */
		{
			VehiclePackage* one_pac = new VehiclePackage();
			one_pac->joinTime = current_time_step;
			one_pac->vehicle_size = TestBedSettings::loading_vehicles * 1;

			for (int i = 0; i < TestBedSettings::loading_vehicles; i++) {

				if (loading_in_who == 0) {
					Vehicle *one = new Vehicle();
					one->origin_node_id = 1;
					one->densition_node_id = 5;
					one_pac->inner_vehicles.push_back(one);
				}
				else {
					Vehicle *two = new Vehicle();
					two->origin_node_id = 1;
					two->densition_node_id = 6;
					one_pac->inner_vehicles.push_back(two);
				}
			}

			RoadNetwork::instance().seg1->all_lanes[0]->vehiclePackageQueue.push_back(one_pac);
			RoadNetwork::instance().seg1->all_lanes[0]->queue_status->total_onside_vehicles += TestBedSettings::loading_vehicles * 1;
			RoadNetwork::instance().seg1->all_lanes[0]->queue_status->in_moving_vehicles += TestBedSettings::loading_vehicles * 1;
		}

		/*
		 * Segment 2
		 */
		{
			VehiclePackage* one_pac = new VehiclePackage();
			one_pac->joinTime = current_time_step;
			one_pac->vehicle_size = TestBedSettings::loading_vehicles * 1;

			for (int i = 0; i < TestBedSettings::loading_vehicles; i++) {
				if (loading_in_who == 0) {
					Vehicle *one = new Vehicle();
					one->origin_node_id = 1;
					one->densition_node_id = 5;
					one_pac->inner_vehicles.push_back(one);
				}
				else {
					Vehicle *two = new Vehicle();
					two->origin_node_id = 1;
					two->densition_node_id = 6;
					one_pac->inner_vehicles.push_back(two);
				}
			}

			RoadNetwork::instance().seg2->all_lanes[0]->vehiclePackageQueue.push_back(one_pac);
			RoadNetwork::instance().seg2->all_lanes[0]->queue_status->total_onside_vehicles += TestBedSettings::loading_vehicles * 1;
			RoadNetwork::instance().seg2->all_lanes[0]->queue_status->in_moving_vehicles += TestBedSettings::loading_vehicles * 1;
		}
	}

	return 1;
}

int close_simulation() {
	if (TestBedSettings::debug_mode)
		std::cout << "do nothing: " << std::endl;
	return 1;
}

