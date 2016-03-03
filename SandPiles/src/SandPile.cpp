/*
 * SandPile.cpp
 *
 *  Created on: Mar 2, 2016
 *      Author: simon
 */

#include "SandPile.h"

SandPile::SandPile():
	dimension(0),sidelength(0),zk(0) {
}

SandPile::SandPile(int dimension, int sidelength, int zk = 100):
		dimension(dimension),sidelength(sidelength),zk(zk) {
	lattice.reserve(pow(sidelength,dimension));
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
}

const void SandPile::printLattice() {
	printLattice("sandPile.dat");
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
