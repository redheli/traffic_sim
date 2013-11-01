/*
 * SpeedDensityRelationshipTool.h
 *
 *  Created on: Oct 29, 2013
 *      Author: hongyu
 */

#ifndef SPEEDDENSITYRELATIONSHIPTOOL_H_
#define SPEEDDENSITYRELATIONSHIPTOOL_H_

#include "shared_include.h"
#include "TestBedSettings.h"
#include "RoadNetwork.h"

class GeneralTool {
private:
	GeneralTool();
	virtual ~GeneralTool();

public:

	static double calculate_speed_based_on_density(double density_moving_part) {
		double speed = TestBedSettings::MAX_SPEED - TestBedSettings::MAX_SPEED * density_moving_part / (TestBedSettings::MAX_LANE_DENSITY / 2);
		return speed < TestBedSettings::MIN_SPEED ? TestBedSettings::MIN_SPEED : speed;
	}

};

#endif /* SPEEDDENSITYRELATIONSHIPTOOL_H_ */
