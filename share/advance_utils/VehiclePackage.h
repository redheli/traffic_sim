/*
 * VehiclePackage.h
 *
 *  Created on: Oct 30, 2013
 *      Author: xuyan
 */

#ifndef VEHICLEPACKAGE_H_
#define VEHICLEPACKAGE_H_

#include <vector>

#include "../shared_include.h"
#include "../Vehicle.h"

class VehiclePackage {
public:

	VehiclePackage();
	virtual ~VehiclePackage();

public:
	std::vector<Vehicle *> inner_vehicles;

	VehiclePackage* front;
	VehiclePackage* back;

	int joinTime;
	int vehicle_size;
//	int in_Queue_Time; // for merge ordering
};

#endif /* VEHICLEPACKAGE_H_ */
