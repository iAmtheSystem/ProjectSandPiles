/*
 * averageSlope.cpp
 *
 *  Created on: Mar 22, 2016
 *      Author: simon
 */

#include "averageSlope.h"

averageSlope::averageSlope() {
	// TODO Auto-generated constructor stub

}

averageSlope::~averageSlope() {
	// TODO Auto-generated destructor stub
}


double averageSlope::determineAverageSlope(int dim, double &var,bool printConvergence, bool printLattice, bool justMidpoint,bool fromZero){
	int sidelength = 100;
		int nrOfElements = pow(sidelength,dim);
		std::cout << "filling from Zero" << std::endl;
		SandPile *pile = new SandPile(dim,sidelength,!fromZero);
		double avSlope;
		double slopeVariance;

		std::stringstream name;
		std::string filename;

		std::fstream file;
		filename = "./data/averageSlope/step"+name.str()+".dat";

		if(printConvergence) file.open("./data/averageSlope/convergence.dat",std::ios::out);

		if(printConvergence) file << "# Dimension: " << dim
				<< "\t Sidelength: " << sidelength
				<< "\n# FromMidpoint: "<< justMidpoint
				<< "\t From Zerozero" <<fromZero << std::endl;

		if(printConvergence) file << "# timesteps | averageSlope | averageSlopeVariance" << std::endl;
		avSlope = pile->averageSlope(slopeVariance);
		if(printConvergence) file << 0 << "\t" << avSlope << "\t" << slopeVariance << "\n";

		if(printLattice) pile->printLattice("./data/averageSlope/step0.dat");

		int totalSteps = nrOfElements*10;
		for(int t=1;t<totalSteps;t++){
			if(t%1000 == 0) std::cout << "timestep " << t << "  ->  " << (double) t/totalSteps * 100 << "%" << std::endl;
			pile->timestep(justMidpoint);
			if(printLattice){
			// Filename
				name.str("");
				name << t;
				filename = "./data/averageSlope/step"+name.str()+".dat";
				pile->printLattice(filename);
			}
			avSlope = pile->averageSlope(slopeVariance);
			if(printConvergence) file << t << "\t" << avSlope << "\t" << slopeVariance << "\n";
		}

		if(printConvergence) file.close();
		free(pile);
		var = slopeVariance;
		return avSlope;
}

double averageSlope::averageSlopeUsual(int dim, double& var) {
	return determineAverageSlope(2,var,false,false,false,false);
}

double averageSlope::fillingFromZero(int dim, bool printLattice, bool justMidpoint){
	double var = 0;
	return determineAverageSlope(2,var,true,printLattice,justMidpoint,true);

	// av = determineAverageSlope(dim,var,true,printLattice,justMidpoint,true);
}



const void averageSlope::averageSlopeOfSize() {
	int dim = 3;
	int zk;
	//dummy
	SandPile* dummy = new SandPile(dim,1);
	zk = dummy->getZk();
	free(dummy);
	std::cout << "Starting Data Slope of Size: dim = " << dim << std::endl;
	std::fstream file;
	file.open("./data/averageSlope/avSlopeBySize.dat",std::ios::out);
	file << "# dimension = " << dim << std::endl;
	file << "# ZK = " << zk << " | zk-2d = " << zk-2*dim << std::endl;
	file << "# size | avSlope | sqrt(var(avSlope)) " << std::endl;


	int sideLengthMax = 50;
	int nrOfValues = 10;

	for(int size=sideLengthMax;size>0;size--){
		double variance = 0;
		double median = 0;
		if(size<20) nrOfValues = 50;
		else if(size<35) nrOfValues = 10;
		else nrOfValues = 3;

		double av[nrOfValues];
		double var[nrOfValues];

		// Mittle über mehrere Werte pro Size
		for(int i=0;i<nrOfValues;i++){
			SandPile* pile = new SandPile(dim,size);
			av[i]=pile->averageSlope(var[i]);
			free(pile);
		}

		median = arithmeticMedianByVariance(nrOfValues,av,var,variance);
		std::cout << "For size "<< size <<" the Average Slope = " << median << " +/- " << sqrt(variance)
				<< " | " <<  (1- (double) size/sideLengthMax) * 100 << "%"<< std::endl;
		file << size << "\t" << median << "\t" << sqrt(variance) << "\n";
	}


	file.close();

}

const void averageSlope::averageSlopeOfdim() {

	int zk;
	int sideLength = 50;
	int dimMax = 4;

	std::fstream file;
	file.open("./data/averageSlope/avSlopeByDimension.dat",std::ios::out);
	file << "# sidelength " << sideLength << std::endl;
	file << "# dim | avSlope | sqrt(var(avSlope)) | zk " << std::endl;


	int nrOfValues = 1;

	for(int dim=dimMax;dim>1;dim--){
		double av[nrOfValues];
		double var[nrOfValues];
		double variance = 0;
		double median = 0;

		SandPile* dummy = new SandPile(dim,1);
		zk = dummy->getZk();
		free(dummy);

		// Mittle über mehrere Werte pro Size
		for(int i=0;i<nrOfValues;i++){
			SandPile* pile = new SandPile(dim,sideLength);
			av[i]=pile->averageSlope(var[i]);
			free(pile);

		}

		median = arithmeticMedianByVariance(nrOfValues,av,var,variance);
		std::cout << "For dimension "<< dim <<" the Average Slope = " << median << " +/- " << sqrt(variance)
				<< " | " << (double) dim/dimMax * 100 << "%"<< std::endl;
		file << dim << "\t" << median << "\t" << sqrt(variance) << "\t" << zk << "\n";
	}


	file.close();

}
