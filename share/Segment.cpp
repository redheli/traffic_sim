#include "Segment.h"

#include <iostream>

#include "TestBedSettings.h"
#include "Lane.h"

Segment::Segment() {
	std::cout << "segment" << std::endl;

	seg_length = TestBedSettings::seg_length;
	hash_table_speed = new Segment_Speed_Hash();
}

Segment::~Segment() {
	if (hash_table_speed) {
		delete hash_table_speed;
	}
}

void Segment::update_time_dynamit_framework() {

}

void Segment::xy_update_time(int current_time_step) {
	//according to the segment ID
	if (seg_id == 1 || seg_id == 2) {
		//these two segments should be processed together
		return;
	}

	if (seg_id == 3) {

	}

	else if (seg_id == 4 || seg_id == 5) {

	}
}

void Segment::reset_simulation_per_time_step() {
	for (std::vector<Lane*>::iterator it = all_lanes.begin();
			it != all_lanes.end(); ++it) {
		/* std::cout << *it; ... */
		(*it)->reset_input_output_capacity();
	}
}

void Segment::xy_add_a_new_vehicle_in_segment(int lane_id) {

}
