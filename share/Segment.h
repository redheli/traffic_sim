/*
 * Vehicle.h
 *
 *  Created on: Oct 29, 2013
 *      Author: redheli
 */
#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "shared_include.h"
#include "Lane.h"
#include "advance_utils/Segment_Speed_Hash.h"

using namespace std;

/*
 * forward declaration
 */
class Vehicle;
//class Lane;

class Segment {
public:
	Segment();
	virtual ~Segment();

public:

	/*
	 * reset the lanes' capacity
	 */
	void reset_simulation_per_time_step();

	/*
	 * Using New Framework
	 */
	void xy_update_time(int current_time_step);

	/*
	 *
	 */
	void xy_clear_old_speeds();

	/*
	 *
	 */
	void xy_move_agents_to_next_segment(int current_time_step);

//	/*
//	 * Set of functions for the new framework
//	 * If name starts from "xy", the function is only used by the new framework
//	 */
//	void xy_add_a_new_vehicle_in_segment(int lane_id);

	/**
	 * process seg 1 and seg 2;
	 */
	Vehicle* xy_find_the_next_vehicle_package();

	/*
	 * process seg 1 and seg 2;
	 */
	void xy_simulate_seg1_2_together(int current_time_step);

public:
	int seg_id;
	double seg_length;

	std::vector<Lane*> all_lanes;
	Segment_Speed_Hash* hash_table_speed;

	/*
	 * Used to judge who & when can pass the segment
	 * If time <= who_can_pass_time, then can pass
	 */
	int who_can_pass_time;
	double who_can_pass_offset;

	/*
	 * Used to remove items in hash table
	 */
//	int last_remove_time_step;
public:
	/*
	 * Using DynaMIT Framework
	 */
	void dy_update_time(int current_time_step);

	/*
	 *Using DynaMIT Framework
	 */
	void dy_simulate_seg1_2_together(int current_time_step);

public:

	void dy_update_queue(int current_time_step);

	void dy_update_moving(int current_time_step, double speed);

	bool can_pass_to_next_lane(Vehicle * the_vehicle);

	/**
	 * process seg 1 and seg 2;
	 */
	Vehicle* dy_find_the_next_vehicle_package();
};

#endif /* SEGMENT_H_ */
