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

const double averageSlope::averageSlopeOfCluster(int point, SandPile *pile) {
	int nrOfElements = pile->getNrOfElements();
	std::vector<int> critical(nrOfElements);
	critical = pile->defineCluster(point);
	// pile->coutLattice2d(critical);
	int clustersize = 0;
	double average=0;
	for(int i=0;i<nrOfElements;i++){
		if(critical[i] == 1){
			clustersize++;
			average += pile->getPoint(i);
		}
	}
	return (double)average/clustersize;
}

const void averageSlope::averageSlopeOfCluster() {
	int nrOfClusters = 1000;
	double variance;
	double mean = 0;
	double M2 = 0;
	double delta = 0;
	double x; // "Messwert..." 0 oder 1#
	double sampleVariance;
	double VarianceXbar = 0;

	bool clusterfound;

	std::fstream file;
	file.open("./data/averageSlope/avSlopeOfCluster.dat",std::ios::out);
	file << "# ClusterNr | averageSlope | clustersize" << std::endl;



	for(int i=0;i<nrOfClusters;i++){
		clusterfound = false;
		SandPile *pile = new SandPile(2,50);
		int point;
		while(!clusterfound){
			point = uniformRand(0,pile->getNrOfElements());
			if(pile->getPoint(point)==pile->getZk()) clusterfound = true;
		}
		x = averageSlopeOfCluster(point,pile);
		// calculating moving average + variance
		delta = x - mean;
		mean += (double) delta/(i+1);
		M2 += delta*(x-mean);

		sampleVariance = (double) M2/i;

		VarianceXbar = sampleVariance/i; // see script chapter 2 page 12.
		int clustersize = pile->clusterSize(point);
		file << i << "\t" << x << "\t "<< clustersize << "\n";
		std::cout << i << "\t" << x << "\t "<< clustersize << "\t" << (double)i/nrOfClusters *100 << "%" << std::endl;
		free(pile);
	}

	variance = VarianceXbar;

	file << "# Mean =" << mean << "\tVariance = " << variance;
	file.close();
	std::cout << "Average Slope of Cluster is " << mean << " +/-" << sqrt(variance) << std::endl;
}

const double averageSlope::averageSlopeOfReached(int point, SandPile *pile) {
	int nrOfElements = pile->getNrOfElements();
	std::vector<int> critical(nrOfElements);
	critical = pile->defineReached(point);
	// pile->coutLattice2d(critical);
	int clustersize = 0;
	double average=0;
	for(int i=0;i<nrOfElements;i++){
		if(critical[i] == 1){
			clustersize++;
			average += pile->getPoint(i);
		}
	}
	return (double)average/clustersize;
}


const void averageSlope::averageSlopeOfReached() {
	int nrOfClusters = 1000;
	double variance;
	double mean = 0;
	double M2 = 0;
	double delta = 0;
	double x; // "Messwert..." 0 oder 1#
	double sampleVariance;
	double VarianceXbar = 0;

	bool clusterfound;

	std::fstream file;
	file.open("./data/averageSlope/avSlopeOfReached.dat",std::ios::out);
	file << "# ClusterNr | averageSlope | clustersize" << std::endl;



	for(int i=0;i<nrOfClusters;i++){
		clusterfound = false;
		SandPile *pile = new SandPile(2,50);
		int point;
		while(!clusterfound){
			point = uniformRand(0,pile->getNrOfElements());
			if(pile->getPoint(point)==pile->getZk()) clusterfound = true;
		}
		x = averageSlopeOfReached(point,pile);
		// calculating moving average + variance
		delta = x - mean;
		mean += (double) delta/(i+1);
		M2 += delta*(x-mean);

		sampleVariance = (double) M2/i;

		VarianceXbar = sampleVariance/i; // see script chapter 2 page 12.
		int clustersize = pile->clusterSize(point);
		file << i << "\t" << x << "\t "<< clustersize << "\n";
		std::cout << i << "\t" << x << "\t "<< clustersize << "\t" << (double)i/nrOfClusters *100 << "%" << std::endl;
		free(pile);
	}

	variance = VarianceXbar;

	file << "# Mean =" << mean << "\tVariance = " << variance;
	file.close();
	std::cout << "Average Slope of Reached is " << mean << " +/-" << sqrt(variance) << std::endl;
}

const void averageSlope::averageSlopeOfClusterReachedAndLattice() {
	int nrOfClusters = 10000;
	bool clusterfound;

	std::fstream file;
	file.open("./data/averageSlope/avSlopeOfClusterReachedAndLattice.dat",std::ios::out);
	file << "# 1 PileNr | 2 averageSlopeLattice | 3 averageSlopeCluster | 4 averageSlopeReached | 5 clustersize" << std::endl;

	double averageSlopeLattice, averageSlopeCluster, averageSlopeReached;
	int clustersize;


	for(int i=0;i<nrOfClusters;i++){
		clusterfound = false;
		SandPile *pile = new SandPile(2,50);
		int point;
		while(!clusterfound){
			point = uniformRand(0,pile->getNrOfElements());
			if(pile->getPoint(point)==pile->getZk()) clusterfound = true;
		}

		averageSlopeCluster = averageSlopeOfCluster(point,pile);
		averageSlopeReached = averageSlopeOfReached(point,pile);
		averageSlopeLattice = pile->averageSlope();
		// calculating moving average + variance
		clustersize = pile->clusterSize(point);
		// "# PileNr | averageSlopeLattice | averageSlopeCluster | averageSlopeReached | clustersize" << std::endl;

		file << i << "\t" << averageSlopeLattice << "\t "
						  << averageSlopeCluster << "\t "
						  << averageSlopeReached << "\t "
						  << clustersize << "\n";
		std::cout << i << "\t" << averageSlopeLattice << "\t "
				  << averageSlopeCluster << "\t "
				  << averageSlopeReached << "\t "
				  << clustersize << "\t" << (double)i/nrOfClusters *100 << "%" << "\n";
		free(pile);
	}

	file.close();

}
