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
#include "../share/TimeTools.h"

using namespace std;

int simulationTime = 10000;
double dt = 0.1; // interval second

// start node, end node, start time tick, number
int OD_1[] = { 5, 4, 0, 10 };
int fre = 4;

void makeVehicles(int time);

//
std::vector<Vehicle*> seg_5;
std::vector<Vehicle*> seg_4;
std::vector<Vehicle*> seg_3;
std::vector<Vehicle*> seg_2;
std::vector<Vehicle*> seg_1;

int main() {
	Segment *s = new Segment;

		TimeTools profile;
		profile.start_profiling();

	for (int i = 0; i < simulationTime; ++i) {
		// update road network and vehicles
		RoadNetwork::instance().update(dt);
		makeVehicles(i);

		std::cout << "tick: " << i << std::endl;
	}

		profile.end_profiling();
		profile.output();

	std::cout << "simulation exit successfully" << std::endl;
	return 0;
}
void makeVehicles(int time) {
	if (time % fre == 0) {
		Vehicle* one = new Vehicle();
		one->densition_node_id = 5;
		one->position = 0;
		RoadNetwork::instance().seg1->move_veh.push(one);

		Vehicle* two = new Vehicle();
		two->densition_node_id = 6;
		two->position = 0;
		RoadNetwork::instance().seg2->move_veh.push(two);
	}
}
