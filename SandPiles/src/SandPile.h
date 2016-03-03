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
	const int zk;

public:
	SandPile();
	SandPile(int dimension,int sidelength,int zk);
	virtual ~SandPile();

	const void fillLatticeRand();
	const void timestep();

	const void printLattice();
	const void printLattice(const std::string name);
};

#endif /* SANDPILE_H_ */
