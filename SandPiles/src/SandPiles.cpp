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
	int dimension = 2;
	int sidelength = 5;
	cout << "S A N D   P I L E S" << endl;

	SandPile *pile2d = new SandPile(dimension,sidelength);


	stringstream name;
	string filename;


	// How to access neighbours:
	pile2d->coutLattice2d();

	int* neighbour[2*dimension];
	int point = 5;
	pile2d->neighbours(point,neighbour);
	cout << "looking at point " << point << endl;
	int toPrint;
	for(int i=0;i<dimension*2;i++){
		if(!(neighbour[i]==NULL)){
		toPrint = *(neighbour[i]);
		cout << toPrint;
		}
		else cout << "NAN";
		// cout << "\t"<<  point+pow(sidelength,i) << endl;
		cout << endl;
	}
	cout << "DEBUG2" << endl;
//	for(int i=0;i<nrOfTimesteps;i++){
//		// cout << "Timestep " << i << endl;
//		name.str("");
//		name << i;
//		filename = "./data/step"+name.str()+".dat";
//		for(int j=0;j<1;j++){
//			pile2d->timestep();
//		}
//		pile2d->printLattice(filename);
//	}


	cout << "Programm finished!" << endl;
	return 0;
}
