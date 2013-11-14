/*
 * Segment_Speed_Hash.hpp
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#ifndef SEGMENT_SPEED_HASH_HPP_
#define SEGMENT_SPEED_HASH_HPP_

#include <map>
#include <vector>
#include <unordered_map>
#include <google/dense_hash_map>

#include "../TestBedSettings.h"

using google::dense_hash_map;
using namespace std;
using std::tr1::hash;

struct eqstr
{
  bool operator()(int s1, int s2) const
  {
    return (s1 == s2);
  }
};

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

	/*
	 *
	 */
	void resizeTable();

public:
	//it is not supported on some computer
//	google::dense_hash_map<int, double, std::tr1::hash<int>, eqstr> speed_his;
//	std::unordered_map<int, double> speed_his;
//	std::map<int, double> speed_his;

	std::vector<double> speed_his;

};

#endif /* SEGMENT_SPEED_HASH_HPP_ */
