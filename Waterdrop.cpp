/*
 * Waterdrop.cpp
 *
 *  Created on: 31.10.2016
 *      Author: kiara
 */

#include <math.h>

#include "Waterdrop.h"
#include "Globals.h"
#include "Random.h"
#include "Waterdrops.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

Waterdrop::Waterdrop() {
	MassPoint x;
	this->vecMassPoints.push_back(x);
	MassPoint y;
	y.setYpos(x.getYpos() + 100);
	y.setXpos(x.getXpos());
	this->vecMassPoints.push_back(y);
	this->isActive = true;
	this->red = Random::randGlfloat(1.0f, 0.0f);
	this->green = Random::randGlfloat(1.0f, 0.0f);
	this->blue = 1.0f;
}

///**
// * for free shape joining will be much more complicated so we're leaving the method here
// * drop2 is the looser
// */
void Waterdrop::joinDrops(Waterdrop* drop2) {}

bool Waterdrop::detectCollision(Waterdrop *drop2) {
	return false;
}

/**
 * Assuming we're updating all positions at once.
 * return: 1 if update was succsessful
 * 		   0 if not (e.g. running out of canvas)
 */
bool Waterdrop::updatePosition(GlassPanel* gp) {
	bool ret = 1;
	freeShape.clear();

	point2d x;
	for (unsigned int i = 0; i < vecMassPoints.size(); i++) {
		MassPoint mp = vecMassPoints.at(i);
		GLfloat speed = gp->calcSpeed(mp.getVolumen(), (int)mp.getXpos(), (int)mp.getYpos());
		speed = speed / 10.f;
		mp.setxSpeed(speed + mp.getxSpeed());
		mp.setySpeed(speed + mp.getySpeed());
		ret &= mp.updatePosition();
	}

// lower point
	x.xcoord = vecMassPoints.at(0).getXpos();
	x.ycoord = vecMassPoints.at(0).getYpos();
	freeShape.push_back(x);

	x.xcoord = vecMassPoints.at(1).getXpos();
	x.ycoord = vecMassPoints.at(1).getYpos();
	freeShape.push_back(x);

	x.xcoord = ((vecMassPoints.at(1).getXpos() + vecMassPoints.at(0).getXpos()) / 2) - vecMassPoints.at(0).getRadius();
	x.ycoord = ((vecMassPoints.at(1).getYpos() + vecMassPoints.at(0).getYpos()) / 2);
	freeShape.push_back(x);

	x.xcoord = vecMassPoints.at(0).getXpos() - vecMassPoints.at(0).getRadius();
	x.ycoord = vecMassPoints.at(0).getYpos();
	freeShape.push_back(x);

	x.xcoord = vecMassPoints.at(0).getXpos();
	x.ycoord = vecMassPoints.at(0).getYpos() - vecMassPoints.at(0).getRadius();
	freeShape.push_back(x);

	x.xcoord = vecMassPoints.at(0).getXpos() + vecMassPoints.at(0).getRadius();
	x.ycoord = vecMassPoints.at(0).getYpos();
	freeShape.push_back(x);

	x.xcoord = ((vecMassPoints.at(1).getXpos() + vecMassPoints.at(0).getXpos()) / 2) + vecMassPoints.at(0).getRadius();
	x.ycoord = ((vecMassPoints.at(1).getYpos() + vecMassPoints.at(0).getYpos()) / 2);
	freeShape.push_back(x);

	x.xcoord = vecMassPoints.at(1).getXpos();
	x.ycoord = vecMassPoints.at(1).getYpos();
	freeShape.push_back(x);

	return ret;
}

void Waterdrop::addJoinedDrop(Waterdrop* drop) {
	inactivatedDueToJoined.push_back(drop);
}

Waterdrop::~Waterdrop() {
}

GLfloat Waterdrop::getMass() {
	GLfloat mass = 0;
	for (unsigned int i = 0; i < vecMassPoints.size(); i++) {
		mass += this->vecMassPoints[i].getVolumen();
	}
	return mass;
}
