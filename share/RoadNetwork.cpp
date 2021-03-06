/*
 * RoadNetwork.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#include "RoadNetwork.h"
#include <stddef.h>

#include "Lane.h"
#include "Segment.h"
#include "GeneralTool.h"

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
	if (seg1)
		delete seg1;

	if (seg2)
		delete seg2;

	if (seg3)
		delete seg3;

	if (seg4)
		delete seg4;

	if (seg5)
		delete seg5;
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
		one->capacity_ratio = 1;
		one->empty_space = seg1->seg_length;
		seg1->all_lanes.push_back(one);
	}
	seg1->hash_table_speed->resizeTable();

	seg2 = new Segment();
	seg2->seg_id = 2;
	{
		Lane* one = new Lane();
		one->lane_id = 2;
		one->the_segment = seg2;
		one->capacity_ratio = 1;
		one->empty_space = seg2->seg_length;
		seg2->all_lanes.push_back(one);
	}
	seg2->hash_table_speed->resizeTable();

	seg3 = new Segment();
	seg3->seg_id = 3;
	{
		Lane* one = new Lane();
		one->lane_id = 3;
		one->the_segment = seg3;
		one->capacity_ratio = 1;
		one->empty_space = seg3->seg_length;
		seg3->all_lanes.push_back(one);
	}
	seg3->hash_table_speed->resizeTable();

	seg4 = new Segment();
	seg4->seg_id = 4;
	{
		Lane* one = new Lane();
		one->lane_id = 4;
		one->the_segment = seg4;
		one->capacity_ratio = 1;
		one->empty_space = seg4->seg_length;
		seg4->all_lanes.push_back(one);
	}
	seg4->hash_table_speed->resizeTable();

	seg5 = new Segment();
	seg5->seg_id = 5;
	{
		Lane* one = new Lane();
		one->lane_id = 5;
		one->the_segment = seg5;
		one->capacity_ratio = 1;
		one->empty_space = seg5->seg_length;
		seg5->all_lanes.push_back(one);
	}
	seg5->hash_table_speed->resizeTable();
}

