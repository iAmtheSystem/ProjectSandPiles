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

#include "fft.h"

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
	std::vector<int> dissipationSpectrum;

	std::vector<double> fourierTransformedSpectrum;
	std::vector<double> fourierTransformedSpectrumAveraged;

public:
	Distribution(int dimension, int sidelength,int nrOfDataPoints);
	virtual ~Distribution();

	const void calculateDistribution();
	const void averageDistribution(int nrOfIterations, int nrOfDistributions);

	const void calculateDissipationRateDistribution();
	const void calculate50Dissipations();
	const void add1000Dissipations();
	const void add1000Dissipations(int tousand,bool silent);
	const void fftSpectrum();
	const void averagefftSpectrum();


	const void randomizeTimeDissipationRate();

	const void fprintData();
	const void fprintData(const std::string name);
	const void fprintData(const std::string name,std::vector<int> data, int nrOfPoints);
	const void fprintData(const std::string name,std::vector<double> data, int nrOfPoints);
	const void fprintData(const std::string name,std::vector<double> data, double data2[], int nrOfPoints);


	const void fprintADissipation();


	const void sortForAll();
	const void sortForTime();
	const void sortForSize();
	const void sortForRadius();

	const std::vector<int>& getDataRadius() const {
		return dataRadius;
	}

	const std::vector<int>& getDataRadiusSorted() const {
		return dataRadiusSorted;
	}

	const std::vector<int>& getDataTimeSorted() const {
		return dataTimeSorted;
	}

	const std::vector<int>& getDissipationRate() const {
		return dissipationRate;
	}
};

#endif /* DISTRIBUTION_H_ */
