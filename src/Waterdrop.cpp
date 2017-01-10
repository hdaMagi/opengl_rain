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
#include "BoundingBox.h"
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
//	this->radius = Random::randGlfloat(7.0f, 5.0f);
//	this->xpos = Random::randGlfloat(WINDOW_WIDTH - this->radius, this->radius);
//	this->ypos = Random::randGlfloat(WINDOW_HEIGHT - this->radius,
//			this->radius);
//	this->xSpeed = Random::randGlfloat(0.1, -0.1);
//	this->ySpeed = 0.1f;
	this->red = Random::randGlfloat(1.0f, 0.0f);
	this->green = Random::randGlfloat(1.0f, 0.0f);
	this->blue = 1.0f;
	this->transparency = 0.0f;
//	this->Deceleration = Random::randGlfloat(0.6f, 0.0f);
//	this->direction = 0; // gerade runter fließen

	b = new BoundingBox(vecMassPoints);
}

void Waterdrop::reset() {
	this->isActive = true;

	this->vecMassPoints.at(0).reset();
	this->vecMassPoints.at(1).reset();
	this->vecMassPoints.at(1).setYpos(
			this->vecMassPoints.at(0).getYpos() + 100);
	this->vecMassPoints.at(1).setXpos(this->vecMassPoints.at(0).getXpos());

	this->red = Random::randGlfloat(1.0f, 0.0f);
	this->green = Random::randGlfloat(1.0f, 0.0f);
	this->blue = 1.0f;
	this->transparency = 0.0f;

	for (std::vector<Waterdrop*>::iterator it =
			this->inactivatedDueToJoined.begin();
			it != this->inactivatedDueToJoined.end(); ++it) {
		Waterdrop & drop = **it;
		drop.reset();
	}
	this->inactivatedDueToJoined.clear();
	freeShape.clear();
}
//
///**
// * for free shape joining will be much more complicated so we're leaving the method here
// * drop2 is the looser
// */

void Waterdrop::joinDrops(Waterdrop* drop2) {
//	radius = sqrt(((pow(radius, 2) * PI) + (pow(radius, 2) * PI)) / PI);
//	drop2->setXpos(-200); // hiding "looser" joined drops
//
	drop2->vecMassPoints.at(0).setXpos(-1000);
	drop2->vecMassPoints.at(1).setXpos(-1000);
//	drop2->setTransparency(1.0f);
//
//	drop2->vecMassPoints.at(0).setIsActive(false);
//	drop2->vecMassPoints.at(1).setIsActive(false);
//
	drop2->setIsActive(false);
	this->inactivatedDueToJoined.push_back(drop2);

}

GLboolean Waterdrop::detectCollision(Waterdrop *drop2) {
	if (this->isActive && drop2->isActive) {
		// Collision x-axis?
		bool collisionX = this->b->p2.xcoord >= drop2->b->p1.xcoord
				&& this->b->p1.xcoord <= drop2->b->p2.xcoord;
		// Collision y-axis?
		bool collisionY = this->b->p2.ycoord >= drop2->b->p1.ycoord
				&& this->b->p1.ycoord <= drop2->b->p2.ycoord; //one.Position.y + one.Size.y >= two.Position.y &&
		if (collisionY && collisionX) {
			printf("%05f > %05f ycollision\n", this->b->p2.ycoord,
					drop2->b->p1.ycoord);
		}
		//	        two.Position.y + two.Size.y >= one.Position.y;
		// Collision only if on both axes
		return collisionX && collisionY;
	} else
		return false;
}

void Waterdrop::AxisSeparatePolygons(std::vector<point2d> whatever,
		std::vector<point2d> A, std::vector<point2d> B) {

}

/**
 * Assuming we're updating all positions at once.
 * return: 1 if update was succsessful
 * 		   0 if not (e.g. running out of canvas)
 */
