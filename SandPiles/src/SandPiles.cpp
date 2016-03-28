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

#include "Distribution.h"
#include "averageSlope.h"

int main() {
	// const int nrOfTimesteps = 1000;
	int dimension = 4;
	int sidelength = 10;
	int nrOfElements = pow(sidelength,dimension);

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

//	pile2d->coutLattice2d();
//	double variance = 0;
//	cout << "Average = " << pile2d->averageSlope(variance);
//	cout << " Variance = " << variance << endl;
//
//
//	pile2d->printLattice("./data/Lattice.dat");
//	cout << "Define Clusters" << endl;
//	pile2d->defineClusters();


//	Distribution *sizeDistribution = new Distribution(dimension,sidelength);
//
//	cout << "Calculating Distribution" << endl;
//	sizeDistribution->calculateDistribution(10000);
//	cout << "\t... calculated -> continue with printing" << endl;
//	sizeDistribution->fprintData();

//	averageSlope *avSlope = new averageSlope();
//	avSlope->determineAverageSlope(2,false,false,true);

//	double x[] = {5,5,6,6,5};
//	double variances[] = {1,1,2,1.5,1};
//	double x_median = 0;
//	double x_var = 0;
//
//	x_median = arithmeticMedianByVariance(5,x,variances,x_var);
//
//	cout << "x = " << x_median << " +/- " << x_var << endl;

//	averageSlope *avSlope = new averageSlope();
//	avSlope->averageSlopeOfSize();


//	pile2d->coutLattice2d();
//	double var = 3;
//	cout << "Average Slope = "<< pile2d->averageSlope(var) << " +/- " << endl;
//	cout << var << endl;
//
//	pile2d->setPoint(7,3);
//	pile2d->setPoint(8,3);
//	pile2d->setPoint(9,3);
//	pile2d->setPoint(4,3);
//	pile2d->setPoint(5,3);

//	pile2d->coutLattice2d();
//
//	int new_nrOfElements = pow(sidelength+2,dimension);
//	std::vector<int> vec_new(new_nrOfElements);
//	vec_new = pile2d->SideZeros();
//
//	cout << "New Lattice with side Zeros "<< endl;
//
//	pile2d->setLattice(vec_new,sidelength+2);
//	pile2d->coutLattice2d(vec_new);
//	cout << "\n With Cluster \n";
//	vec_new=pile2d->defineCluster(17);
//	pile2d->coutLattice2d( vec_new );
//	pile2d->printLattice("./data/Lattice2.dat");
//	pile2d->fprintLattice("./data/Cluster2.dat",vec_new);
//
//	cout << "Set Edges" << endl;
//	pile2d->clusterEdge( vec_new,11);

//	averageSlope *avSlope = new averageSlope();
//	avSlope->averageSlopeOfClusterReachedAndLattice();


//	int koord1[2];
//	int koord2[2];
//
//	cout << "getting coordinates" << endl;
//	coord(2,4,10,koord1);
//	coord(2,4,0,koord2);
//
//	cout << radius(2,koord1,koord2) << endl;


//	int time = 0;
//	double distance = 0;
//	std::vector<int> vec_new(nrOfElements);
//	int clusterpos = pile2d->randomCluster();
//
//	vec_new=pile2d->defineCluster(clusterpos,time,distance);
//	cout << "Lattice\n";
//	pile2d->coutLattice2d();
//
//	int koord[2];
//	coord(dimension,sidelength,clusterpos,koord);
//	cout << "Pos = " << clusterpos << " Clusterkoords: X = " << koord[0] << "\tY = " << koord[1] << endl;
//	pile2d->coutLattice2d(vec_new);
//	cout << "with avalanche time " << time << " and maxDistance " << distance << endl;


	cout << "Calculate Distribution" << endl;
	Distribution* distri = new Distribution(dimension,sidelength,256);
	distri->calculateDissipationRateDistribution()();
	distri->fprintADissipation();

	cout << "Programm finished!" << endl;
	return 0;
}
