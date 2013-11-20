#include "Segment.h"

#include <iostream>

#include "TestBedSettings.h"
#include "Lane.h"
#include "GeneralTool.h"
#include "RoadNetwork.h"

Segment::Segment() {
	seg_id = 0;
	seg_length = TestBedSettings::seg_length;
	hash_table_speed = new Segment_Speed_Hash();

	who_can_pass_time = TestBedSettings::start_time_step - TestBedSettings::time_step_unit;
	who_can_pass_offset = 0;

//	last_remove_time_step = TestBedSettings::start_time_step - TestBedSettings::time_step_unit;
}

Segment::~Segment() {
	if (hash_table_speed) {
		delete hash_table_speed;
	}

	if (this->all_lanes[0]) {
		delete this->all_lanes[0];
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
//	double moving_length = this->seg_length - this->all_lanes[0]->queue_status->current_queue_length;
//	double moving_density = this->all_lanes[0]->queue_status->in_moving_vehicles / moving_length;

	double moving_density = this->all_lanes[0]->queue_status->total_onside_vehicles / this->seg_length;

	double speed = GeneralTool::calculate_speed_based_on_density(moving_density);
	this->hash_table_speed->add_time_speed(current_time_step, speed);

	if (current_time_step % TestBedSettings::remove_speed_frequency == 0)
		this->xy_clear_old_speeds();

	if (TestBedSettings::debug_mode)
		std::cout << "seg_ID:" << this->seg_id << "	,speed:" << speed << "	,moving:" << this->all_lanes[0]->queue_status->in_moving_vehicles << "	,all:"
				<< this->all_lanes[0]->queue_status->total_onside_vehicles << "	,queue:" << this->all_lanes[0]->queue_status->current_queue_length << "	,empty space:"
				<< this->all_lanes[0]->empty_space << std::endl;

//Step 2: Update Can Pass Time
	who_can_pass_offset += speed * TestBedSettings::time_step_unit;
	this->all_lanes[0]->queue_status->the_accumulated_offset += speed * TestBedSettings::time_step_unit;

	if (this->seg_id == 3 && this->all_lanes[0]->queue_status->current_queue_length > 0) {
		std::cout << "this->all_lanes[0]->queue_length:" << this->all_lanes[0]->queue_status->current_queue_length << std::endl;
	}

	while (who_can_pass_offset > this->seg_length) {
		who_can_pass_time += TestBedSettings::time_step_unit;

		//add queue length
		this->all_lanes[0]->update_queue_status_when_moving_segment(who_can_pass_time);

		who_can_pass_offset -= this->hash_table_speed->get_time_speed(who_can_pass_time) * TestBedSettings::time_step_unit;
	}

//	if(this->seg_id == 3)
//	{
//		std::cout << "this->ccc:" << this->all_lanes[0]->queue_status->current_queue_length << std::endl;
//	}

//	if (TestBedSettings::debug_mode)
//		std::cout << "seg " << this->seg_id << ",who_can_pass_offset:" << who_can_pass_offset << ",who_can_pass_time:" << who_can_pass_time << std::endl;

//Step 3: Pass Some Vehicles to Next Segment
	xy_move_agents_to_next_segment(current_time_step);

//Step 4: Update Queue
	this->all_lanes[0]->update_queue_status_after_moving_segment(who_can_pass_time);

//Step 5: Update Empty Space
	if (this->all_lanes[0]->vehiclePackageQueue.empty()) {
		this->all_lanes[0]->empty_space = this->seg_length;
	}
	else {
		int last_time_step = this->all_lanes[0]->vehiclePackageQueue.back()->joinTime;
		double total_empty_space = 0;
		for (int i = last_time_step + TestBedSettings::time_step_unit; i <= current_time_step; i += TestBedSettings::time_step_unit) {
			total_empty_space += TestBedSettings::time_step_unit * this->hash_table_speed->get_time_speed(i);
		}

//		total_empty_space -= this->all_lanes[0]->vehiclePackageQueue.back()->inner_vehicles.size() * TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;

		//queue feedback
		if (total_empty_space > (this->seg_length - this->all_lanes[0]->queue_status->current_queue_length)) {
			total_empty_space = this->seg_length - this->all_lanes[0]->queue_status->current_queue_length;
		}

		assert(total_empty_space >= 0);

		this->all_lanes[0]->empty_space = total_empty_space;
	}

#ifdef USE_DEBUY_CODE
	if(TestBedSettings::debug_mode)
	{
		this->debug();
	}
#endif
}

void Segment::xy_move_agents_to_next_segment(int current_time_step) {
	int out_capacity = this->all_lanes[0]->outside_capacity_per_time_step_unit;

//	static int gt5 = 0;
//	static int gt6 = 0;
	int move_in = 0;

	if (seg_id == 4 || seg_id == 5) {
		while (out_capacity > 0 && this->all_lanes[0]->vehiclePackageQueue.empty() == false) {
			VehiclePackage* the_last = this->all_lanes[0]->vehiclePackageQueue.front();
			if (the_last->joinTime > who_can_pass_time) {
				//cannot pass the segment
				//leave the segment
				break;
			}

//			std::cout << "the_last->vehicle_size:" << the_last->vehicle_size << std::endl;

			//all can leave
			if (the_last->vehicle_size <= out_capacity) {
				/*
				 * TBA
				 * process queue length now
				 */
				this->all_lanes[0]->queue_status->total_onside_vehicles -= the_last->vehicle_size;
				this->all_lanes[0]->queue_status->in_queue_vehicles -= the_last->vehicle_size;
				this->all_lanes[0]->queue_status->current_queue_length -= the_last->vehicle_size * TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;
				if (this->all_lanes[0]->queue_status->in_queue_vehicles <= 0)
					this->all_lanes[0]->queue_status->end_queue_VehiclePackage = NULL;

				//release memory
				for (std::vector<Vehicle *>::iterator it = the_last->inner_vehicles.begin(); it != the_last->inner_vehicles.end(); ++it) {
					/* std::cout << *it; ... */
					Vehicle * one = (*it);
					if (one)
						delete (one);
				}

				//update capacity
				out_capacity -= the_last->vehicle_size;

				//remove from the list
				this->all_lanes[0]->vehiclePackageQueue.pop();

#ifdef USE_DEBUY_CODE
				if(TestBedSettings::debug_mode)
				{
					this->all_lanes[0]->count_passing_vehicle += the_last->vehicle_size;
				}
#endif

				if (the_last)
					delete the_last;
			}
			//part can leave
			else {

				int start_output = 0;

				for (std::vector<Vehicle *>::iterator it = the_last->inner_vehicles.begin(); start_output < out_capacity && it != the_last->inner_vehicles.end();) {
					/* std::cout << *it; ... */
					Vehicle * one = (*it);
					if (one) {
						delete (one);
						it = the_last->inner_vehicles.erase(it);
					}

					start_output++;

#ifdef USE_DEBUY_CODE
					if(TestBedSettings::debug_mode)
					{
						this->all_lanes[0]->count_passing_vehicle += the_last->vehicle_size;
					}
#endif
				}

				the_last->vehicle_size -= out_capacity;

				this->all_lanes[0]->queue_status->total_onside_vehicles -= out_capacity;
				this->all_lanes[0]->queue_status->in_queue_vehicles -= out_capacity;
				this->all_lanes[0]->queue_status->current_queue_length -= out_capacity * TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;
				if (this->all_lanes[0]->queue_status->in_queue_vehicles <= 0)
					this->all_lanes[0]->queue_status->end_queue_VehiclePackage = NULL;

				//update capacity & exit the while loop
				out_capacity = 0;
			}
		}
	}
	else if (seg_id == 3) {
		bool can_stop = false;

		while (can_stop == false && out_capacity > 0 && this->all_lanes[0]->vehiclePackageQueue.empty() == false) {

//			std::cout << "this->all_lanes[0]->vehiclePackageQueue:" << this->all_lanes[0]->vehiclePackageQueue.package_size << std::endl;
//			std::cout << "can_stop:" << can_stop << std::endl;
//			std::cout << "out_capacity:" << out_capacity << std::endl;

			VehiclePackage* the_last = this->all_lanes[0]->vehiclePackageQueue.front();
			if (the_last->joinTime > who_can_pass_time) {
				//cannot pass the segment
				//leave the segment

				break;
			}

//			std::cout << "can_stop:" << can_stop << std::endl;

			for (std::vector<Vehicle *>::iterator it = the_last->inner_vehicles.begin(); out_capacity > 0 && it != the_last->inner_vehicles.end();) {
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
						can_stop = true;
						break;
					}

					/*
					 * TBA
					 * not process queue length now
					 */

					go_to->queue_status->total_onside_vehicles++;
					go_to->queue_status->in_moving_vehicles++;

					out_capacity--;

					//move to next Segment
					VehiclePackage* the_back = NULL;
					if (go_to->vehiclePackageQueue.empty() || go_to->vehiclePackageQueue.back()->joinTime != current_time_step) {
						the_back = new VehiclePackage();
						the_back->joinTime = current_time_step;
						go_to->vehiclePackageQueue.push_back(the_back);
					}
					else {
						the_back = go_to->vehiclePackageQueue.back();
					}

					the_back->inner_vehicles.push_back(*it);
					the_back->vehicle_size++;

					if (this->seg_id == 3) {
//						std::cout << "one go to 5:" << gt5 << std::endl;
//						gt5++;
						move_in ++;
					}
				}
				else if (the_vehicle->densition_node_id == 6) {
					Lane* go_to = RoadNetwork::instance().seg5->all_lanes[0];
					if (go_to->inside_capacity_per_time_step_unit > 0 && go_to->empty_space > TestBedSettings::VEHICLE_OCCUPANCY_LENGTH) {
						go_to->inside_capacity_per_time_step_unit--;
						go_to->empty_space -= TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;
					}
					else {
						//no more space, so stop here
						can_stop = true;
						break;
					}

					/*
					 * TBA
					 * not process queue length now
					 */

					go_to->queue_status->total_onside_vehicles++;
					go_to->queue_status->in_moving_vehicles++;

					out_capacity--;

					//move to next Segment
					VehiclePackage* the_back = NULL;
					if (go_to->vehiclePackageQueue.empty() || go_to->vehiclePackageQueue.back()->joinTime != current_time_step) {
						the_back = new VehiclePackage();
						the_back->joinTime = current_time_step;
						go_to->vehiclePackageQueue.push_back(the_back);
					}
					else {
						the_back = go_to->vehiclePackageQueue.back();
					}

					the_back->inner_vehicles.push_back(*it);
					the_back->vehicle_size++;

					if (this->seg_id == 3) {
//						std::cout << "one go to 5:" << gt5 << std::endl;
//						gt5++;
						move_in ++;
					}
				}
				else {
					std::cout << "Error: Not Existing Des When process seg 3" << std::endl;
				}

//				int ii = it - the_last->inner_vehicles.begin();
//				std::cout << "ii:" << ii << std::endl;
				it = the_last->inner_vehicles.erase(it);

				this->all_lanes[0]->queue_status->total_onside_vehicles--;
				this->all_lanes[0]->queue_status->in_queue_vehicles--;
				this->all_lanes[0]->queue_status->current_queue_length -= TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;

				if (this->all_lanes[0]->queue_status->in_queue_vehicles <= 0)
					this->all_lanes[0]->queue_status->end_queue_VehiclePackage = NULL;
			}

			//if no more vehicle, remove this package
			if (the_last->inner_vehicles.size() <= 0) {
				all_lanes[0]->vehiclePackageQueue.pop();

				if (the_last)
					delete the_last;
			}

#ifdef USE_DEBUY_CODE
			if(TestBedSettings::debug_mode)
			{
				this->all_lanes[0]->count_passing_vehicle += the_last->vehicle_size;
			}
#endif
		}

		if(move_in > 1)
		{
			std::cout << "Error cannot move out more than 1:" << move_in << std::endl;
		}
		else
		{
			std::cout << "move out:" << move_in << std::endl;
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

	bool pass_1 = false;
	bool pass_2 = false;

	if (size_seg_1 > 0 && RoadNetwork::instance().seg1->all_lanes[0]->vehiclePackageQueue.front()->joinTime <= RoadNetwork::instance().seg1->who_can_pass_time) {
		can_pass_1 = true;
	}
	if (size_seg_2 > 0 && RoadNetwork::instance().seg2->all_lanes[0]->vehiclePackageQueue.front()->joinTime <= RoadNetwork::instance().seg2->who_can_pass_time) {
		can_pass_2 = true;
	}

	static int random_seed = 0;
	if (can_pass_1 && can_pass_2) {
		random_seed = 1 - random_seed;

		if (random_seed == 0) {
			pass_1 = true;
		}
		else {
			pass_2 = true;
		}
	}
	else if (can_pass_1) {
		pass_1 = true;
	}
	else if (can_pass_2) {
		pass_2 = true;
	}
	else {
		return NULL;
	}

	if (pass_1 == true) {
		VehiclePackage* the_one = RoadNetwork::instance().seg1->all_lanes[0]->vehiclePackageQueue.front();
		Segment* seg = RoadNetwork::instance().seg1;

#ifdef USE_DEBUY_CODE
		if(TestBedSettings::debug_mode)
		{
			seg->all_lanes[0]->count_passing_vehicle ++;
		}
#endif
		if (the_one->inner_vehicles.size() > 1) {
			the_one->vehicle_size--;
			std::vector<Vehicle *>::iterator it = the_one->inner_vehicles.end() - 1;
			Vehicle* one = (*it);
			the_one->inner_vehicles.erase(it);

			seg->all_lanes[0]->queue_status->total_onside_vehicles--;
			seg->all_lanes[0]->queue_status->in_queue_vehicles--;
			seg->all_lanes[0]->queue_status->current_queue_length -= TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;
			if (seg->all_lanes[0]->queue_status->in_queue_vehicles <= 0) {
				seg->all_lanes[0]->queue_status->end_queue_VehiclePackage = NULL;
			}

			return one;
		}
		else {
			std::vector<Vehicle *>::iterator it = the_one->inner_vehicles.end() - 1;
			Vehicle* one = (*it);

			if (the_one)
				delete the_one;

			seg->all_lanes[0]->vehiclePackageQueue.pop();

			seg->all_lanes[0]->queue_status->total_onside_vehicles--;
			seg->all_lanes[0]->queue_status->in_queue_vehicles--;
			seg->all_lanes[0]->queue_status->current_queue_length -= TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;
			if (seg->all_lanes[0]->queue_status->in_queue_vehicles <= 0) {
				seg->all_lanes[0]->queue_status->end_queue_VehiclePackage = NULL;
			}

			return one;
		}

	}
	else if (pass_2 == true) {
		VehiclePackage* the_one = RoadNetwork::instance().seg2->all_lanes[0]->vehiclePackageQueue.front();
		Segment* seg = RoadNetwork::instance().seg2;
#ifdef USE_DEBUY_CODE
		if(TestBedSettings::debug_mode)
		{
			seg->all_lanes[0]->count_passing_vehicle ++;
		}
#endif
		if (the_one->inner_vehicles.size() > 1) {
			the_one->vehicle_size--;
			std::vector<Vehicle *>::iterator it = the_one->inner_vehicles.end() - 1;
			Vehicle* one = (*it);
			the_one->inner_vehicles.erase(it);

			seg->all_lanes[0]->queue_status->total_onside_vehicles--;
			seg->all_lanes[0]->queue_status->in_queue_vehicles--;
			seg->all_lanes[0]->queue_status->current_queue_length -= TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;
			if (seg->all_lanes[0]->queue_status->in_queue_vehicles <= 0) {
				seg->all_lanes[0]->queue_status->end_queue_VehiclePackage = NULL;
			}

			return one;
		}
		else {
			std::vector<Vehicle *>::iterator it = the_one->inner_vehicles.end() - 1;
			Vehicle* one = (*it);

			if (the_one)
				delete the_one;

			seg->all_lanes[0]->vehiclePackageQueue.pop();

			seg->all_lanes[0]->queue_status->total_onside_vehicles--;
			seg->all_lanes[0]->queue_status->in_queue_vehicles--;
			seg->all_lanes[0]->queue_status->current_queue_length -= TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;
			if (seg->all_lanes[0]->queue_status->in_queue_vehicles <= 0) {
				seg->all_lanes[0]->queue_status->end_queue_VehiclePackage = NULL;
			}

			return one;
		}

	}

	return NULL;
}

void Segment::xy_simulate_seg1_2_together(int current_time_step) {
//Step 1: Update Speed & Step 2
//only 1 lane, so hard coded
	{
		Segment* seg = RoadNetwork::instance().seg1;
//		double moving_length = seg->seg_length - seg->all_lanes[0]->queue_status->current_queue_length;
//		double moving_density = seg->all_lanes[0]->queue_status->in_moving_vehicles / moving_length;

		double moving_density = seg->all_lanes[0]->queue_status->total_onside_vehicles / seg->seg_length;

		double speed = GeneralTool::calculate_speed_based_on_density(moving_density);
		seg->hash_table_speed->add_time_speed(current_time_step, speed);

		if (current_time_step % TestBedSettings::remove_speed_frequency == 0)
			seg->xy_clear_old_speeds();

		if (TestBedSettings::debug_mode)
			std::cout << "seg_ID:" << seg->seg_id << "	,speed:" << speed << "	,moving:" << seg->all_lanes[0]->queue_status->in_moving_vehicles << "	,all:"
					<< seg->all_lanes[0]->queue_status->total_onside_vehicles << "	,queue:" << seg->all_lanes[0]->queue_status->current_queue_length << "	,empty space:"
					<< seg->all_lanes[0]->empty_space << std::endl;

		//Step 2: Update Can Pass Time
		seg->who_can_pass_offset += speed * TestBedSettings::time_step_unit;
		while (seg->who_can_pass_offset > seg->seg_length) {
			seg->who_can_pass_time += TestBedSettings::time_step_unit;

//			std::cout << "seg " << seg->seg_id << ", some vehicle can pass, who_can_pass_time:" << seg->who_can_pass_time << ",who_can_pass_offset:"
//					<< seg->who_can_pass_offset << std::endl;
			seg->all_lanes[0]->update_queue_status_when_moving_segment(seg->who_can_pass_time);
			//
			assert(seg->who_can_pass_time <= current_time_step);
			seg->who_can_pass_offset -= seg->hash_table_speed->get_time_speed(seg->who_can_pass_time) * TestBedSettings::time_step_unit;
		}
	}

	{
		Segment* seg = RoadNetwork::instance().seg2;
//		double moving_length = seg->seg_length - seg->all_lanes[0]->queue_status->current_queue_length;
//		double moving_density = seg->all_lanes[0]->queue_status->in_moving_vehicles / moving_length;

		double moving_density = seg->all_lanes[0]->queue_status->total_onside_vehicles / seg->seg_length;

		double speed = GeneralTool::calculate_speed_based_on_density(moving_density);
		seg->hash_table_speed->add_time_speed(current_time_step, speed);

		if (current_time_step % TestBedSettings::remove_speed_frequency == 0)
			seg->xy_clear_old_speeds();

		if (TestBedSettings::debug_mode)
			std::cout << "seg_ID:" << seg->seg_id << "	,speed:" << speed << "	,moving:" << seg->all_lanes[0]->queue_status->in_moving_vehicles << "	,all:"
					<< seg->all_lanes[0]->queue_status->total_onside_vehicles << "	,queue:" << seg->all_lanes[0]->queue_status->current_queue_length << "	,empty space:"
					<< seg->all_lanes[0]->empty_space << std::endl;

		//Step 2: Update Can Pass Time
		seg->who_can_pass_offset += speed * TestBedSettings::time_step_unit;
		while (seg->who_can_pass_offset > seg->seg_length) {
			seg->who_can_pass_time += TestBedSettings::time_step_unit;

//			std::cout << "seg " << seg->seg_id << ", some vehicle can pass, who_can_pass_time:" << seg->who_can_pass_time << ",who_can_pass_offset:"
//					<< seg->who_can_pass_offset << std::endl;
			seg->all_lanes[0]->update_queue_status_when_moving_segment(seg->who_can_pass_time);
			//
			assert(seg->who_can_pass_time <= current_time_step);
			seg->who_can_pass_offset -= seg->hash_table_speed->get_time_speed(seg->who_can_pass_time) * TestBedSettings::time_step_unit;
		}

//		if (TestBedSettings::debug_mode)
//			std::cout << "seg " << seg->seg_id << ",who_can_pass_offset:" << seg->who_can_pass_offset << ",who_can_pass_time:" << seg->who_can_pass_time << std::endl;

	}

//Step 3: Move Vehicle To Next Segment
	int temp_input_capacity = RoadNetwork::instance().seg3->all_lanes[0]->inside_capacity_per_time_step_unit;
	double temp_empty_space = RoadNetwork::instance().seg3->all_lanes[0]->empty_space;

//	std::cout << "temp_input_capacity:" << temp_input_capacity << ",temp_empty_space:" << temp_empty_space << std::endl;

	while (temp_input_capacity > 0 && temp_empty_space > TestBedSettings::VEHICLE_OCCUPANCY_LENGTH) {
		Vehicle* the_next_one = Segment::xy_find_the_next_vehicle_package();

		if (the_next_one == NULL) {
//			std::cout << "xy_find_the_next_vehicle_package is NULL" << std::endl;
			break;
		}

//		std::cout << "xy_find_the_next_vehicle_package" << std::endl;

//		else {
////			std::cout << "xy_find_the_next_vehicle_package is not not not NULL" << std::endl;
//		}

		Lane* go_to = RoadNetwork::instance().seg3->all_lanes[0];
		temp_input_capacity--;
		temp_empty_space -= TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;

		//add vehicle number
		go_to->queue_status->total_onside_vehicles++;
		go_to->queue_status->in_moving_vehicles++;

		//move to next Segment
		VehiclePackage* the_back = NULL;
		if (go_to->vehiclePackageQueue.empty() || go_to->vehiclePackageQueue.back()->joinTime != current_time_step) {
			the_back = new VehiclePackage();
			the_back->joinTime = current_time_step;
			go_to->vehiclePackageQueue.push_back(the_back);
		}
		else {
			the_back = go_to->vehiclePackageQueue.back();
		}

		the_back->inner_vehicles.push_back(the_next_one);
		the_back->vehicle_size++;

		//upate queue
	}

//Step 4: Update Queue Status
	RoadNetwork::instance().seg1->all_lanes[0]->update_queue_status_after_moving_segment(current_time_step);
	RoadNetwork::instance().seg2->all_lanes[0]->update_queue_status_after_moving_segment(current_time_step);

//Step 5: Update Empty Space
//No need to calculate for seg 1 and seg 2;
	{
		Segment* seg = RoadNetwork::instance().seg1;
		if (seg->all_lanes[0]->vehiclePackageQueue.empty()) {
			seg->all_lanes[0]->empty_space = seg->seg_length;
		}
		else {
			int last_time_step = seg->all_lanes[0]->vehiclePackageQueue.back()->joinTime;
			double total_empty_space = 0;
			for (int i = last_time_step + TestBedSettings::time_step_unit; i <= current_time_step; i += TestBedSettings::time_step_unit) {
				total_empty_space += TestBedSettings::time_step_unit * seg->hash_table_speed->get_time_speed(i);
			}

//			total_empty_space -= all_lanes[0]->vehiclePackageQueue.back()->inner_vehicles.size() * TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;
			//queue feedback
			if (total_empty_space > (seg->seg_length - seg->all_lanes[0]->queue_status->current_queue_length)) {
				total_empty_space = seg->seg_length - seg->all_lanes[0]->queue_status->current_queue_length;
			}

			if (total_empty_space < 0)
				total_empty_space = 0;
			assert(total_empty_space >= 0);

			seg->all_lanes[0]->empty_space = total_empty_space;
		}

#ifdef USE_DEBUY_CODE
		seg->debug();
#endif
	}

	{
		Segment* seg = RoadNetwork::instance().seg2;
		if (seg->all_lanes[0]->vehiclePackageQueue.empty()) {
			seg->all_lanes[0]->empty_space = seg->seg_length;
		}
		else {
			int last_time_step = seg->all_lanes[0]->vehiclePackageQueue.back()->joinTime;
			double total_empty_space = 0;
			for (int i = last_time_step + TestBedSettings::time_step_unit; i <= current_time_step; i += TestBedSettings::time_step_unit) {
				total_empty_space += TestBedSettings::time_step_unit * seg->hash_table_speed->get_time_speed(i);
			}

//			total_empty_space -= all_lanes[0]->vehiclePackageQueue.back()->inner_vehicles.size() * TestBedSettings::VEHICLE_OCCUPANCY_LENGTH;
			//queue feedback
			if (total_empty_space > (seg->seg_length - seg->all_lanes[0]->queue_status->current_queue_length)) {
				total_empty_space = seg->seg_length - seg->all_lanes[0]->queue_status->current_queue_length;
			}

			if (total_empty_space < 0)
				total_empty_space = 0;

			assert(total_empty_space >= 0);

			seg->all_lanes[0]->empty_space = total_empty_space;
		}
#ifdef USE_DEBUY_CODE
		seg->debug();
#endif
	}
}

void Segment::reset_simulation_per_time_step() {
	for (std::vector<Lane*>::iterator it = all_lanes.begin(); it != all_lanes.end(); ++it) {
		/* std::cout << *it; ... */
		(*it)->reset_input_output_capacity();
	}
}

//void Segment::xy_add_a_new_vehicle_in_segment(int lane_id) {
//
//}

void Segment::xy_clear_old_speeds() {
//	if (this->all_lanes[0]->vehiclePackageQueue.size() <= 0)
//		return;
//
//	for (int i = this->last_remove_time_step + TestBedSettings::time_step_unit; i <= this->all_lanes[0]->vehiclePackageQueue.queueFront->joinTime - TestBedSettings::time_step_unit; i +=
//			TestBedSettings::time_step_unit) {
//		this->hash_table_speed->speed_his.erase(i);
//	}
//
//	this->last_remove_time_step = this->all_lanes[0]->vehiclePackageQueue.queueFront->joinTime - TestBedSettings::time_step_unit;
}

#ifdef USE_DEBUY_CODE
void Segment::debug() {

	std::cout << "seg ID:" << this->seg_id << std::endl;

	for (std::vector<Lane*>::iterator it = all_lanes.begin(); it != all_lanes.end(); ++it) {
		/* std::cout << *it; ... */
		(*it)->debug();
	}
}
#endif
