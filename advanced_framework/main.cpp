/*
 * Purpose: A Test-bed for The New Framework
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#include <iostream>

#include "../share/TestBedSettings.h"

using namespace std;

static int current_time_step = 0;

/*
 * Functions
 */
int init_simulation();
int simulate_one_time_step();
int close_simulation();

int main() {

	init_simulation();

	for (current_time_step = TestBedSettings::start_time_step; current_time_step < TestBedSettings::end_time_step; current_time_step += TestBedSettings::time_step_unit) {
		simulate_one_time_step();
		std::cout << "tick: " << current_time_step << std::endl;
	}

	close_simulation();

	std::cout << "simulation exit successfully" << std::endl;
	return 0;
}

int init_simulation()
{
	std::cout << "init_simulation: " << std::endl;
	return 1;
}

int simulate_one_time_step()
{
	std::cout << "simulate_one_time_step: " << std::endl;
	return 1;
}

int close_simulation()
{
	std::cout << "close_simulation: " << std::endl;
	return 1;
}

