#include "Segment.h"

#include <iostream>

#include "Lane.h"

Segment::Segment()
{
	std::cout<<"segment"<<std::endl;

	hash_table_speed = new Segment_Speed_Hash();
}

Segment::~Segment()
{
	if(hash_table_speed)
	{
		delete hash_table_speed;
	}
}

void Segment::update_time_dynamit_framework()
{

}

void Segment::update_time_new_framework()
{

}

void Segment::reset_simulation_per_time_step()
{
	for(std::vector<Lane*>::iterator it = all_lanes.begin(); it != all_lanes.end(); ++it) {
	    /* std::cout << *it; ... */
		(*it)->reset_input_output_capacity();
	}
}
