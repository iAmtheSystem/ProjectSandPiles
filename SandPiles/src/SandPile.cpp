/*
 * SandPile.cpp
 *
 *  Created on: Mar 2, 2016
 *      Author: simon
 */

#include "SandPile.h"

SandPile::SandPile():
	dimension(0),sidelength(0),nrOfElements(0),zk(0) {
	std::cout << "INIT" << std::endl;
}

SandPile::SandPile(int dimension, int sidelength):
		dimension(dimension),sidelength(sidelength),nrOfElements(pow(sidelength,dimension)),zk(2*dimension+1) {
	// lattice = std::vector<int> (nrOfElements);
	lattice.resize(nrOfElements);
	fillLatticeRand(zk,zk*2);
	relax(lattice);
}


SandPile::SandPile(int dimension, int sidelength, bool initialize):
		dimension(dimension),sidelength(sidelength),nrOfElements(pow(sidelength,dimension)),zk(2*dimension) {
	// lattice = std::vector<int> (nrOfElements);
	lattice.resize(nrOfElements);
	if(initialize) fillLatticeRand(zk,zk*2);
	relax(lattice);
}

SandPile::~SandPile() {
	// TODO Auto-generated destructor stub
}

const void SandPile::fillLatticeRand(const int from, const int to) {
	for(int i=0;i<pow(sidelength,dimension);i++){
		lattice[i] = uniformRand(from,to);
	}
}

const void SandPile::timestep() {
	timestep(false);
}

const void SandPile::timestep(bool midpoint) {
	lattice = relax(lattice);
	// 1. add random sand
	// TODO
	// std::cout << "\taddSand" << std::endl;
	if(midpoint){
		addSand(nrOfElements/2+sidelength/2);
	}
	else lattice=addSand(lattice);
}

const void SandPile::printLattice() {
	printLattice("sandPile.dat");
}

const void SandPile::setPoint(int point, int value) {
	lattice[point] = value;
}

std::vector<int> SandPile::relax(std::vector<int> &lat) {
	std::vector<int> nextTimeStepLattice (lat);

	// koordinates are just there to make to code better to understand,
	// could be neglected for higher performance
	int koord[dimension];
	bool relaxed;
	do{ // performance optimierbar!!!
		lat=nextTimeStepLattice;
		relaxed = true;
		for(int i=0;i<dimension;i++){
			koord[i] = 0;
		}


		for(int i=0;i<nrOfElements;i++){


			if(lat[i]>zk){
				relaxed = false;
				nextTimeStepLattice[i]-= 2*dimension;


				for(int d=0;d<dimension;d++){
					if(koord[d]<sidelength-1){
						nextTimeStepLattice[i+pow(sidelength,d)]++;
					}
					if(koord[d]>0){
						nextTimeStepLattice[i-pow(sidelength,d)]++;
					}
				}
			}
			koord[0] ++;
			for(int d=0;d<dimension;d++){
				if(koord[d]>=sidelength){
					koord[d+1]++;
					koord[d] = 0;
				}
			}

		}
		// std::cout << "Relaxed: " << relaxed << "\n";
	}while(!relaxed);
	return nextTimeStepLattice;
}



std::vector<int> SandPile::addSand(std::vector<int> & lat) {

	return addSand(lat,0.001);
}

std::vector<int> SandPile::addSand(std::vector<int>& lat, double probability) {
	for(int i=0;i<nrOfElements;i++){
		if(uniformRand(0,1)<probability) lat[i]++;
	}
	// add just one grain by one
	// lat[uniformRand(0,nrOfElements)]++;
	return lat;
}


const void SandPile::printLattice(const std::string name) {

	fprintLattice(name,lattice);
	// std::cout << " ...Finished Print" << std::endl;

}



const void SandPile::coutLattice2d() {
	coutLattice2d(lattice);
}
const void SandPile::coutLattice2d(std::vector<int> lat) {
	for(int i=0;i<nrOfElements;i++){
		std::cout << lat[i] << "\t";
		if(i%sidelength==sidelength-1) std::cout << std::endl;
	}
}



const void SandPile::fprintLattice(const std::string name,std::vector<int> & lat) {

	std::cout << "Printing file for " << dimension <<"-dim lattice in " << name << std::endl;

	std::fstream file;
	file.open(name.c_str(),std::ios::out);
	file << "# dimension = " << dimension << std::endl;
	file << "# x | y | z ... | value " << std::endl;
	int koord[dimension];

	for(int i=0;i<dimension;i++){
		koord[i] = 0;
	}


	for(int i=0;i<pow(sidelength,dimension);i++){
		for(int d=0;d<dimension;d++){
			file << koord[d] << "\t";
			// std::cout << koord[d] << "\t";
		}
		file << lat[i] << std::endl;
		// std::cout << lattice[i] << std::endl;
		koord[0] ++;
		for(int d=0;d<dimension;d++){
			if(koord[d]>=sidelength){
				koord[d+1]++;
				koord[d] = 0;
			}
		}
	}


	file.close();

}


void SandPile::neighbours(int point,int** neighbour,std::vector<int> & lat){

	// TODO make it without koord
	int koord[dimension];

	for(int i=0;i<dimension;i++){
		koord[i] = 0;
	}


	for(int i=0;i<point;i++){

		// std::cout << lattice[i] << std::endl;
		koord[0] ++;
		for(int d=0;d<dimension;d++){
			if(koord[d]>=sidelength){
				koord[d+1]++;
				koord[d] = 0;
			}
		}
	}



	for(int d=0;d<dimension;d++){
		int p1 = (int) (point+pow(sidelength,d));
		int p2 = (int) (point-pow(sidelength,d));
		if(!(koord[d] == sidelength-1)){
			neighbour[d*2]   = &lat[p1];
		}
		else neighbour[d*2] = NULL;

		if(!(koord[d] == 0)){
			neighbour[d*2+1] = &lat[p2];
		}
		else neighbour[d*2+1] = NULL;
	}


	// How to access:
//	int* neighbour[2*dimension];
//	int point = 5;
//	pile2d->neighbours(point,neighbour);
//	cout << "looking at point " << point << endl;
//	int toPrint;
//	for(int i=0;i<dimension*2;i++){
//		if(!(neighbour[i]==NULL)){
//		toPrint = *(neighbour[i]);
//		cout << toPrint;
//		}
//		else cout << "NAN";
//		// cout << "\t"<<  point+pow(sidelength,i) << endl;
//		cout << endl;
//	}


}

