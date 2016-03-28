/*
 * Distribution.cpp
 *
 *  Created on: Mar 12, 2016
 *      Author: simon
 */

#include "Distribution.h"

Distribution::Distribution(int dimension, int sidelength, int nrOfDataPoints)
:dimension(dimension),sidelength(sidelength),nrOfElements(pow(sidelength,dimension)),nrOfDatapoints(nrOfDataPoints)
{
	dataTime = std::vector<int> (nrOfDataPoints);
	dataSize = std::vector<int> (nrOfDataPoints);
	dataRadius = std::vector<int> (nrOfDataPoints);

	dataTimeSorted = std::vector<int> (nrOfElements);
	dataSizeSorted = std::vector<int> (nrOfElements);
	dataRadiusSorted = std::vector<int> (nrOfElements);

	dissipationRate = std::vector<int> (nrOfElements);
}

Distribution::~Distribution() {
	// TODO Auto-generated destructor stub
}

const void Distribution::calculateDistribution() {
	for(int i=0;i<nrOfDatapoints;i++){
		// std::cout << i << "\t";
		SandPile *pile = new SandPile(dimension,sidelength);
		// Thermalizing
//		for(int j=0;j<nrOfElements;j++){
//			pile->timestep();
//		}
		int randomCluster = pile->randomCluster();
		dataTime[i] = 0;
		dataSize[i] = 0;
		dataRadius[i] = 0;
		pile->caluclateClusterdata(randomCluster,dataTime[i],dataSize[i],dataRadius[i]);

		std::cout
					<< i << "\t"
					<< dataTime[i] << "\t"
					<< dataSize[i] << "\t"
					<< dataRadius[i] << "\t"
					<< double(i)/nrOfDatapoints * 100 << "%" << "\n";

		free(pile);
	}
}

const void Distribution::calculateDissipationRateDistribution() {
	SandPile *pile = new SandPile(dimension,sidelength);
	// Thermalizing
//		for(int j=0;j<nrOfElements;j++){
//			pile->timestep();
//		}

	int randomCluster = pile->randomCluster();
	pile->caluclateDissipationdata(randomCluster,dissipationRate);

}


const void Distribution::fprintData() {
	fprintData("./data/TimeSizeRadiusDistribution.dat");
}

const void Distribution::averageDistribution(int nrOfIterations,
		int nrOfDistributions) {
	for(int nr=0;nr<nrOfDistributions;nr++){
		// TODO DODODODODODO
	}
}

const void Distribution::fprintData(const std::string name) {
	std::cout << "Printing file for Time/Size/Radius Distribution" << std::endl;

		std::fstream file;
		file.open(name.c_str(),std::ios::out);
		file << "# dimension = " << dimension << std::endl;
		file << "# nrOfCluster | Time | Size | Radius " << std::endl;

		for(int i=0;i<nrOfDatapoints;i++){
			file  << i << "\t"
					<< dataTime[i] << "\t"
					<< dataSize[i] << "\t"
					<< dataRadius[i] << "\t"
					<< std::endl;
		}

		sortForAll();

		fprintData("./data/TimeDistribution.dat",dataTimeSorted,nrOfElements);
		fprintData("./data/SizeDistribution.dat",dataSizeSorted,nrOfElements);
		fprintData("./data/RadiusDistribution.dat",dataRadiusSorted,nrOfElements);

		file.close();

}

const void Distribution::fprintData(const std::string name,
		std::vector<int> data, int nrOfPoints) {

	std::fstream file;

	file.open(name.c_str(),std::ios::out);


	file << "# dimension = " << dimension << " sidelength = " << sidelength << std::endl;
	file << "# x | y" << std::endl;
	for(int i=0;i<nrOfElements;i++){
		file  << i << "\t" << data[i] << std::endl;
	}

	file.close();

}


const void Distribution::sortForAll(){
	sortForTime();
	sortForSize();
	sortForRadius();
}

const void Distribution::sortForTime() {
	for(int i=0;i<nrOfDatapoints;i++){
		dataTimeSorted[dataTime[i]]++;
	}
}

const void Distribution::sortForSize() {
	for(int i=0;i<nrOfDatapoints;i++){
		dataSizeSorted[dataSize[i]]++;
	}
}

const void Distribution::fprintADissipation() {
	fprintData("./data/ADissipation.dat",dissipationRate,nrOfElements);
}

const void Distribution::sortForRadius() {
	for(int i=0;i<nrOfDatapoints;i++){
		dataRadiusSorted[dataRadius[i]]++;
	}
}
