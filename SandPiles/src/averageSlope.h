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
#include "simpleMath.h"

class averageSlope {
public:
	averageSlope();
	virtual ~averageSlope();
	double determineAverageSlope(int dim, double &var,bool printConvergence, bool printLattice, bool justMidpoint,bool fromZero);
	double fillingFromZero(int dim, bool printLattice=false,bool justMidpoint=false);
	double averageSlopeUsual(int dim,double &var);
	const void averageSlopeOfdim();
	const void averageSlopeOfSize();
};

#endif /* AVERAGESLOPE_H_ */
