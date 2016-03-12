/*
 * SandPile.h
 *
 *  Created on: Mar 2, 2016
 *      Author: simon
 */

#ifndef SANDPILE_H_
#define SANDPILE_H_

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>

#include "simpleMath.h"

class SandPile {
private:
	std::vector<int> lattice;
	const int dimension;
	const int sidelength;
	const int nrOfElements;
	const int zk;

public:
	SandPile();
	SandPile(int dimension,int sidelength);
	virtual ~SandPile();

	const void fillLatticeRand(const int from, const int to);
	const void setPoint(int point, int value);
	void neighbours(int point, int** neighbour,std::vector<int> & lat);
	void neighboursNumbers(int point,int neighbourNumbers[]);
	void setNeighbours(int point,std::vector<int> & lat,int value);
	void increaseNeighbours(int point,std::vector<int> & lat);


	const void timestep();
	std::vector<int> relax(std::vector<int> &lat);
	std::vector<int> addSand(std::vector<int> & lat);
	std::vector<int> addSand(std::vector<int> & lat,double probability);


	const void printLattice();
	const void printLattice(const std::string name);
	const void fprintLattice(const std::string name, std::vector<int> &lat);

	const void coutLattice2d();
	const void coutLattice2d(std::vector<int> lat);


	void testCritical(int point,std::vector<int> &lat,std::vector<int> &critical,std::vector<int> &allCritical);
	const void defineClusters();

	const std::vector<int>& getLattice() const {
		return lattice;
	}

	void setLattice(const std::vector<int>& lattice) {
		this->lattice = lattice;
	}
};

#endif /* SANDPILE_H_ */
