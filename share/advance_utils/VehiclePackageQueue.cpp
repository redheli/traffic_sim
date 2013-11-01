/*
 * VehiclePackageQueue.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: xuyan
 */

#include "VehiclePackageQueue.h"

VehiclePackageQueue::VehiclePackageQueue() {
	queueFront = NULL;
	queueEnd = NULL;

	package_size = 0;
}

VehiclePackageQueue::~VehiclePackageQueue() {

}

bool VehiclePackageQueue::empty() {
	return queueFront == NULL;
}

VehiclePackage* VehiclePackageQueue::front() {
	return queueFront;
}

VehiclePackage* VehiclePackageQueue::back() {
	return queueEnd;
}

bool VehiclePackageQueue::pop() {
	if (queueFront == NULL) {
		return false;
	}

	VehiclePackage* the_one = queueFront->back;
	if (the_one == NULL) {
		queueEnd = NULL;
		queueFront = NULL;
	} else {
		the_one->front = NULL;
		queueFront = the_one;
	}

	package_size--;

	return true;
}

bool VehiclePackageQueue::push_back(VehiclePackage* one) {
	if (queueEnd == NULL) {
		one->front = NULL;
		one->back = NULL;

		queueEnd = one;
		queueFront = one;
	} else {
		VehiclePackage* the_one = queueEnd;
		the_one->back = one;
		one->front = the_one;
		one->back = NULL;

		queueEnd = one;
	}

	package_size++;

	return true;
}

int VehiclePackageQueue::size() {
	return package_size;
}
