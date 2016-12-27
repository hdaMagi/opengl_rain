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
	this->red = Random::randGlfloat(1.0f, 0.0f);
	this->green = Random::randGlfloat(1.0f, 0.0f);
	this->blue = 1.0f;
//	this->Deceleration = Random::randGlfloat(0.6f, 0.0f);
//	this->direction = 0; // gerade runter fließen

	b = new BoundingBox(vecMassPoints);
}

///**
// * for free shape joining will be much more complicated so we're leaving the method here
// * drop2 is the looser
// */

void Waterdrop::joinDrops(Waterdrop* drop2) {
//	radius = sqrt(((pow(radius, 2) * PI) + (pow(radius, 2) * PI)) / PI);
	drop2->setIsActive(false);
//	drop2->setXpos(-200); // hiding "looser" joined drops
	this->inactivatedDueToJoined.push_back(drop2);
}

GLboolean Waterdrop::detectCollision(Waterdrop *drop2) {

	// Collision x-axis?
	bool collisionX = this->b->p2.xcoord >= drop2->b->p1.xcoord && this->b->p1.xcoord <= drop2->b->p2.xcoord;
	// Collision y-axis?
	bool collisionY = this->b->p2.ycoord >= drop2->b->p1.ycoord && this->b->p1.ycoord <= drop2->b->p2.ycoord; //one.Position.y + one.Size.y >= two.Position.y &&
	if (collisionY && collisionX) {
		printf("%05f > %05f ycollision\n", this->b->p2.ycoord, drop2->b->p1.ycoord);
	}
	//	        two.Position.y + two.Size.y >= one.Position.y;
	// Collision only if on both axes
	return collisionX && collisionY;

//	float dst = sqrt(
//			pow((drop2->getXpos() - this->getXpos()), 2)
//					+ pow((drop2->getYpos() - this->getYpos()), 2));
//	float dst2 = dst - this->getRadius() - drop2->getRadius();
//
////	printf(
////			"D1X: %02f, \t D1Y: %02f, \t D2X: %02f, \t D2Y: %02f\n",
////			drop1->xpos, drop1->ypos, drop2->xpos, drop2->ypos);
//	if (dst2 < 0) {
////		printf("collided\n");
//		return true;
//	}
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
bool Waterdrop::updatePosition(GlassPanel* gp) {
	bool ret = 1;
	freeShape.clear();
	point2d x;

	for (unsigned int i = 0; i < vecMassPoints.size(); i++) {
		MassPoint mp = vecMassPoints.at(i);
		GLfloat speed = gp->calcSpeed(mp.getVolumen(), (int)mp.getXpos(), (int)mp.getYpos());
		speed = speed / 100.f;
		/*mp.setxSpeed(speed + mp.getxSpeed());
		mp.setySpeed(speed + mp.getySpeed());*/
		vecMassPoints.at(i).setxSpeed(speed);
		vecMassPoints.at(i).setySpeed(speed);
		ret &= vecMassPoints.at(i).updatePosition();
	}

	b->update(vecMassPoints);
//	// informal codings
//	// upper point
//	x.xcoord = vecMassPoints.at(0).getXpos();
//	x.ycoord = vecMassPoints.at(0).getYpos();
//	freeShape.push_back(x);

//	// left middle point
//	x.xcoord = (vecMassPoints.at(0).getXpos() + vecMassPoints.at(1).getXpos()) / 2;
//	x.ycoord = vecMassPoints.at(1).getYpos() - vecMassPoints.at(1).getRadius();
//	freeShape.push_back(x);

// lower point

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

//	x.xcoord = vecMassPoints.at(1).getXpos();
//	x.ycoord = vecMassPoints.at(1).getYpos() - vecMassPoints.at(1).getRadius();
//	freeShape.push_back(x);

//	x.xcoord = vecMassPoints.at(1).getXpos();
//	x.ycoord = vecMassPoints.at(1).getYpos() - vecMassPoints.at(1).getRadius();
//	freeShape.push_back(x);
//	x.xcoord =  (vecMassPoints.at(0).getXpos() + vecMassPoints.at(1).getXpos()) / 2;
//	x.ycoord = vecMassPoints.at(1).getYpos() + vecMassPoints.at(1).getRadius();
//	freeShape.push_back(x);

//

//		for (GLfloat j = 0; j < PI; j = j + 0.1) {
//			if (iter % 2 == 0) {
//				x.xcoord = vecMassPoints.at(i).getXpos() + sin(j) * 10;
//			} else {
//				x.xcoord = vecMassPoints.at(i).getXpos() - sin(j) * 10;
//			}
//			if (i < PI / 2) {
//				x.ycoord = vecMassPoints.at(i).getYpos() - j * (1 - iter);
//			} else {
//				x.ycoord = vecMassPoints.at(i).getYpos() + j * iter;
//			}
//			freeShape.push_back(x);
//			iter++;
//		}
//}
	return ret;
}

void Waterdrop::addJoinedDrop(Waterdrop* drop) {
	inactivatedDueToJoined.push_back(drop);
}

Waterdrop::~Waterdrop() {
}
