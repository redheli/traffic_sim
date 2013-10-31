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

	VehiclePackage* queueFront;
	VehiclePackage* queueEnd;
};


#endif /* VEHICLEPACKAGEQUEUE_H_ */
