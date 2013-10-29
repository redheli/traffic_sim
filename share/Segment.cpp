#include "Segment.h"

#include <iostream>

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
