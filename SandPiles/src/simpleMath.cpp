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

extern void coord(int dim, int sidelength, int point, int koord[]) {

	for(int dimension=0;dimension<dim;dimension++){
		koord[dimension]=0;
	}

	for(int i=0;i<point;i++){
		koord[0] = koord[0] + 1;

		for(int dimension=0;dimension<dim;dimension++){
			if(koord[dimension]==sidelength){

				koord[dimension] = 0;
				koord[dimension+1]++;
			}
		}


	}
}

extern double radius(int dim, int koord1[], int koord2[]) {
	int sum = 0;
	for(int i=0;i<dim;i++){
		sum += (koord1[i]-koord2[i])*(koord1[i]-koord2[i]);
	}
	return sqrt(sum);
}
