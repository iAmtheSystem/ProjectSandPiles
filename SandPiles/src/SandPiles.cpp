//============================================================================
// Name        : SandPiles.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "simpleMath.h"
#include "SandPile.h"

int main() {
	cout << "S A N D   P I L E S" << endl;
	SandPile *pile2d = new SandPile(2,5,100);

	SandPile *pile3d = new SandPile(3,5,100);

	pile2d->printLattice("2d.dat");
	pile3d->printLattice();


	return 0;
}