void SandPile::neighboursNumbers(int point,int neighbourNumbers[]){

	int koord[dimension];

	for(int i=0;i<dimension;i++){
		koord[i] = 0;
	}


	for(int i=0;i<point;i++){

		koord[0] ++;
		for(int d=0;d<dimension;d++){
			if(koord[d]>=sidelength){
				koord[d+1]++;
				koord[d] = 0;
			}
		}
	}


	for(int d=0;d<dimension;d++){
		int p1 = (int) (point+pow(sidelength,d));
		int p2 = (int) (point-pow(sidelength,d));
		if(!(koord[d] == sidelength-1)){
			neighbourNumbers[d*2]   = p1;
		}
		else neighbourNumbers[d*2] = -1;

		if(!(koord[d] == 0)){
			neighbourNumbers[d*2+1] = p2;
		}
		else neighbourNumbers[d*2+1] = -1;
	}


}


void SandPile::setNeighbours(int point,std::vector<int> & lat,int value){
	int* neighbour[2*dimension];
	neighbours(point,neighbour,lat);

	for(int i=0;i<dimension*2;i++){
		if(!(neighbour[i]==NULL)){
			// std::cout <<  "set neighbour to " << value << std::endl;
			*(neighbour[i]) = value;
		}
	}
}

void SandPile::increaseNeighbours(int point,std::vector<int> & lat){
	int* neighbour[2*dimension];
	neighbours(point,neighbour,lat);

	for(int i=0;i<dimension*2;i++){
		if(!(neighbour[i]==NULL)){
			// std::cout <<  "set neighbour to " << value << std::endl;
			*(neighbour[i]) = *(neighbour[i]) + 1;
		}
	}
}


void SandPile::testCritical(int point,std::vector<int> &lat,std::vector<int> &critical,std::vector<int> &allCritical){
	if(lat[point]>zk){

		lat[point]-=2*dimension;
		increaseNeighbours(point,lat);

		//std::cout << "Critical: " << std::endl;
		//coutLattice2d(lat);

		critical[point] = 1;
		setNeighbours(point,critical,1);
		allCritical[point] = 1;
		setNeighbours(point,allCritical,1);

		int neighbourNr[2*dimension];
		neighboursNumbers(point,neighbourNr);

		for(int i=0;i<2*dimension;i++){
			if(neighbourNr[i]>=0){
				testCritical(neighbourNr[i],lat,critical,allCritical);
			}
		}

	}
}


void SandPile::testCritical(int point,std::vector<int> &lat,std::vector<int> &critical){
	if(lat[point]>zk){

		lat[point]-=2*dimension;
		increaseNeighbours(point,lat);


		critical[point] = 1;
		// setNeighbours(point,critical,1);

		int neighbourNr[2*dimension];
		neighboursNumbers(point,neighbourNr);

		for(int i=0;i<2*dimension;i++){
			if(neighbourNr[i]>=0){
				testCritical(neighbourNr[i],lat,critical);
			}
		}

	}
}



const double SandPile::averageSlope(double& variance) {

	double mean = 0;
	double M2 = 0;
	double delta = 0;
	double x; // "Messwert..." 0 oder 1#
	double sampleVariance;
	double VarianceXbar = 0;


	for(int i=0;i<nrOfElements;i++){
		x = lattice[i];
		// calculating moving average + variance
		delta = x - mean;
		mean += (double) delta/(i+1);
		M2 += delta*(x-mean);

		sampleVariance = (double) M2/i;

		VarianceXbar = sampleVariance/i; // see script chapter 2 page 12.

	}

	variance = VarianceXbar;
	return mean;
}


const void SandPile::defineClusters() {
	std::vector<int> copiedLattice;
	std::vector<int> allCritical(nrOfElements);
	int clustersize;

	std::stringstream name;
	std::string filename;

	for(int i=0;i<nrOfElements;i++){
		std::vector<int> critical(nrOfElements);
		copiedLattice = lattice;
		copiedLattice[i]++;
        // coutLattice2d(copiedLattice);
		testCritical(i,copiedLattice,critical,allCritical);

		clustersize = 0;
		for(int j=0;j<nrOfElements;j++){
			clustersize += critical[i];
		}
		name.str("");
		name << i;
		filename = "./data/cluster"+name.str()+".dat";
		fprintLattice(filename,critical);
	}// End all Elements

	fprintLattice("data/AllCritical.dat",allCritical);
	std::cout << "Critical Lattice:" << std::endl;
	coutLattice2d(allCritical);
}

void SandPile::addSand(int point) {
	lattice[point]++;
}

void SandPile::addSandRandom() {
	lattice[uniformRand(0,nrOfElements)]++;
}



const int SandPile::clusterSize(int point) {
	std::vector<int> copiedLattice = lattice;
	int clustersize = 0;
	std::vector<int> critical(nrOfElements);

	copiedLattice[point]++;

	testCritical(point,copiedLattice,critical);
	for(int j=0;j<nrOfElements;j++){
		clustersize += critical[j];
	}


	return clustersize;
}


