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
	// const int nrOfTimesteps = 1000;
	int dimension = 2;
	int sidelength = 5;

	cout << "S A N D   P I L E S ." << endl;


	SandPile *pile2d = new SandPile(dimension,sidelength);


//	stringstream name;
//	string filename;
//
//
//	// How to access neighbours:
//	pile2d->coutLattice2d();
//
//	int* neighbour[2*dimension];
//	int neighbourNr[2*dimension];
//	int point = 5;
//	vector<int> copy = pile2d->getLattice();
//	pile2d->neighbours(point,neighbour,copy);
//	pile2d->neighboursNumbers(point,neighbourNr);
//	cout << "looking at point " << point << endl;
//
//	cout << "with neighbours ";
//	for(int i=0;i<dimension*2;i++){
//		cout << neighbourNr[i] << "\t";
//	}
//	cout << endl;
//
//	int toPrint;
//	for(int i=0;i<dimension*2;i++){
//		if(!(neighbour[i]==NULL)){
//		toPrint = *(neighbour[i]);
//		cout << toPrint;
//		}
//		else cout << "NAN";
//		// cout << "\t"<<  point+pow(sidelength,i) << endl;
//		cout << endl;
//	}
//	vector<int> lat = pile2d->getLattice();
//	pile2d->increaseNeighbours(point,lat);
//
//	pile2d->setLattice(lat);
//
//	// pile2d->timestep();
//	pile2d->coutLattice2d();
//
////	cout << "DEBUG 1" << endl;
////	std::vector<int> test(10);
////	for(int i=0;i<10;i++){
////		cout << "test " << i << " includes " << test[i] << endl;
////	}
//
//	cout << "DEBUG2.a" << endl;
////	for(int i=0;i<nrOfTimesteps;i++){
////		// cout << "Timestep " << i << endl;
////		name.str("");
////		name << i;
////		filename = "./data/step"+name.str()+".dat";
////		for(int j=0;j<1;j++){
////			pile2d->timestep();
////		}
////		pile2d->printLattice(filename);
////	}

	pile2d->coutLattice2d();
	pile2d->printLattice("./data/Lattice.dat");
	cout << "Define Clusters" << endl;
	pile2d->defineClusters();


	cout << "Programm finished!" << endl;
	return 0;
}
