/*
 * BoundingBox.cpp
 *
 *  Created on: 22.12.2016
 *      Author: jannis
 */

#include "../include/BoundingBox.h"
#include "../include/Globals.h"
#include <math.h>

BoundingBox::BoundingBox() {
	// TODO Auto-generated constructor stub

}

BoundingBox::BoundingBox(std::vector<MassPoint> vecMassPoints) {

	update(vecMassPoints);

}

void BoundingBox::update(std::vector<MassPoint> vecMassPoints) {
	point2d actualClosest;
	actualClosest.xcoord = 99999999999;
	actualClosest.ycoord = 99999999999;
	GLfloat actualClosestRadius = 0;
	point2d actualFarest;
	actualFarest.xcoord = 1;
	actualFarest.ycoord = 1;
	GLfloat actualFarestRadius = 0;

	for (std::vector<MassPoint>::iterator iter = vecMassPoints.begin();
			iter != vecMassPoints.end(); ++iter) {
		MassPoint & mp = *iter;
		GLfloat betMP = sqrt(pow(mp.getXpos(), 2) + pow(mp.getYpos(), 2));
		GLfloat betAC = sqrt(
				pow(actualClosest.xcoord, 2) + pow(actualClosest.ycoord, 2));
		GLfloat betAF = sqrt(
				pow(actualFarest.xcoord, 2) + pow(actualFarest.ycoord, 2));

		if (betMP < betAC) {
			betAC = betMP;
			actualClosestRadius = mp.getRadius();
			actualClosest.xcoord = mp.getXpos();
			actualClosest.ycoord = mp.getYpos() - mp.getRadius();
		}

		if (betMP > betAF) {
			betAF = betMP;
			actualFarestRadius = mp.getRadius();
			actualFarest.xcoord = mp.getXpos();
			actualFarest.ycoord = mp.getYpos() + mp.getRadius();
		}
	}

	if (actualClosest.xcoord + actualClosestRadius
			<= actualFarest.xcoord + actualFarestRadius) {
		pAC.xcoord = actualClosest.xcoord - actualClosestRadius;
		pAF.xcoord = actualFarest.xcoord + actualFarestRadius;
	} else{
		pAC.xcoord = actualClosest.xcoord + actualClosestRadius;
		pAF.xcoord = actualFarest.xcoord - actualFarestRadius;
	}
	pAC.ycoord = actualClosest.ycoord;
	pAF.ycoord = actualFarest.ycoord;

	// make sure p1 is the "minor" point and p2 is the "major"
	p1.xcoord = std::min(pAC.xcoord, pAF.xcoord);
	p1.ycoord = std::min(pAC.ycoord, pAF.ycoord);
	p2.xcoord = std::max(pAC.xcoord, pAF.xcoord);
	p2.ycoord = std::max(pAC.ycoord, pAF.ycoord);


}

BoundingBox::~BoundingBox() {
	// TODO Auto-generated destructor stub
}

