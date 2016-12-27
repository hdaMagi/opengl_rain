/*
 * BoundingBox.h
 *
 *  Created on: 22.12.2016
 *      Author: jannis
 */

#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_

#include <vector>

#include "MassPoint.h"
#include "Globals.h"

class BoundingBox {
public:
	BoundingBox();
	BoundingBox(std::vector<MassPoint> vecMassPoints);
	void update(std::vector<MassPoint> vecMassPoints);
	point2d pAC;
	point2d pAF;
	point2d p1;
	point2d p2;
	virtual ~BoundingBox();
};

#endif /* BOUNDINGBOX_H_ */