bool Waterdrop::updatePosition() {
	bool ret = 1;

	freeShape.clear();
	point2d x;

	for (unsigned int i = 0; i < vecMassPoints.size(); i++) {
		ret &= vecMassPoints.at(i).updatePosition();
	}

	b->update(vecMassPoints);

	if (b->p2.ycoord < 0) {
		reset();
	}

// punkt oben
	x.xcoord = vecMassPoints.at(1).getXpos();
	x.ycoord = vecMassPoints.at(1).getYpos();
	freeShape.push_back(x);

	x.xcoord = vecMassPoints.at(1).getXpos();
	x.ycoord = vecMassPoints.at(1).getYpos() + vecMassPoints.at(1).getRadius();
	freeShape.push_back(x);

	for (GLfloat i = 0; i < PI / 2; i += 0.1f) {
		x.xcoord = vecMassPoints.at(1).getXpos()
				+ vecMassPoints.at(1).getRadius() * cos(i);
		x.ycoord = vecMassPoints.at(1).getYpos()
				+ vecMassPoints.at(1).getRadius() * sin(i);
		freeShape.push_back(x);
	}

	x.xcoord = vecMassPoints.at(1).getXpos() - vecMassPoints.at(1).getRadius();
	x.ycoord = vecMassPoints.at(1).getYpos();
	freeShape.push_back(x);

	for (GLfloat i = PI; i < PI + PI / 2; i += 0.1f) {
		x.xcoord = vecMassPoints.at(0).getXpos()
				+ vecMassPoints.at(1).getRadius() * cos(i);
		x.ycoord = vecMassPoints.at(0).getYpos()
				+ vecMassPoints.at(1).getRadius() * sin(i);
		freeShape.push_back(x);
	}

	x.xcoord = ((vecMassPoints.at(1).getXpos() + vecMassPoints.at(0).getXpos())
			/ 2) - vecMassPoints.at(0).getRadius();
	x.ycoord = ((vecMassPoints.at(1).getYpos() + vecMassPoints.at(0).getYpos())
			/ 2);
	freeShape.push_back(x);

	x.xcoord = vecMassPoints.at(0).getXpos() - vecMassPoints.at(0).getRadius();
	x.ycoord = vecMassPoints.at(0).getYpos();
	freeShape.push_back(x);

	for (GLfloat i = PI / 2; i < PI; i += 0.1f) {
		x.xcoord = vecMassPoints.at(1).getXpos()
				+ vecMassPoints.at(1).getRadius() * cos(i);
		x.ycoord = vecMassPoints.at(1).getYpos()
				+ vecMassPoints.at(1).getRadius() * sin(i);
		freeShape.push_back(x);
	}

	x.xcoord = vecMassPoints.at(0).getXpos();
	x.ycoord = vecMassPoints.at(0).getYpos() - vecMassPoints.at(0).getRadius();
	freeShape.push_back(x);

	x.xcoord = vecMassPoints.at(0).getXpos() + vecMassPoints.at(0).getRadius();
	x.ycoord = vecMassPoints.at(0).getYpos();
	freeShape.push_back(x);

	x.xcoord = ((vecMassPoints.at(1).getXpos() + vecMassPoints.at(0).getXpos())
			/ 2) + vecMassPoints.at(0).getRadius();
	x.ycoord = ((vecMassPoints.at(1).getYpos() + vecMassPoints.at(0).getYpos())
			/ 2);
	freeShape.push_back(x);

	x.xcoord = vecMassPoints.at(1).getXpos() + vecMassPoints.at(1).getRadius();
	x.ycoord = vecMassPoints.at(1).getYpos();
	freeShape.push_back(x);

	for (GLfloat i = PI + PI / 2; i < 2 * PI; i += 0.1f) {
		x.xcoord = vecMassPoints.at(0).getXpos()
				+ vecMassPoints.at(1).getRadius() * cos(i);
		x.ycoord = vecMassPoints.at(0).getYpos()
				+ vecMassPoints.at(1).getRadius() * sin(i);
		freeShape.push_back(x);
	}

	x.xcoord = vecMassPoints.at(1).getXpos();
	x.ycoord = vecMassPoints.at(1).getYpos() + vecMassPoints.at(1).getRadius();
	freeShape.push_back(x);

	return ret;
}

void Waterdrop::addJoinedDrop(Waterdrop* drop) {
	inactivatedDueToJoined.push_back(drop);
}

Waterdrop::~Waterdrop() {
}

