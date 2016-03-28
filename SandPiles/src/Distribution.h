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
	int nrOfDatapoints;
	std::vector<int> dataTime;
	std::vector<int> dataSize;
	std::vector<int> dataRadius;

	std::vector<int> dataTimeSorted;
	std::vector<int> dataSizeSorted;
	std::vector<int> dataRadiusSorted;

	std::vector<int> dissipationRate;

public:
	Distribution(int dimension, int sidelength,int nrOfDataPoints);
	virtual ~Distribution();

	const void calculateDistribution();
	const void averageDistribution(int nrOfIterations, int nrOfDistributions);

	const void calculateDissipationRateDistribution();



	const void fprintData();
	const void fprintData(const std::string name);
	const void fprintData(const std::string name,std::vector<int> data, int nrOfPoints);

	const void fprintADissipation();


	const void sortForAll();
	const void sortForTime();
	const void sortForSize();
	const void sortForRadius();

};

#endif /* DISTRIBUTION_H_ */
