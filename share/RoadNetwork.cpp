/*
 * RoadNetwork.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#include "RoadNetwork.h"
#include <stddef.h>

//Signton

RoadNetwork RoadNetwork::instance_;

RoadNetwork::RoadNetwork()
{
	seg1 = NULL;
	seg2 = NULL;
	seg3 = NULL;
	seg4 = NULL;
	seg5 = NULL;
}

RoadNetwork::~RoadNetwork()
{

}

/*
 * TBA
 * Need to add more in the road network
 */
void RoadNetwork::init_network()
{
	seg1 = new Segment();
	seg2 = new Segment();
	seg3 = new Segment();
	seg4 = new Segment();
	seg5 = new Segment();
}
