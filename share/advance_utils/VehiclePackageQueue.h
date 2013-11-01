/*
 * VehiclePackageQueue.h
 *
 *  Created on: Oct 31, 2013
 *      Author: xuyan
 */

#ifndef VEHICLEPACKAGEQUEUE_H_
#define VEHICLEPACKAGEQUEUE_H_

#include <vector>

#include "../shared_include.h"
#include "VehiclePackage.h"

class VehiclePackageQueue {
public:

	VehiclePackageQueue();
	virtual ~VehiclePackageQueue();

public:
	bool empty();
	VehiclePackage* front();
	VehiclePackage* back();

	bool pop();
	bool push_back(VehiclePackage* one);

	int size();

public:

	VehiclePackage* queueFront;
	VehiclePackage* queueEnd;
	int package_size;
};


#endif /* VEHICLEPACKAGEQUEUE_H_ */
