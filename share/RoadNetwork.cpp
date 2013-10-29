/*
 * RoadNetwork.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#include "RoadNetwork.h"
#include <stddef.h>

#include "Lane.h"

//Signton

RoadNetwork RoadNetwork::instance_;

RoadNetwork::RoadNetwork() {
	seg1 = NULL;
	seg2 = NULL;
	seg3 = NULL;
	seg4 = NULL;
	seg5 = NULL;
}

RoadNetwork::~RoadNetwork() {

}

/*
 * TBA
 * Need to add more in the road network
 */
void RoadNetwork::init_network() {
	seg1 = new Segment();
	seg1->seg_id = 1;
	{
		Lane* one = new Lane();
		one->lane_id = 1;
		one->the_segment = seg1;
		seg1->all_lanes.push_back(one);
	}

	seg2 = new Segment();
	seg2->seg_id = 2;
	{
		Lane* one = new Lane();
		one->lane_id = 2;
		one->the_segment = seg2;
		seg1->all_lanes.push_back(one);
	}

	seg3 = new Segment();
	seg3->seg_id = 3;
	{
		Lane* one = new Lane();
		one->lane_id = 3;
		one->the_segment = seg3;
		seg1->all_lanes.push_back(one);

		Lane* two = new Lane();
		two->lane_id = 4;
		two->the_segment = seg3;
		seg1->all_lanes.push_back(two);
	}

	seg4 = new Segment();
	seg4->seg_id = 4;
	{
		Lane* one = new Lane();
		one->lane_id = 5;
		one->the_segment = seg4;
		seg1->all_lanes.push_back(one);
	}

	seg5 = new Segment();
	seg5->seg_id = 5;
	{
		Lane* one = new Lane();
		one->lane_id = 6;
		one->the_segment = seg5;
		seg1->all_lanes.push_back(one);
	}
}
