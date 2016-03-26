/*
 * pointTwoD.cpp
 *
 *  Created on: Mar 25, 2016
 *      Author: simon
 */

#include "pointTwoD.h"


pointTwoD::pointTwoD(int point,int sidelength):x(point%sidelength),y(point/sidelength),sidelength(sidelength) {
}


pointTwoD::~pointTwoD() {
	// TODO Auto-generated destructor stub
}

bool pointTwoD::isValid(int x, int y) {
	return x>=0 && x<sidelength && y>=0 && y<sidelength;
}
