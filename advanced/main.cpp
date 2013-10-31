///*
// * Purpose: A Test-bed for The New Framework
// *
// *  Created on: Oct 29, 2013
// *      Author: xuyan
// */
//
//#include <iostream>
//
//#include "../share/TestBedSettings.h"
//#include "../share/RoadNetwork.h"
//#include "../share/VehiclePackage.h"
//#include "../share/TimeTools.h"
//
//using namespace std;
//
//static int current_time_step = 0;
//
///*
// * Functions
// */
//int init_simulation();
//void init_simulation_per_one_time_step();
//int simulate_one_time_step();
//int load_vehicles_one_time_step();
//int close_simulation();
//
//int main() {
//
//	init_simulation();
//
//	TimeTools profile;
//	profile.start_profiling();
//
//	for (current_time_step = TestBedSettings::start_time_step; current_time_step < TestBedSettings::end_time_step; current_time_step += TestBedSettings::time_step_unit) {
//		init_simulation_per_one_time_step();
//		simulate_one_time_step();
//		load_vehicles_one_time_step();
//		std::cout << "tick: " << current_time_step << std::endl;
//	}
//
//	profile.end_profiling();
//	profile.output();
//
//	close_simulation();
//
//	if (TestBedSettings::debug_mode)
//		std::cout << "simulation exit successfully" << std::endl;
//
//	return 0;
//}
//
//int init_simulation() {
//	if (TestBedSettings::debug_mode)
//		std::cout << "init_simulation: " << std::endl;
//
//	RoadNetwork::instance().init_network();
//
//	return 1;
//}
//
//void init_simulation_per_one_time_step() {
//	RoadNetwork::instance().seg1->reset_simulation_per_time_step();
//	RoadNetwork::instance().seg2->reset_simulation_per_time_step();
//	RoadNetwork::instance().seg3->reset_simulation_per_time_step();
//	RoadNetwork::instance().seg4->reset_simulation_per_time_step();
//	RoadNetwork::instance().seg5->reset_simulation_per_time_step();
//}
//
//int simulate_one_time_step() {
//	if (TestBedSettings::debug_mode)
//		std::cout << "simulate_one_time_step: " << std::endl;
//
//	RoadNetwork::instance().seg4->xy_update_time(current_time_step);
//	RoadNetwork::instance().seg5->xy_update_time(current_time_step);
//	RoadNetwork::instance().seg3->xy_update_time(current_time_step);
//
//	/*
//	 * Segment 1 & 2 simulated together
//	 */
//	RoadNetwork::instance().xy_simulate_seg1_2_together(current_time_step);
//
//	return 1;
//}
//
//int load_vehicles_one_time_step() {
//	if (TestBedSettings::debug_mode)
//		std::cout << "load_vehicles_one_time_step: " << std::endl;
//
//	if (current_time_step % TestBedSettings::loading_freq == 0) {
//		/*
//		 * Currently, there is no constrains on the empty space
//		 * Segment 1
//		 */
//		{
//			VehiclePackage* one_pac = new VehiclePackage();
//			one_pac->joinTime = current_time_step;
//
//			for (int i = 0; i < TestBedSettings::loading_vehicles; i++) {
//				Vehicle *one = new Vehicle();
//				one->origin_node_id = 1;
//				one->densition_node_id = 5;
//				one_pac->inner_vehicles.push_back(one);
//
//				Vehicle *two = new Vehicle();
//				two->origin_node_id = 1;
//				two->densition_node_id = 6;
//				one_pac->inner_vehicles.push_back(two);
//			}
//
//			RoadNetwork::instance().seg1->all_lanes[0]->vehiclePackageQueue.push(one_pac);
//		}
//
//		/*
//		 * Segment 2
//		 */
//		{
//			VehiclePackage* one_pac = new VehiclePackage();
//			one_pac->joinTime = current_time_step;
//
//			for (int i = 0; i < TestBedSettings::loading_vehicles; i++) {
//				Vehicle *one = new Vehicle();
//				one->origin_node_id = 1;
//				one->densition_node_id = 5;
//				one_pac->inner_vehicles.push_back(one);
//
//				Vehicle *two = new Vehicle();
//				two->origin_node_id = 1;
//				two->densition_node_id = 6;
//				one_pac->inner_vehicles.push_back(two);
//			}
//
//			RoadNetwork::instance().seg2->all_lanes[0]->vehiclePackageQueue.push(one_pac);
//		}
//	}
//
//	return 1;
//}
//
//int close_simulation() {
//	if (TestBedSettings::debug_mode)
//		std::cout << "do nothing: " << std::endl;
//	return 1;
//}
//
