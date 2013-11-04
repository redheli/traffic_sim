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

int TestBedSettings::start_time_step = 0 * 3600; //sec
int TestBedSettings::end_time_step = 1 * 3600;   //sec
int TestBedSettings::time_step_unit = 2;  //sec
int TestBedSettings::total_time_step = (end_time_step - start_time_step) / time_step_unit;  //sec

double TestBedSettings::seg_length = 10000; //meter
int TestBedSettings::lane_outside_capacity_per_time_step_unit = 1800 * time_step_unit / 3600; //vehicles per time_step_unit
int TestBedSettings::lane_inside_capacity_per_time_step_unit = 1800 * time_step_unit / 3600; //vehicles per time_step_unit

double TestBedSettings::VEHICLE_LENGTH = 5; // m
double TestBedSettings::VEHICLE_OCCUPANCY_LENGTH = (1.5 * VEHICLE_LENGTH); // m

double TestBedSettings::MAX_SPEED = 25; // m/s
double TestBedSettings::MIN_SPEED = 5; // m/s
double TestBedSettings::MAX_LANE_DENSITY = 1.0 / (VEHICLE_OCCUPANCY_LENGTH); //max number of vehicle in a lane

int TestBedSettings::loading_freq = 1 * time_step_unit; //how many time_step_units load once
int TestBedSettings::loading_vehicles = 1; //how many vehicles load once

bool TestBedSettings::debug_mode = false;

int TestBedSettings::remove_speed_frequency = time_step_unit * 100; //sec
