#include "Segment.h"

#include <iostream>

#include "TestBedSettings.h"
#include "Lane.h"
#include "GeneralTool.h"
#include "RoadNetwork.h"

Segment::Segment() {
	seg_id = 0;
	seg_length = TestBedSettings::seg_length;
	free_space = 0.0;
	hash_table_speed = new Segment_Speed_Hash();

	who_can_pass_time = 0;
	who_can_pass_offset = 0;
}

Segment::~Segment() {
	if (hash_table_speed) {
		delete hash_table_speed;
	}
}

/**
 * Step 1: Update Speed
 * Step 2: Update Can Pass Time
 * Step 3: Pass Some Vehicles to Next Segment
 * Step 4: Update Queue
 * Step 5: Update Empty Space
 */
void Segment::xy_update_time(int current_time_step) {
	//according to the segment ID

//Step 1: Update Speed
	//only 1 lane, so hard coded
	double moving_length = this->seg_length - this->all_lanes[0]->queue_status->current_queue_length;
	double moving_density = this->all_lanes[0]->in_moving_vehicles / moving_length;
	double speed = GeneralTool::calculate_speed_based_on_density(moving_density);
	this->hash_table_speed->add_time_speed(current_time_step, speed);

	if (TestBedSettings::debug_mode)
		std::cout << "seg " << this->seg_id << " speed:" << speed << std::endl;

//Step 2: Update Can Pass Time
	who_can_pass_offset += speed * TestBedSettings::time_step_unit;
	while (who_can_pass_offset > this->seg_length) {
		who_can_pass_time++;

		//
//		assert(who_can_pass_time <= current_time_step);
		who_can_pass_offset -= this->hash_table_speed->get_time_speed(who_can_pass_time);
	}

//Step 3: Pass Some Vehicles to Next Segment
	xy_move_agents_to_next_segment(current_time_step);

//Step 4: Update Queue


//Step 5: Update Empty Space
	int last_time_step = this->all_lanes[0]->vehiclePackageQueue.back()->joinTime;
	double total_empty_space = 0;
	for (int i = last_time_step; i <= current_time_step; i++) {
		total_empty_space += TestBedSettings::time_step_unit * this->hash_table_speed->get_time_speed(i);
	}

	total_empty_space -= this->all_lanes[0]->vehiclePackageQueue.back()->inner_vehicles.size() * TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;
	assert(total_empty_space > 0);

	this->all_lanes[0]->empty_space = total_empty_space;
}

void Segment::xy_move_agents_to_next_segment(int current_time_step) {
	int out_capacity = this->all_lanes[0]->outside_capacity_per_time_step_unit;

	if (seg_id == 4 || seg_id == 5) {
		while (out_capacity > 0 && this->all_lanes[0]->vehiclePackageQueue.empty() == false) {
			VehiclePackage* the_last = this->all_lanes[0]->vehiclePackageQueue.front();
			if (the_last->joinTime > who_can_pass_time) {
				//cannot pass the segment
				//leave the segment
				break;
			}

			//all can leave
			if (the_last->vehicle_size <= out_capacity) {
				/*
				 * TBA
				 * not process queue length now
				 */

				//release memory
				for (std::vector<Vehicle *>::iterator it = the_last->inner_vehicles.begin(); it != the_last->inner_vehicles.end(); ++it) {
					/* std::cout << *it; ... */
					if (*it)
						delete (*it);
				}

//				if(this->all_lanes[0]->queue_status->end_queue_VehiclePackage == the_last)
//					this->all_lanes[0]->queue_status->end_queue_VehiclePackage = NULL;

				if (the_last)
					delete the_last;

				//update capacity
				out_capacity -= the_last->vehicle_size;
			}
			//part can leave
			else {

				int start_output = 0;

				for (std::vector<Vehicle *>::iterator it = the_last->inner_vehicles.begin(); start_output < out_capacity && it != the_last->inner_vehicles.end(); ++it) {
					/* std::cout << *it; ... */
					if (*it) {
						delete (*it);
						the_last->inner_vehicles.erase(it);
					}

					start_output++;
				}

				the_last->vehicle_size -= out_capacity;

				//update capacity & exit the while loop
				out_capacity = 0;
			}
		}
	}
	else if (seg_id == 3) {
		while (out_capacity > 0 && this->all_lanes[0]->vehiclePackageQueue.empty() == false) {
			VehiclePackage* the_last = this->all_lanes[0]->vehiclePackageQueue.front();
			if (the_last->joinTime > who_can_pass_time) {
				//cannot pass the segment
				//leave the segment
				break;
			}

			for (std::vector<Vehicle *>::iterator it = the_last->inner_vehicles.begin(); out_capacity > 0 && it != the_last->inner_vehicles.end(); ++it) {
				/* std::cout << *it; ... */
				Vehicle * the_vehicle = (*it);
				if (the_vehicle->densition_node_id == 5) {
					Lane* go_to = RoadNetwork::instance().seg4->all_lanes[0];
					if (go_to->inside_capacity_per_time_step_unit > 0 && go_to->empty_space > TestBedSettings::VEHICLE_OCCUPANCY_LENGTH) {
						go_to->inside_capacity_per_time_step_unit--;
						go_to->empty_space -= TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;
					}
					else {
						//no more space, so stop here
						break;
					}

					/*
					 * TBA
					 * not process queue length now
					 */

					//move to next Segment
					VehiclePackage* the_back = go_to->vehiclePackageQueue.back();
					if (the_back == NULL || the_back->joinTime != current_time_step) {
						the_back = new VehiclePackage();
						go_to->vehiclePackageQueue.push(the_back);
					}

					the_back->inner_vehicles.push_back(*it);
					the_back->vehicle_size++;
				}
				else if (the_vehicle->densition_node_id == 6) {
					Lane* go_to = RoadNetwork::instance().seg5->all_lanes[0];
					if (go_to->inside_capacity_per_time_step_unit > 0 && go_to->empty_space > TestBedSettings::VEHICLE_OCCUPANCY_LENGTH) {
						go_to->inside_capacity_per_time_step_unit--;
						go_to->empty_space -= TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;
					}
					else {
						//no more space, so stop here
						break;
					}

					/*
					 * TBA
					 * not process queue length now
					 */

					//move to next Segment
					VehiclePackage* the_back = go_to->vehiclePackageQueue.back();
					if (the_back == NULL || the_back->joinTime != current_time_step) {
						the_back = new VehiclePackage();
						go_to->vehiclePackageQueue.push(the_back);
					}

					the_back->inner_vehicles.push_back(*it);
					the_back->vehicle_size++;
				}
				else {
					std::cout << "Error: Not Existing Des When process seg 3" << std::endl;
				}

				the_last->inner_vehicles.erase(it);
			}
		}
	}
	else if (seg_id == 1 || seg_id == 2) {
		std::cout << "Error: should not use the function to process seg 1 and seg 2." << std::endl;
	}
}

