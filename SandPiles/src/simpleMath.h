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
#include <cmath>

extern bool seeded;

extern double uniformRand(double from, double to);

extern double arithmeticMedianByVariance(int array_length,double x[], double variances[], double & var);

#endif /* SIMPLEMATH_H_ */
