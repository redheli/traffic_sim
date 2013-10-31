/*
 * Segment_Speed_Hash.hpp
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#ifndef SEGMENT_SPEED_HASH_HPP_
#define SEGMENT_SPEED_HASH_HPP_

#include <map>
//#include <unordered_map>

#include "../TestBedSettings.h"

using namespace std;

class Segment_Speed_Hash {
public:
	Segment_Speed_Hash();
	virtual ~Segment_Speed_Hash();

public:

	int add_time_speed(int time, double speed);

	/*
	 * This function does not guarantee safety, please check whether the key exists
	 */
	double get_time_speed(int time);

public:
	//it is not supported on some computer
//	std::unordered_map<int, double> speed_his;
	std::map<int, double> speed_his;
};

#endif /* SEGMENT_SPEED_HASH_HPP_ */
