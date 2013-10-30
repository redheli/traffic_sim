/*
 * TimeTools.h
 *
 *  Created on: Oct 30, 2013
 *      Author: xuyan
 */

#ifndef TIMETOOLS_H_
#define TIMETOOLS_H_

#include "shared_include.h"
#include <sys/time.h>

class TimeTools {
public:
	TimeTools();
	~TimeTools();

public:
	void start_profiling();
	void end_profiling();
	void output();
	double diff_ms(timeval t1, timeval t2);

private:
	timeval start_time;
	timeval end_time;
};

#endif /* TIMETOOLS_H_ */