Vehicle* Segment::xy_find_the_next_vehicle_package() {
	int size_seg_1 = RoadNetwork::instance().seg1->all_lanes[0]->vehiclePackageQueue.size();
	int size_seg_2 = RoadNetwork::instance().seg2->all_lanes[0]->vehiclePackageQueue.size();
	bool can_pass_1 = false;
	bool can_pass_2 = false;

	if (size_seg_1 > 0 && RoadNetwork::instance().seg1->all_lanes[0]->vehiclePackageQueue.front()->joinTime <= RoadNetwork::instance().seg1->who_can_pass_time) {
		can_pass_1 = true;
	}
	if (size_seg_2 > 0 && RoadNetwork::instance().seg2->all_lanes[0]->vehiclePackageQueue.front()->joinTime <= RoadNetwork::instance().seg2->who_can_pass_time) {
		can_pass_2 = true;
	}

	if (can_pass_1 && can_pass_2) {
		if ((RoadNetwork::instance().seg1->all_lanes[0]->vehiclePackageQueue.front()->in_Queue_Time) < (RoadNetwork::instance().seg2->all_lanes[0]->vehiclePackageQueue.front()->in_Queue_Time)) {
			VehiclePackage* the_one = RoadNetwork::instance().seg1->all_lanes[0]->vehiclePackageQueue.front();
			if (the_one->inner_vehicles.size() > 1) {
				the_one->vehicle_size--;
				std::vector<Vehicle *>::iterator it = the_one->inner_vehicles.end() - 1;
				Vehicle* one = (*it);
				the_one->inner_vehicles.erase(it);

				return one;
			}
			else {
				std::vector<Vehicle *>::iterator it = the_one->inner_vehicles.end() - 1;
				Vehicle* one = (*it);

				if (the_one)
					delete the_one;

				RoadNetwork::instance().seg1->all_lanes[0]->vehiclePackageQueue.pop();

				return one;
			}
		}
		else {
			VehiclePackage* the_one = RoadNetwork::instance().seg2->all_lanes[0]->vehiclePackageQueue.front();
			if (the_one->inner_vehicles.size() > 1) {
				the_one->vehicle_size--;
				std::vector<Vehicle *>::iterator it = the_one->inner_vehicles.end() - 1;
				Vehicle* one = (*it);
				the_one->inner_vehicles.erase(it);

				return one;
			}
			else {
				std::vector<Vehicle *>::iterator it = the_one->inner_vehicles.end() - 1;
				Vehicle* one = (*it);

				if (the_one)
					delete the_one;

				RoadNetwork::instance().seg2->all_lanes[0]->vehiclePackageQueue.pop();

				return one;
			}
		}
	}

	if (can_pass_1) {
		VehiclePackage* the_one = RoadNetwork::instance().seg1->all_lanes[0]->vehiclePackageQueue.front();
		if (the_one->inner_vehicles.size() > 1) {
			the_one->vehicle_size--;
			std::vector<Vehicle *>::iterator it = the_one->inner_vehicles.end() - 1;
			Vehicle* one = (*it);
			the_one->inner_vehicles.erase(it);

			return one;
		}
		else {
			std::vector<Vehicle *>::iterator it = the_one->inner_vehicles.end() - 1;
			Vehicle* one = (*it);

			if (the_one)
				delete the_one;

			RoadNetwork::instance().seg1->all_lanes[0]->vehiclePackageQueue.pop();

			return one;
		}
	}

	if (can_pass_2) {
		VehiclePackage* the_one = RoadNetwork::instance().seg2->all_lanes[0]->vehiclePackageQueue.front();
		if (the_one->inner_vehicles.size() > 1) {
			the_one->vehicle_size--;
			std::vector<Vehicle *>::iterator it = the_one->inner_vehicles.end() - 1;
			Vehicle* one = (*it);
			the_one->inner_vehicles.erase(it);

			return one;
		}
		else {
			std::vector<Vehicle *>::iterator it = the_one->inner_vehicles.end() - 1;
			Vehicle* one = (*it);

			if (the_one)
				delete the_one;

			RoadNetwork::instance().seg2->all_lanes[0]->vehiclePackageQueue.pop();

			return one;
		}
	}

	return NULL;
}

