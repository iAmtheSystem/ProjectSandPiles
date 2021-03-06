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
#include "pointTwoD.h"

class SandPile {
private:
	std::vector<int> lattice;
	const int dimension;
	int sidelength;
	int nrOfElements;
	const int zk;

public:
	SandPile();
	SandPile(int dimension,int sidelength);
	SandPile(int dimension,int sidelength,  bool initialize);
	virtual ~SandPile();

	const void fillLatticeRand(const int from, const int to);
	const void setPoint(int point, int value);
	void neighbours(int point, int** neighbour,std::vector<int> & lat);
	void neighboursNumbers(int point,int neighbourNumbers[]);
	void setNeighbours(int point,std::vector<int> & lat,int value);
	void increaseNeighbours(int point);
	void increaseNeighbours(int point,std::vector<int> & lat);


	const void timestep();
	const void timestep(bool midpoint);
	const void relax();
	std::vector<int> relax(std::vector<int> &lat);
	void addSand(int point);
	void addSandRandom();
	std::vector<int> addSand(std::vector<int> & lat);
	std::vector<int> addSand(std::vector<int> & lat,double probability);

	int* clustersizeDistribution();

	const void printLattice();
	const void printLattice(const std::string name);
	const void fprintLattice(const std::string name, std::vector<int> &lat);

	const void coutLattice2d();
	const void coutLattice2d(std::vector<int> lat);
	const void coutLattice2d(std::vector<int> lat,int sideL);


	const double averageSlope();
	const double averageSlope(double& variance);

	const int randomCluster();

	void testCritical(int point,std::vector<int> &lat,std::vector<int> &critical);
	void testCritical(int point,std::vector<int> &lat,std::vector<int> &critical,int timesteps, int &timestepsMax, int &size);
	void testDissipation(int point,std::vector<int> &lat,std::vector<int> &critical, int timesteps, int &timestepsMax, int &size, std::vector<int> &dissipationRate);
	void testCritical(int point,std::vector<int> &lat,std::vector<int> &critical,std::vector<int> &allCritical);


	void caluclateClusterdata(int point,int &time, int &size, int &radius);
	void caluclateDissipationdata(int point,std::vector<int> &dissipationRate);


	void testReached(int point,std::vector<int> &lat,std::vector<int> &critical);
	const void defineClusters();
	std::vector<int> defineCluster(int point);
	std::vector<int> defineCluster(int point, int &time, double &distance);

	std::vector<int> defineReached(int point);
	const int clusterSize(int point);
	void clusterEdge(std::vector<int> critical,int startpoint);
	void clusterEdge(std::vector<int> critical,int startpoint,int clusterpoint);
	bool OutOfRange2d(int point);

	std::vector<int> SideZeros();
	std::vector<int> SideZeros(std::vector<int> vector);

	const int getPoint(const int point) const {
		return lattice[point];
	}

	const std::vector<int>& getLattice() const {
		return lattice;
	}

	void setLattice(const std::vector<int>& lattice) {
		setLattice(lattice,sidelength);
	}

	void setLattice(const std::vector<int>& lattice,int new_sidelength) {
		this->lattice = lattice;
		this->sidelength = new_sidelength;
		this->nrOfElements= pow(new_sidelength,dimension);
	}

	const int getZk() const {
		return zk;
	}

	int getNrOfElements() const {
		return nrOfElements;
	}
};

#endif /* SANDPILE_H_ */
