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

extern double arithmeticMedianByVariance(int array_length, double x[], double variances[],
		double& var) {
	double median = 0;
	double weight = 0;
	double w_i = 0;
	for(int i=0;i<array_length;i++){
		w_i = 1/variances[i];
		median += x[i]*w_i;
		weight += w_i;
	}
	median /= weight; //  = median*1/1/var

	// variance like gaußian error propagation

	for(int i=0;i<array_length;i++){
		var += 1/(weight);
	}
	var = sqrt(var);

	return median;
}
