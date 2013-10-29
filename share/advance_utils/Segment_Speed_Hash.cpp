/*
 * Segment_Speed_Hash.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */


#include "Segment_Speed_Hash.h"

Segment_Speed_Hash::Segment_Speed_Hash()
{
	/*
	 * each time step has a reserve;
	 * This is not the best choice, in reality, I should remove some;
	 * But for this case study, it is fine;
	 */
//	speed_his.reserve(TestBedSettings::total_time_step);
}

Segment_Speed_Hash::~Segment_Speed_Hash()
{
	speed_his.clear();
}

int Segment_Speed_Hash::add_time_speed(int time, double speed)
{
	speed_his[time] = speed;
	return 1;
}

double Segment_Speed_Hash::get_time_speed(int time)
{
	return speed_his[time];
}

