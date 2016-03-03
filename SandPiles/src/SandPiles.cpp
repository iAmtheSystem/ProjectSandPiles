//============================================================================
// Name        : SandPiles.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "simpleMath.h"
#include "SandPile.h"

int main() {
	const int nrOfTimesteps = 1000;
	cout << "S A N D   P I L E S" << endl;
	SandPile *pile2d = new SandPile(2,20,5);


	stringstream name;
	string filename;
	for(int i=0;i<nrOfTimesteps;i++){
		name.str("");
		name << i;
		filename = "./data/step"+name.str()+".dat";
		pile2d->timestep();
		pile2d->printLattice(filename);
	}



	return 0;
}
