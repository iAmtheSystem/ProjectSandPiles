/*
 * simpleMath.h
 *
 *  Created on: Mar 2, 2016
 *      Author: simon
 */

#ifndef SIMPLEMATH_H_
#define SIMPLEMATH_H_

#include <time.h>
#include <stdlib.h>

bool seeded = false;

double uniformRand(double from, double to){
	if(!seeded) {
		srand (time(NULL));
		seeded = true;
	}
	return (double) rand()/RAND_MAX * (from-to) + to;

}




#endif /* SIMPLEMATH_H_ */
