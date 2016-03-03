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
	SandPile(int dimension,int sidelength,int zk);
	virtual ~SandPile();

	const void fillLatticeRand();
	const void setPoint(int point, int value);

	const void timestep();
	std::vector<int> relax(std::vector<int> &lat);
	std::vector<int> addSand(std::vector<int> & lat);
	std::vector<int> addSand(std::vector<int> & lat,double probability);


	const void printLattice();
	const void printLattice(const std::string name);
	const void coutLattice2d();
};

#endif /* SANDPILE_H_ */
