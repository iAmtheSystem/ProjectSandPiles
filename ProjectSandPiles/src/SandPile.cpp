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
	lattice.reserve(dimension*sidelength);
	fillLatticeRand();
}

SandPile::~SandPile() {
	// TODO Auto-generated destructor stub
}

const void SandPile::fillLatticeRand() {
}

const void SandPile::timestep() {
}
