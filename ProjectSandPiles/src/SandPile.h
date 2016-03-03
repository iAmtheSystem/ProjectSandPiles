/*
 * SandPile.h
 *
 *  Created on: Mar 2, 2016
 *      Author: simon
 */

#ifndef SANDPILE_H_
#define SANDPILE_H_

#include <vector>

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

};

#endif /* SANDPILE_H_ */