void Segment::xy_simulate_seg1_2_together(int current_time_step) {
	//Step 1: Update Speed & Step 2
	//only 1 lane, so hard coded
	{
		double moving_length = RoadNetwork::instance().seg1->seg_length - RoadNetwork::instance().seg1->all_lanes[0]->queue_status->current_queue_length;
		double moving_density = RoadNetwork::instance().seg1->all_lanes[0]->in_moving_vehicles / moving_length;
		double speed = GeneralTool::calculate_speed_based_on_density(moving_density);
		RoadNetwork::instance().seg1->hash_table_speed->add_time_speed(current_time_step, speed);

		if (TestBedSettings::debug_mode)
			std::cout << "seg 1 speed:" << speed << std::endl;

		//Step 2: Update Can Pass Time
		RoadNetwork::instance().seg1->who_can_pass_offset += speed * TestBedSettings::time_step_unit;
		while (RoadNetwork::instance().seg1->who_can_pass_offset > RoadNetwork::instance().seg1->seg_length) {
			RoadNetwork::instance().seg1->who_can_pass_time++;

			//
			assert(RoadNetwork::instance().seg1->who_can_pass_time <= current_time_step);
			RoadNetwork::instance().seg1->who_can_pass_offset -= RoadNetwork::instance().seg1->hash_table_speed->get_time_speed(RoadNetwork::instance().seg1->who_can_pass_time);
		}
	}

	{
		double moving_length = RoadNetwork::instance().seg2->seg_length - RoadNetwork::instance().seg2->all_lanes[0]->queue_status->current_queue_length;
		double moving_density = RoadNetwork::instance().seg2->all_lanes[0]->in_moving_vehicles / moving_length;
		double speed = GeneralTool::calculate_speed_based_on_density(moving_density);
		RoadNetwork::instance().seg2->hash_table_speed->add_time_speed(current_time_step, speed);

		if (TestBedSettings::debug_mode)
			std::cout << "seg 2 speed:" << speed << std::endl;

		//Step 2: Update Can Pass Time
		RoadNetwork::instance().seg2->who_can_pass_offset += speed * TestBedSettings::time_step_unit;
		while (RoadNetwork::instance().seg2->who_can_pass_offset > RoadNetwork::instance().seg2->seg_length) {
			RoadNetwork::instance().seg2->who_can_pass_time++;

			//
			assert(RoadNetwork::instance().seg2->who_can_pass_time <= current_time_step);
			RoadNetwork::instance().seg2->who_can_pass_offset -= RoadNetwork::instance().seg2->hash_table_speed->get_time_speed(RoadNetwork::instance().seg2->who_can_pass_time);
		}
	}

	//Step 3: Move Vehicle To Next Segment
	int temp_input_capacity = RoadNetwork::instance().seg3->all_lanes[0]->inside_capacity_per_time_step_unit;
	double temp_empty_space = RoadNetwork::instance().seg3->all_lanes[0]->empty_space;

	while (temp_input_capacity > 0 && temp_empty_space > TestBedSettings::VEHICLE_OCCUPANCY_LENGTH) {
		Vehicle* the_next_one = Segment::xy_find_the_next_vehicle_package();
		if (the_next_one == NULL)
			break;

		Lane* go_to = RoadNetwork::instance().seg3->all_lanes[0];
		temp_input_capacity--;
		temp_empty_space -= TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;

		//move to next Segment
		VehiclePackage* the_back = go_to->vehiclePackageQueue.back();
		if (the_back == NULL || the_back->joinTime != current_time_step) {
			the_back = new VehiclePackage();
			go_to->vehiclePackageQueue.push(the_back);
		}

		the_back->inner_vehicles.push_back(the_next_one);
		the_back->vehicle_size++;
	}

	//Step 4: Update Queue Status

	//Step 5: Update Empty Space

}

void Segment::reset_simulation_per_time_step() {
	for (std::vector<Lane*>::iterator it = all_lanes.begin(); it != all_lanes.end(); ++it) {
		/* std::cout << *it; ... */
		(*it)->reset_input_output_capacity();
	}
}

void Segment::xy_add_a_new_vehicle_in_segment(int lane_id) {

}
