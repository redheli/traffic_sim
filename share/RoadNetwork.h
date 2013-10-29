/*
 * RoadNetwork.h
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#ifndef ROADNETWORK_H_
#define ROADNETWORK_H_

#include "Segment.h"

class RoadNetwork {
public:

	RoadNetwork();
	virtual ~RoadNetwork();

	void init_network();

public:
	/*
	 * List of Segments
	 */
	Segment* seg1;
	Segment* seg2;
	Segment* seg3;
	Segment* seg4;
	Segment* seg5;

};

#endif /* ROADNETWORK_H_ */
