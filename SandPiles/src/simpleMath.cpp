/*
 * simpleMath.cpp
 *
 *  Created on: Mar 3, 2016
 *      Author: simon
 */


#include "simpleMath.h"

bool seeded = false;

double uniformRand(double from, double to){
	if(!seeded) {
		srand (time(NULL));
		seeded = true;
	}
	return (double) rand()/RAND_MAX * (from-to) + to;

}
