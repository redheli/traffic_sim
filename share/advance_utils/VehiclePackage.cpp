/*
 * VehiclePackage.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: xuyan
 */

#include "VehiclePackage.h"

VehiclePackage::VehiclePackage() {
	joinTime = 0;
	vehicle_size = 0;
//	in_Queue_Time = 0;

	front = NULL;
	back = NULL;
}

VehiclePackage::~VehiclePackage() {

}
