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
	seg1 = new Segment(); seg1->seg_id = 1;
	seg2 = new Segment(); seg2->seg_id = 2;
	seg3 = new Segment(); seg3->seg_id = 3;
	seg4 = new Segment(); seg4->seg_id = 4;
	seg5 = new Segment(); seg5->seg_id = 5;
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
			vh->position -= dt*speed_move_in_queue;
			seg4->queue_veh.push(vh);
		}
	}
	// calculate queue size
	if(!seg4->queue_veh.empty()) // at least on vh in queue
	{
		Vehicle *last_vh = seg4->queue_veh.back();
		seg4->queue_length = seg4->seg_length - last_vh->position;
	}
	else
	{
		seg4->queue_length = 0;
	}
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
	// calcu free space
	if(seg4->move_veh.size()>0) // has at least one vh
	{
		seg4->free_space = seg4->seg_length - seg4->move_veh.back()->position;
	}
	else // no vh in moving queue
	{
		seg4->free_space = seg4->seg_length - seg4->queue_length;
	}

	// seg 5
	 size_t queue_size5 = seg5->queue_veh.size();
		for(int i=0; i< queue_size5; ++i)
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
				// if can not ,keep in queue and position changed
//				vh->position -= dt*speed_move_in_queue;
				seg5->queue_veh.push(vh);
			}
		}
		// calculate queue size
			if(!seg5->queue_veh.empty()) // at least on vh in queue
			{
				Vehicle *last_vh = seg5->queue_veh.back();
				seg5->queue_length = seg5->seg_length - last_vh->position;
			}
			else
			{
				seg5->queue_length = 0;
			}
		// move queue
		size_t move_queue_size5 = seg5->move_veh.size();
		for(int i=0; i< move_queue_size5; ++i)
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
		// calcu free space
			if(seg5->move_veh.size()>0) // has at least one vh
			{
				seg5->free_space = seg5->seg_length - seg5->move_veh.back()->position;
			}
			else // no vh in moving queue
			{
				seg5->free_space = seg5->seg_length - seg5->queue_length;
			}

	// seg 3
	size_t seg3_queue_size = seg3->queue_veh.size();
	for(int i=0; i< seg3_queue_size; ++i)
	{
		Vehicle *vh = seg3->queue_veh.front();
		seg3->queue_veh.pop();
		// check vh can go to next seg?
		vh->position += dt*speed_move_in_queue;
		if(vh->position > seg3->seg_length)
		{
			// move to next seg
			if(vh->densition_node_id == 5) // move to seg 4
			{
				// check seg4's moving queue
				if(seg4->free_space >vh->length) // moving queue has some space
				{
					vh->position = vh->position - seg3->seg_length;
					seg4->move_veh.push(vh);
					seg4->free_space = seg4->free_space - vh->length;
				}
				else // can not enter seg4, keep in current queue
				{
					seg3->queue_veh.push(vh);
				}
			}
			else  // move to seg 5
			{
				// check seg5's moving queue
				if(seg5->free_space >vh->length) // moving queue has some space
				{
					vh->position = vh->position - seg5->seg_length;
					seg5->move_veh.push(vh);
					seg5->free_space = seg4->free_space - vh->length;
				}
				else // can not enter seg5, keep in current queue
				{
					seg3->queue_veh.push(vh);
				}
			}
		}// if vh->position > seg3->seg_length
		else
		{
			vh->position -= dt*speed_move_in_queue;
			seg3->queue_veh.push(vh);
			break; // no need check rest vh
		}
	}// queue
	// moving queue
	size_t move_queue_size3 = seg3->move_veh.size();
	for(int i=0; i< move_queue_size3; ++i)
	{
		Vehicle *vh = seg3->move_veh.front();
		seg3->move_veh.pop();
		// calcu vh position , check if enter the queue
		vh->position += dt*speed_moveing;
		if(vh->position > seg3->seg_length - seg3->queue_length)
		{
			vh->position = seg3->seg_length - seg3->queue_length - vh->length;
			seg3->queue_length = seg3->seg_length - vh->position;
		}
		else
		{
			// still in moving queue
			seg3->move_veh.push(vh);
		}
	}
	// calcu free space
		if(seg3->move_veh.size()>0) // has at least one vh
		{
			seg3->free_space = seg3->seg_length - seg3->move_veh.back()->position;
		}
		else // no vh in moving queue
		{
			seg3->free_space = seg3->seg_length - seg3->queue_length;
		}

	// seg 1
		size_t seg1_queue_size = seg1->queue_veh.size();
			for(int i=0; i< seg1_queue_size; ++i)
			{
				Vehicle *vh = seg1->queue_veh.front();
				seg1->queue_veh.pop();
				// check vh can go to next seg, seg3
				vh->position += dt*speed_move_in_queue;
				if(vh->position > seg1->seg_length)
				{

					// check seg3's moving queue
					if(seg3->free_space >vh->length) // moving queue has some space
					{
						vh->position = vh->position - seg1->seg_length;
						seg3->move_veh.push(vh);
						seg3->free_space = seg3->free_space - vh->length;
					}
					else // can not enter seg3, keep in current queue , and not update position
					{
						vh->position -= dt*speed_move_in_queue;
						seg1->queue_veh.push(vh);
						break; // no need check rest
					}

				}// if vh->position > seg3->seg_length
				else // keep in the queue, but position updated
				{
					seg1->queue_veh.push(vh);
				}
			}// queue
			// moving queue
			size_t move_queue_size1 = seg1->move_veh.size();
			for(int i=0; i< move_queue_size1; ++i)
			{
				Vehicle *vh = seg1->move_veh.front();
				seg1->move_veh.pop();
				// calcu vh position , check if enter the queue
				vh->position += dt*speed_moveing;
				if(vh->position > seg1->seg_length - seg1->queue_length)
				{
					vh->position = seg1->seg_length - seg1->queue_length - vh->length;
					seg1->queue_length = seg1->seg_length - vh->position;
				}
				else
				{
					// still in moving queue
					seg1->move_veh.push(vh);
				}
			}
			// calcu free space
				if(seg1->move_veh.size()>0) // has at least one vh
				{
					seg1->free_space = seg1->seg_length - seg1->move_veh.back()->position;
				}
				else // no vh in moving queue
				{
					seg1->free_space = seg1->seg_length - seg1->queue_length;
				}
	// seg 2
				size_t seg2_queue_size = seg2->queue_veh.size();
							for(int i=0; i< seg2_queue_size; ++i)
							{
								Vehicle *vh = seg2->queue_veh.front();
								seg2->queue_veh.pop();
								// check vh can go to next seg, seg3
								vh->position += dt*speed_move_in_queue;
								if(vh->position > seg2->seg_length)
								{

									// check seg3's moving queue
									if(seg3->free_space >vh->length) // seg3 moving queue has some space
									{
										vh->position = vh->position - seg2->seg_length;
										seg3->move_veh.push(vh);
										seg3->free_space = seg3->free_space - vh->length;
									}
									else // can not enter seg3, keep in current queue , and not update position
									{
										vh->position -= dt*speed_move_in_queue;
										seg2->queue_veh.push(vh);
										break; // no need check rest
									}

								}// if vh->position > seg3->seg_length
								else // keep in the queue, but position updated
								{
									seg2->queue_veh.push(vh);
								}
							}// queue
							// moving queue
							size_t move_queue_size2 = seg2->move_veh.size();
							for(int i=0; i< move_queue_size2; ++i)
							{
								Vehicle *vh = seg2->move_veh.front();
								seg2->move_veh.pop();
								// calcu vh position , check if enter the queue
								vh->position += dt*speed_moveing;
								if(vh->position > seg2->seg_length - seg2->queue_length)
								{
									vh->position = seg2->seg_length - seg2->queue_length - vh->length;
									seg2->queue_length = seg2->seg_length - vh->position;
								}
								else
								{
									// still in moving queue
									seg2->move_veh.push(vh);
								}
							}
							// calcu free space
								if(seg2->move_veh.size()>0) // has at least one vh
								{
									seg2->free_space = seg2->seg_length - seg2->move_veh.back()->position;
								}
								else // no vh in moving queue
								{
									seg2->free_space = seg2->seg_length - seg2->queue_length;
								}
	// add vh to network


}

