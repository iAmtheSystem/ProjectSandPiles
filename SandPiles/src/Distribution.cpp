/*
 * Distribution.cpp
 *
 *  Created on: Mar 12, 2016
 *      Author: simon
 */

#include "Distribution.h"

Distribution::Distribution(int dimension, int sidelength)
:dimension(dimension),sidelength(sidelength),nrOfElements(pow(sidelength,dimension))
{
	data = std::vector<int> (nrOfElements);

}

Distribution::~Distribution() {
	// TODO Auto-generated destructor stub
}

const void Distribution::calculateDistribution(int nrOfIterations) {
	for(int i=0;i<nrOfIterations;i++){
		// std::cout << i << "\t";
		SandPile *pile = new SandPile(dimension,sidelength);

		std::cout << "data point " << i;

		// Thermalizing
		for(int j=0;j<nrOfElements;j++){
			pile->timestep();
		}
		int randomLatticeSite = uniformRand(0,nrOfElements);
		if(pile->getPoint(randomLatticeSite)<2*dimension){
			i--;
			std::cout << " redo ";
			continue;
		}
		int size = pile->clusterSize(randomLatticeSite);


		data[size]++;
		std::cout << std::endl;
		// std::cout << size << std::endl;
		free(pile);
	}
}

const void Distribution::fprintData() {
	fprintData("./data/SizeDistribution.dat");
}

const void Distribution::averageDistribution(int nrOfIterations,
		int nrOfDistributions) {
	for(int nr=0;nr<nrOfDistributions;nr++){
		// TODO DODODODODODO
	}
}

const void Distribution::fprintData(const std::string name) {
	std::cout << "Printing file for Size Distribution" << std::endl;

		std::fstream file;
		file.open(name.c_str(),std::ios::out);
		file << "# dimension = " << dimension << std::endl;
		file << "# size | nrOfCluster " << std::endl;

		for(int i=0;i<nrOfElements;i++){
			std::cout << i << "\t" << data[i] << "\n";
			file << i << "\t" << data[i] << "\n";
		}


		file.close();

}
