/*
 * RoadNetwork.h
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#ifndef ROADNETWORK_H_
#define ROADNETWORK_H_

#include "shared_include.h"

#include "Segment.h"

class RoadNetwork {
public:

	virtual ~RoadNetwork();

	void init_network();
    void update(double dt);
	/*
	 * Using New Framework
	 */
	void xy_simulate_seg1_2_together(int current_time_step);

public:
	/*
	 * List of Segments
	 */
	Segment* seg1;
	Segment* seg2;
	Segment* seg3;
	Segment* seg4;
	Segment* seg5;

public:
	static RoadNetwork &
	instance() {
		return instance_;
	}

private:
	RoadNetwork();

private:
	static RoadNetwork instance_;
};

#endif /* ROADNETWORK_H_ */
