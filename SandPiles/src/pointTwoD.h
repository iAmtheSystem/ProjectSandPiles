/*
 * pointTwoD.h
 *
 *  Created on: Mar 25, 2016
 *      Author: simon
 */

#ifndef POINTTWOD_H_
#define POINTTWOD_H_

class pointTwoD {
private:
	int x;
	int y;
	int sidelength;
public:
	pointTwoD(int point,int sidelength);
	virtual ~pointTwoD();

	bool isValid(int x,int y);

	int getX() const {
		return x;
	}

	void setX(int x) {
		this->x = x;
	}

	int getY() const {
		return y;
	}

	void setY(int y) {
		this->y = y;
	}
};

#endif /* POINTTWOD_H_ */
