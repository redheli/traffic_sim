//============================================================================
// Name        : traffic_sim.cpp
// Author      : Max
// Version     :
// Copyright   : Your copyright notice
// Description : Traffic Simulator in C++, Ansi-style
//============================================================================

#include <iostream>
#include "../share/Segment.h"
#include "../share/RoadNetwork.h"

using namespace std;

int simulationTime = 100;
double dt = 0.1; // interval second

// start node, end node, start time tick, number
int OD_1[] = {5,4,0,10};

//
std::vector<Vehicle*> seg_5;
std::vector<Vehicle*> seg_4;
std::vector<Vehicle*> seg_3;
std::vector<Vehicle*> seg_2;
std::vector<Vehicle*> seg_1;

int main() {
	Segment *s = new Segment;

	for(int i=0;i<simulationTime; ++i)
	{
		// update road network and vehicles
		RoadNetwork::instance().update();

		std::cout<<"tick: "<<i<<std::endl;
	}
	std::cout<<"simulation exit successfully"<<std::endl;
	return 0;
}
void makeVehicles()
{

}
