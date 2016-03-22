/*
 * averageSlope.cpp
 *
 *  Created on: Mar 22, 2016
 *      Author: simon
 */

#include "averageSlope.h"

averageSlope::averageSlope() {
	// TODO Auto-generated constructor stub

}

averageSlope::~averageSlope() {
	// TODO Auto-generated destructor stub
}

const void averageSlope::determineAverageSlope(int dim) const {


}

const void averageSlope::fillingFromZero(int dim, bool printLattice, bool justMidpoint) const {
	int sidelength = 20;
	int nrOfElements = pow(sidelength,dim);
	std::cout << "filling from Zero" << std::endl;
	SandPile *pile = new SandPile(dim,sidelength,false);
	double avSlope;
	double slopeVariance;

	std::stringstream name;
	std::string filename;

	std::fstream file;
	file.open("./data/averageSlope/convergence.dat",std::ios::out);
	file << "# timesteps | averageSlope | averageSlopeVariance" << std::endl;
	avSlope = pile->averageSlope(slopeVariance);
	file << 0 << "\t" << avSlope << "\t" << slopeVariance << "\n";

	if(printLattice) pile->printLattice("./data/averageSlope/step0.dat");

	for(int t=1;t<nrOfElements*100;t++){
		std::cout << "timestep " << t << std::endl;
		pile->timestep(justMidpoint);
		if(printLattice){
		// Filename
			name.str("");
			name << t;
			filename = "./data/averageSlope/step"+name.str()+".dat";
			pile->printLattice(filename);
		}
		avSlope = pile->averageSlope(slopeVariance);
		file << t << "\t" << avSlope << "\t" << slopeVariance << "\n";
	}

	file.close();
	free(pile);
}
