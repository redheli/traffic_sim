/*
 * LaneQueue.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#include "LaneQueue.h"


LaneQueue::LaneQueue()
{
	end_queue_vehicle = NULL;
	the_time_step = 0;
	the_accumulated_offset = 0;
	current_queue_length = 0;
}

LaneQueue::~LaneQueue(){}

