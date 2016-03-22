/*
 * averageSlope.h
 *
 *  Created on: Mar 22, 2016
 *      Author: simon
 */

#ifndef AVERAGESLOPE_H_
#define AVERAGESLOPE_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

#include "SandPile.h"

class averageSlope {
public:
	averageSlope();
	virtual ~averageSlope();
	const void determineAverageSlope(int dim) const;
	const void fillingFromZero(int dim, bool printLattice=false,bool justMidpoint=false) const;
};

#endif /* AVERAGESLOPE_H_ */
