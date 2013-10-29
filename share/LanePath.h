/*
 * LanePath.h
 *
 *  Created on: Oct 29, 2013
 *      Author: xuyan
 */

#ifndef LANEPATH_H_
#define LANEPATH_H_

#include "shared_include.h"

class Lane;

class LanePath {
public:
	LanePath();
	virtual ~LanePath();

public:
	int ID;
	std::vector<Lane*> the_lanes;
};

#endif /* LANEPATH_H_ */
