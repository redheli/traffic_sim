//============================================================================
// Name        : traffic_sim.cpp
// Author      : Max
// Version     :
// Copyright   : Your copyright notice
// Description : Traffic Simulator in C++, Ansi-style
//============================================================================

#include <iostream>
#include "../share/Segment.h"
using namespace std;

int simulationTime = 100;

int main() {
	Segment *s = new Segment;
	for(int i=0;i<simulationTime; ++i)
	{
		std::cout<<"tick: "<<i<<std::endl;
	}
	std::cout<<"simulation exit successfully"<<std::endl;
	return 0;
}
