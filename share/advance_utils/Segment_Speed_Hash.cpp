/*
 * Segment_Speed_Hash.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */


#include "Segment_Speed_Hash.h"

Segment_Speed_Hash::Segment_Speed_Hash()
{
	speed_his.reserve(TestBedSettings::total_time_step);
}

Segment_Speed_Hash::~Segment_Speed_Hash()
{

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

