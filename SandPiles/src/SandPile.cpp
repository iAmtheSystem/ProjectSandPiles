/*
 * SandPile.cpp
 *
 *  Created on: Mar 2, 2016
 *      Author: simon
 */

#include "SandPile.h"

SandPile::SandPile():
	dimension(0),sidelength(0),nrOfElements(0),zk(0) {
}

SandPile::SandPile(int dimension, int sidelength, int zk = 100):
		dimension(dimension),sidelength(sidelength),nrOfElements(pow(sidelength,dimension)),zk(zk) {
	lattice = std::vector<int> (nrOfElements);
	fillLatticeRand();
}

SandPile::~SandPile() {
	// TODO Auto-generated destructor stub
}

const void SandPile::fillLatticeRand() {
	for(int i=0;i<pow(sidelength,dimension);i++){
		lattice[i] = uniformRand(0,zk-1); // zk >= 1
	}
}

const void SandPile::timestep() {
	//std::cout << "\trelax" << std::endl;
	// relax configuration simultaneously
	lattice = relax(lattice);
	// 1. add random sand
	// TODO
	// std::cout << "\taddSand" << std::endl;
	lattice=addSand(lattice);
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


			if(lat[i]>=zk){
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

	return addSand(lat,0.1);
}

std::vector<int> SandPile::addSand(std::vector<int>& lat, double probability) {
//	for(int i=0;i<nrOfElements;i++){
//		if(uniformRand(0,1)<probability) lat[i]++;
//	}
	// add just one grain by one
	lat[uniformRand(0,nrOfElements)]++;
	return lat;
}


const void SandPile::printLattice(const std::string name) {
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
		file << lattice[i] << std::endl;
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
	// std::cout << " ...Finished Print" << std::endl;

}



const void SandPile::coutLattice2d() {
	for(int i=0;i<nrOfElements;i++){
		std::cout << lattice[i] << "\t";
		if(i%sidelength==sidelength-1) std::cout << std::endl;
	}
}
