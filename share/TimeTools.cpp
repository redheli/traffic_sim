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
	std::cout << "===================================" << std::endl;
	std::cout << "Simulation Time (ms10E-3)" << cost << std::endl;
}

double TimeTools::diff_ms(timeval t1, timeval t2) {
//	diff = (tv[i].tv_sec - tv[i - 1].tv_sec) * 1000000;
//	diff += tv[i].tv_usec - tv[i - 1].tv_usec;

	return (((t1.tv_sec - t2.tv_sec) * 1000.0) + (t1.tv_usec - t2.tv_usec) / 1000.0);
}
