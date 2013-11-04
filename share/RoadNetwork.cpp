/*
 * RoadNetwork.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#include "RoadNetwork.h"
#include <stddef.h>

#include "Lane.h"
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
//		one->the_segment = seg1;
		one->empty_space = seg1->seg_length;
		seg1->all_lanes.push_back(one);
	}

	seg2 = new Segment();
	seg2->seg_id = 2;
	{
		Lane* one = new Lane();
		one->lane_id = 2;
//		one->the_segment = seg2;
		one->empty_space = seg2->seg_length;
		seg2->all_lanes.push_back(one);
	}

	seg3 = new Segment();
	seg3->seg_id = 3;
	{
		Lane* one = new Lane();
		one->lane_id = 3;
//		one->the_segment = seg3;
		one->empty_space = seg3->seg_length;
		seg3->all_lanes.push_back(one);
	}

	seg4 = new Segment();
	seg4->seg_id = 4;
	{
		Lane* one = new Lane();
		one->lane_id = 4;
//		one->the_segment = seg4;
		one->empty_space = seg4->seg_length;
		seg4->all_lanes.push_back(one);
	}

	seg5 = new Segment();
	seg5->seg_id = 5;
	{
		Lane* one = new Lane();
		one->lane_id = 5;
//		one->the_segment = seg5;
		one->empty_space = seg5->seg_length;
		seg5->all_lanes.push_back(one);
	}
}

void RoadNetwork::xy_simulate_seg1_2_together(int current_time_step)
{

}
void RoadNetwork::update()
{
    double dt = 0.1;
    double speed_move_in_queue = 3;
    double speed_moveing = 30;
	// seg 4
//    std::priority_queue<Vehicle*> queue_veh_tmp;
    size_t queue_size = seg4->queue_veh.size();
	for(int i=0; i< queue_size; ++i)
	{
		Vehicle *vh = seg4->queue_veh.front();
		seg4->queue_veh.pop();
		// check vh can go to next seg?
		vh->position += dt*speed_move_in_queue;
		if(vh->position > seg4->seg_length)
		{
			// out
			delete vh;
		}
		else
		{
			// if can not push to tmp queue
			seg4->queue_veh.push(vh);
		}
	}
	// calculate queue size
	Vehicle *last_vh = seg4->queue_veh.back();
	seg4->queue_length = seg4->seg_length - last_vh->position;
	// move queue
	size_t move_queue_size = seg4->move_veh.size();
	for(int i=0; i< move_queue_size; ++i)
	{
		Vehicle *vh = seg4->move_veh.front();
		seg4->move_veh.pop();
		// calcu vh position , check if enter the queue
		vh->position += dt*speed_moveing;
		if(vh->position > seg4->seg_length - seg4->queue_length)
		{
			vh->position = seg4->seg_length - seg4->queue_length - vh->length;
			seg4->queue_length = seg4->seg_length - vh->position;
		}
		else
		{
			// still in moving queue
			seg4->move_veh.push(vh);
		}
	}

	// seg 5
	 size_t queue_size = seg5->queue_veh.size();
		for(int i=0; i< queue_size; ++i)
		{
			Vehicle *vh = seg5->queue_veh.front();
			seg5->queue_veh.pop();
			// check vh can go to next seg?
			vh->position += dt*speed_move_in_queue;
			if(vh->position > seg5->seg_length)
			{
				// out
				delete vh;
			}
			else
			{
				// if can not push to tmp queue
				seg5->queue_veh.push(vh);
			}
		}
		// calculate queue size
		Vehicle *last_vh = seg5->queue_veh.back();
		seg5->queue_length = seg5->seg_length - last_vh->position;
		// move queue
		size_t move_queue_size = seg5->move_veh.size();
		for(int i=0; i< move_queue_size; ++i)
		{
			Vehicle *vh = seg5->move_veh.front();
			seg5->move_veh.pop();
			// calcu vh position , check if enter the queue
			vh->position += dt*speed_moveing;
			if(vh->position > seg5->seg_length - seg5->queue_length)
			{
				vh->position = seg5->seg_length - seg5->queue_length - vh->length;
				seg5->queue_length = seg5->seg_length - vh->position;
			}
			else
			{
				// still in moving queue
				seg5->move_veh.push(vh);
			}
		}
//	seg5->update_time_dynamit_framework();
//	// seg 3
//	seg3->update_time_dynamit_framework();
//	// seg 1
//	seg1->update_time_dynamit_framework();
//	// seg 2
//	seg2->update_time_dynamit_framework();

	// add vh to network


}

