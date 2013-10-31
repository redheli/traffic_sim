/*
 * TimeTools.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: xuyan
 */

#include "TimeTools.h"

TimeTools::TimeTools() {
}

TimeTools::~TimeTools() {

}

void TimeTools::start_profiling() {
//	start_time = System.
	gettimeofday(&start_time, NULL);
}

void TimeTools::end_profiling() {
	gettimeofday(&end_time, NULL);
}

void TimeTools::output() {
	double cost = diff_ms(end_time, start_time);
	std::cout << "Time (ms)" << cost << std::endl;
}

double TimeTools::diff_ms(timeval t1, timeval t2) {
	return (((t1.tv_sec - t2.tv_sec) * 1000000.0) + (t1.tv_usec - t2.tv_usec) / 1000.0);
}
