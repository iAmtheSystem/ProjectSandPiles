/*
 * Distribution.h
 *
 *  Created on: Mar 12, 2016
 *      Author: simon
 */

#ifndef DISTRIBUTION_H_
#define DISTRIBUTION_H_

#include <vector>
#include <fstream>
#include <string>
#include "SandPile.h"
#include "simpleMath.h"

// the Size Distribution is meant
class Distribution {
private:
	const int dimension;
	const int sidelength;
	const int nrOfElements;
	std::vector<int> data;
public:
	Distribution(int dimension, int sidelength);
	virtual ~Distribution();

	const void calculateDistribution(int nrOfIterations);
	const void averageDistribution(int nrOfIterations, int nrOfDistributions);

	const void fprintData();
	const void fprintData(const std::string name);


};

#endif /* DISTRIBUTION_H_ */
