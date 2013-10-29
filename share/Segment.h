/*
 * Vehicle.h
 *
 *  Created on: Oct 29, 2013
 *      Author: redheli
 */
#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "advance_utils/Segment_Speed_Hash.h"

class Segment
{
public:
	Segment();
	virtual ~Segment();

public:

public:
	int seg_id;
	int seg_length;
	Segment_Speed_Hash* hash_table_speed;
};

#endif /* SEGMENT_H_ */
