/*
 * TestBedSettings.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#include "TestBedSettings.h"

/**
 * Setting Values
 */

const int TestBedSettings::start_time_step = 0 * 3600; //sec
const int TestBedSettings::end_time_step = 1 * 3600;   //sec
const int TestBedSettings::time_step_unit = 2;  //sec
const int TestBedSettings::total_time_step = (end_time_step - start_time_step) / time_step_unit;  //sec

const double TestBedSettings::seg_length = 1000; //meter
const int TestBedSettings::lane_outside_capacity_per_time_step_unit = 1800 * time_step_unit / 3600; //vehicles per time_step_unit
const int TestBedSettings::lane_inside_capacity_per_time_step_unit = 1800 * time_step_unit / 3600; //vehicles per time_step_unit

const double TestBedSettings::VEHICLE_LENGTH = 5; // m
const double TestBedSettings::VEHICLE_OCCUPANCY_LENGTH = (1.5 * VEHICLE_LENGTH); // m

const double TestBedSettings::MAX_SPEED = 25; // m/s
const double TestBedSettings::MIN_SPEED = 5; // m/s
const double TestBedSettings::MAX_LANE_DENSITY = 1.0 / (VEHICLE_OCCUPANCY_LENGTH); //max number of vehicle in a lane

const int TestBedSettings::loading_freq = 2 * time_step_unit; //how many time_step_units load once
const int TestBedSettings::loading_vehicles = 2; //how many vehicles load once

const bool TestBedSettings::debug_mode = true;

