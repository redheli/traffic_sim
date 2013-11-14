/*
 * Segment_Speed_Hash.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#include "Segment_Speed_Hash.h"

//Segment_Speed_Hash::Segment_Speed_Hash() : speed_his(TestBedSettings::total_time_step + 1) {
Segment_Speed_Hash::Segment_Speed_Hash() {
	/*
	 * each time step has a reserve;
	 * This is not the best choice, in reality, I should remove some;
	 * But for this case study, it is fine;
	 */
//	speed_his.reserve(TestBedSettings::total_time_step);
//	speed_his.set_empty_key(-1);
//	speed_his.set_deleted_key(-2);
}

Segment_Speed_Hash::~Segment_Speed_Hash() {
	speed_his.clear();
}

void Segment_Speed_Hash::resizeTable() {
	speed_his.resize(TestBedSettings::total_time_step + 1);
}

int Segment_Speed_Hash::add_time_speed(int time, double speed) {

//	assert(time / TestBedSettings::time_step_unit < TestBedSettings::total_time_step);

	speed_his[time / TestBedSettings::time_step_unit] = speed;

//	speed_his[time] = speed;
	return 1;
}

double Segment_Speed_Hash::get_time_speed(int time) {

//	return 20;

//	assert(time / TestBedSettings::time_step_unit < TestBedSettings::total_time_step);

	return speed_his[time / TestBedSettings::time_step_unit];


//	return speed_his[time];
}
