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
	dissipationSpectrum = std::vector<int> (nrOfElements);
	fourierTransformedSpectrum = std::vector<double> (nrOfElements);
	fourierTransformedSpectrumAveraged = std::vector<double> (nrOfElements);
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
	for(int i=0;i<nrOfElements;i++){
		dissipationRate[i]= 0;
	}

	pile->caluclateDissipationdata(randomCluster,dissipationRate);

}


const void Distribution::calculate50Dissipations() {
	std::stringstream name;
	std::string filename;

	for(int i=0;i<50;i++){
		SandPile *pile = new SandPile(dimension,sidelength);
		// std::cout << "Calculating Distribution Nr " << i;
		int randomCluster = pile->randomCluster();
		// std::cout << " with random Cluster " << randomCluster;
		// std::cout << " with Lattice[5] " << pile->getPoint(5);
		std::cout << std::endl;

		for(int j=0;j<nrOfElements;j++){
			dissipationRate[j]= 0;

		}



		pile->caluclateDissipationdata(randomCluster,dissipationRate);
		randomizeTimeDissipationRate();

		name.str("");
		name << i;
		filename = "./data/dissipation/dissipation"+name.str()+".dat";
		fprintData(filename,dissipationRate,nrOfElements);
		free(pile);
	}
}

const void Distribution::add1000Dissipations() {
	int tousand = 10000;
	// std::cout << "\t Add 1000 Datapoints" << std::endl;

	for(int i=0;i<tousand;i++){
		SandPile *pile = new SandPile(dimension,sidelength);
		/// std::cout << "Calculating Distribution Nr " << i << "\t" << (double) i / tousand * 100 << "%";
		int randomCluster = pile->randomCluster();
		// std::cout << " with random Cluster " << randomCluster;
		// std::cout << " with Lattice[5] " << pile->getPoint(5);
		// std::cout << std::endl;

		for(int j=0;j<nrOfElements;j++){
			dissipationRate[j]= 0;
		}

		pile->caluclateDissipationdata(randomCluster,dissipationRate);
		randomizeTimeDissipationRate();

		for(int j=0;j<nrOfElements;j++){
			dissipationSpectrum[j] += dissipationRate[j];
		}

		fprintData("./data/dissipation/dissipationSpectrum.dat",dissipationSpectrum,nrOfElements);
		free(pile);
	}

}


const void Distribution::averageDistribution(int nrOfIterations,
		int nrOfDistributions) {
	for(int nr=0;nr<nrOfDistributions;nr++){
		// TODO DODODODODODO
	}
}

const void Distribution::fprintData() {
	fprintData("./data/TimeSizeRadiusDistribution.dat");
}



const void Distribution::fprintData(const std::string name) {
	std::cout << "Printing file for Time/Size/Radius Distribution" << std::endl;

		std::fstream file;
		file.open(name.c_str(),std::ios::out);
		file << "# dimension = " << dimension << "nr Of Elements = " << nrOfElements << std::endl;
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

const void Distribution::fprintData(const std::string name,
		std::vector<double> data, int nrOfPoints) {

	std::fstream file;

	file.open(name.c_str(),std::ios::out);


	file << "# dimension = " << dimension << " sidelength = " << sidelength << std::endl;
	file << "# x | y | var" << std::endl;
	for(int i=0;i<nrOfElements;i++){
		file  << i << "\t" << data[i] <<  std::endl;
	}

	file.close();

}




const void Distribution::fprintData(const std::string name,
		std::vector<double> data, double data2[], int nrOfPoints) {

	std::fstream file;

	file.open(name.c_str(),std::ios::out);


	file << "# dimension = " << dimension << " sidelength = " << sidelength << std::endl;
	file << "# x | y | var" << std::endl;
	for(int i=0;i<nrOfElements;i++){
		file  << i << "\t" << data[i] << "\t" << sqrt(data2[i]) << std::endl;
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

const void Distribution::randomizeTimeDissipationRate() {
	std::vector<int> puffer(dissipationRate);

	int moveBy = uniformRand(0,nrOfElements);
	int j;
	for(int i=0;i<nrOfElements;i++){
		j=i+moveBy;
		if(j>=nrOfElements) j-=nrOfElements;
		dissipationRate[i] = puffer[j];
	}
}

const void Distribution::fftSpectrum() {
	add1000Dissipations();
	const int datasize = 1024;
   //   Allocate memory for signal data
   complex *pSignal = new complex[datasize];
   for(int i=0;i<datasize;i++){
	   pSignal[i] = complex( (double) dissipationSpectrum[i]);
   }
//   for(int i=0;i<datasize;i++){
//	   std::cout << (&pSignal[i])->re() << " + i* " << (&pSignal[i])->im() << std::endl;
//   }
   //   Apply FFT
   CFFT::Forward(pSignal, datasize);
   // std::cout << "*** fourier transform **** " << std::endl;
   for(int i=0;i<datasize;i++){
	   // std::cout << (&pSignal[i])->re() << " + i* " << (&pSignal[i])->im() << std::endl;
	   fourierTransformedSpectrum[i] = (&pSignal[i])->norm();
   }
   //   Free memory
   // fprintData("./data/dissipation/transformedSpectrum.dat",fourierTransformedSpectrum,datasize);
   delete[] pSignal;
}

const void Distribution::averagefftSpectrum() {
	const int averageSamples = 100;

	double buffer[nrOfElements][averageSamples];
	double var[nrOfElements];

	for(int i=0;i<nrOfElements;i++){
		fourierTransformedSpectrumAveraged[i] = 0;
	}
	std::cout << "calculate FFTSpectra" << std::endl;
	std::stringstream name;
	std::string filename;
	for(int i = 0;i<averageSamples;i++){
		std::cout << "Calculating FFT Spectrum Nr " << i << " "<< (double) i/averageSamples * 100 << "%" << std::endl;
		fftSpectrum();
//		name.str("");
//		name << i;
//		filename = "./data/dissipation/transformedspectrum"+name.str()+".dat";

		// fprintData(filename,fourierTransformedSpectrum,1024);

		for(int j=0;j<nrOfElements;j++){
			buffer[j][i] = fourierTransformedSpectrum[j];

		}
	}
	std::cout << "Average Samples" << std::endl;
	for(int i = 0;i<nrOfElements;i++){
		// std::cout << i << "\tDebug 1" << std::endl;
		// std::cout << "\tBuffer[i][0] = " << buffer[i][0] << std::endl;
		fourierTransformedSpectrumAveraged[i] = meanAndVarianceOnline(buffer[i],averageSamples,(var[i]));
		// std::cout << "\tDebug 2" << std::endl;
	}


	fprintData("./data/dissipation/averagedFFTOfSpectrum.dat",fourierTransformedSpectrumAveraged,var,nrOfElements);

}

const void Distribution::sortForRadius() {
	for(int i=0;i<nrOfDatapoints;i++){
		dataRadiusSorted[dataRadius[i]]++;
	}
}
