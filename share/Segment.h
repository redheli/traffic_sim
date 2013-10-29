/*
 * Vehicle.h
 *
 *  Created on: Oct 29, 2013
 *      Author: redheli
 */
#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "shared_include.h"

#include "advance_utils/Segment_Speed_Hash.h"

using namespace std;

/*
 * forward declaration
 */
class Lane;

class Segment
{
public:
	Segment();
	virtual ~Segment();

public:

	/*
	 * reset the lanes' capacity
	 */
	void reset_simulation_per_time_step();

	/*
	 * Using DynaMIT Framework
	 */
	void update_time_dynamit_framework();

	/*
	 * Using New Framework
	 */
	void update_time_new_framework();

public:
	int seg_id;
	int seg_length;

	std::vector<Lane*> all_lanes;
	Segment_Speed_Hash* hash_table_speed;
};

#endif /* SEGMENT_H_ */
