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
//	this->radius = Random::randGlfloat(7.0f, 5.0f);
//	this->xpos = Random::randGlfloat(WINDOW_WIDTH - this->radius, this->radius);
//	this->ypos = Random::randGlfloat(WINDOW_HEIGHT - this->radius,
//			this->radius);
//	this->xSpeed = Random::randGlfloat(0.1, -0.1);
//	this->ySpeed = 0.1f;
	this->red = Random::randGlfloat(1.0f, 0.0f);
	this->green = Random::randGlfloat(1.0f, 0.0f);
	this->blue = 1.0f;
//	this->Deceleration = Random::randGlfloat(0.6f, 0.0f);
//	this->direction = 0; // gerade runter fließen
}

//void Waterdrop::reset() {
//	this->isActive = true;
//	this->radius = Random::randGlfloat(7.0f, 5.0f);
//	this->xpos = Random::randGlfloat(WINDOW_WIDTH - this->radius, this->radius);
//	this->ypos = WINDOW_HEIGHT;
//	this->xSpeed = Random::randGlfloat(0.1, -0.1);
//	this->ySpeed = 0.1f;
//	this->red = Random::randGlfloat(1.0f, 0.0f);
//	this->green = Random::randGlfloat(1.0f, 0.0f);
//	this->blue = 1.0f;
//	this->Deceleration = Random::randGlfloat(0.6f, 0.0f);
//	this->direction = 0;
//	for (std::vector<Waterdrop*>::iterator it =
//			this->inactivatedDueToJoined.begin();
//			it != this->inactivatedDueToJoined.end(); ++it) {
//		Waterdrop & drop = **it;
//		drop.reset();
//	}
//	this->inactivatedDueToJoined.clear();
//	freeShape.clear();
//}
//
///**
// * for free shape joining will be much more complicated so we're leaving the method here
// * drop2 is the looser
// */
void Waterdrop::joinDrops(Waterdrop* drop2) {
//	radius = sqrt(((pow(radius, 2) * PI) + (pow(radius, 2) * PI)) / PI);
//	drop2->setIsActive(false);
//	drop2->setXpos(-200); // hiding "looser" joined drops
//	this->inactivatedDueToJoined.push_back(drop2);
}

bool Waterdrop::detectCollision(Waterdrop *drop2) {
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

/**
 * Assuming we're updating all positions at once.
 * return: 1 if update was succsessful
 * 		   0 if not (e.g. running out of canvas)
 */
bool Waterdrop::updatePosition() {
	bool ret = 1;

	freeShape.clear();

	point2d x;
	int iter = 0;

	for (unsigned int i = 0; i < vecMassPoints.size(); i++) {
		ret &= vecMassPoints.at(i).updatePosition();
	}

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

	for (GLfloat i= 0; i <  PI / 2; i += 0.1f) {
		x.xcoord = vecMassPoints.at(1).getXpos() + vecMassPoints.at(1).getRadius() * cos(i);
		x.ycoord = vecMassPoints.at(1).getYpos() + vecMassPoints.at(1).getRadius() * sin(i);
		freeShape.push_back(x);
	}

	x.xcoord = vecMassPoints.at(1).getXpos() - vecMassPoints.at(1).getRadius();
	x.ycoord = vecMassPoints.at(1).getYpos();
	freeShape.push_back(x);


	for (GLfloat i= PI; i <  PI + PI / 2; i += 0.1f) {
		x.xcoord = vecMassPoints.at(0).getXpos() + vecMassPoints.at(1).getRadius() * cos(i);
		x.ycoord = vecMassPoints.at(0).getYpos() + vecMassPoints.at(1).getRadius() * sin(i);
		freeShape.push_back(x);
	}


	x.xcoord = ((vecMassPoints.at(1).getXpos() + vecMassPoints.at(0).getXpos()) / 2) - vecMassPoints.at(0).getRadius();
	x.ycoord = ((vecMassPoints.at(1).getYpos() + vecMassPoints.at(0).getYpos()) / 2);
	freeShape.push_back(x);



	x.xcoord = vecMassPoints.at(0).getXpos() - vecMassPoints.at(0).getRadius();
	x.ycoord = vecMassPoints.at(0).getYpos();
	freeShape.push_back(x);

	for (GLfloat i= PI /2; i <  PI; i += 0.1f) {
		x.xcoord = vecMassPoints.at(1).getXpos() + vecMassPoints.at(1).getRadius() * cos(i);
		x.ycoord = vecMassPoints.at(1).getYpos() + vecMassPoints.at(1).getRadius() * sin(i);
		freeShape.push_back(x);
	}

	x.xcoord = vecMassPoints.at(0).getXpos();
	x.ycoord = vecMassPoints.at(0).getYpos() - vecMassPoints.at(0).getRadius();
	freeShape.push_back(x);




	x.xcoord = vecMassPoints.at(0).getXpos() + vecMassPoints.at(0).getRadius();
	x.ycoord = vecMassPoints.at(0).getYpos();
	freeShape.push_back(x);

	x.xcoord = ((vecMassPoints.at(1).getXpos() + vecMassPoints.at(0).getXpos()) / 2) + vecMassPoints.at(0).getRadius();
	x.ycoord = ((vecMassPoints.at(1).getYpos() + vecMassPoints.at(0).getYpos()) / 2);
	freeShape.push_back(x);

	x.xcoord = vecMassPoints.at(1).getXpos() + vecMassPoints.at(1).getRadius();
	x.ycoord = vecMassPoints.at(1).getYpos();
	freeShape.push_back(x);

	for (GLfloat i= PI + PI /2; i <  2*PI; i += 0.1f) {
		x.xcoord = vecMassPoints.at(0).getXpos() + vecMassPoints.at(1).getRadius() * cos(i);
		x.ycoord = vecMassPoints.at(0).getYpos() + vecMassPoints.at(1).getRadius() * sin(i);
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
//
///**
// * @todo: rand --> random class
// */
//int Waterdrop::Direction(void) {
//	int temp = 0;
//	const int min = 1;
//	const int max = 1;
//	switch (this->direction) {
//	case -1: //links fließen
//	{
//		temp = min + (rand() % 100);
//		break;
//	}
//	case 1: //rechts fliessen
//	{
//		temp = (rand() % (100 - max));
//		break;
//	}
//	default: {
//		temp = (rand() % 100);
//		break;
//	}
//	}
//
//	if (temp < min) {
//		direction -= 1;
//	} else if (temp > (100 - 1 - max)) {
//		direction += 1;
//	}
//	return direction;
//}

void Waterdrop::addJoinedDrop(Waterdrop* drop) {
	inactivatedDueToJoined.push_back(drop);
}

Waterdrop::~Waterdrop() {
}

