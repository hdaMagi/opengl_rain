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

Waterdrop::Waterdrop() {
	this->isActive = true;
	this->radius = Random::randGlfloat(7.0f, 5.0f);
	this->xpos = Random::randGlfloat(WINDOW_WIDTH - this->radius, this->radius);
	this->ypos = Random::randGlfloat(WINDOW_HEIGHT - this->radius,
			this->radius);
	this->xSpeed = Random::randGlfloat(0.1, -0.1);
	this->ySpeed = 0.1f;
	this->red = Random::randGlfloat(1.0f, 0.0f);
	this->green = Random::randGlfloat(1.0f, 0.0f);
	this->blue = 1.0f;
	this->Acceleration = 0.0f;
	this->Deceleration = Random::randGlfloat(0.6f, 0.0f);
	this->Scalez = 0.0f;
	this->direction = 0; // gerade runter fließen

}

void Waterdrop::reset() {
	this->isActive = true;
	this->radius = Random::randGlfloat(7.0f, 5.0f);
	this->xpos = Random::randGlfloat(WINDOW_WIDTH - this->radius, this->radius);
	this->ypos = WINDOW_HEIGHT;
	this->xSpeed = Random::randGlfloat(0.1, -0.1);
	this->ySpeed = 0.1f;
	this->red = Random::randGlfloat(1.0f, 0.0f);
	this->green = Random::randGlfloat(1.0f, 0.0f);
	this->blue = 1.0f;
	this->Acceleration = 0.0f;
	this->Deceleration = Random::randGlfloat(0.6f, 0.0f);
	this->Scalez = 0.0f;
	this->direction = 0;
	for (std::vector<Waterdrop*>::iterator it =
			this->inactivatedDueToJoined.begin();
			it != this->inactivatedDueToJoined.end(); ++it) {
		Waterdrop & drop = **it;
		drop.reset();
	}
	this->inactivatedDueToJoined.clear();
freeShape.clear();
}

/**
 * for free shape joining will be much more complicated so we're leaving the method here
 * drop2 is the looser
 */
void Waterdrop::joinDrops(Waterdrop* drop2) {
//	printf("JOINING");

	radius = sqrt(((pow(radius, 2) * PI) + (pow(radius, 2) * PI)) / PI);
	drop2->setIsActive(false);
	drop2->setXpos(-200); // hiding "looser" joined drops
	this->inactivatedDueToJoined.push_back(drop2);

}

bool Waterdrop::detectCollision(Waterdrop *drop2) {
	float dst = sqrt(
			pow((drop2->getXpos() - this->getXpos()), 2)
					+ pow((drop2->getYpos() - this->getYpos()), 2));
	float dst2 = dst - this->getRadius() - drop2->getRadius();

//	printf(
//			"D1X: %02f, \t D1Y: %02f, \t D2X: %02f, \t D2Y: %02f\n",
//			drop1->xpos, drop1->ypos, drop2->xpos, drop2->ypos);
	if (dst2 < 0) {
//		printf("collided\n");
		return true;
	}
	return false;
}

/**
 * Assuming we're updating all positions at once.
 * return: 1 if update was succsessful
 * 		   0 if not (e.g. running out of canvas)
 */
int i = 0;
bool Waterdrop::updatePosition() {

	xpos = xpos - (xSpeed + Deceleration) * Direction();
	if (xpos + radius < 0.0f || (xpos - radius > WINDOW_WIDTH)) {
		reset();
		return 0;
	}

	ypos = ypos - (ySpeed + Deceleration);
	if (ypos + radius < 0.0f) {
		reset();
		return 0;
	}

	if(i == 10) {
		freeShape.clear();
		i = 0;
	}
	i++;
	for (GLfloat angle = 0; angle < 2 * PI; angle += 0.1f) {
		point2d x;
		x.xcoord = xpos + radius * cos(angle);
		x.ycoord = ypos + radius * sin(angle);
		freeShape.push_back(x);
	}
	return 1;
}

/**
 * @todo: rand --> random class
 */
int Waterdrop::Direction(void) {
	int temp = 0;
	const int min = 1;
	const int max = 1;
	switch (this->direction) {
	case -1: //links fließen
	{
		temp = min + (rand() % 100);
		break;
	}
	case 1: //rechts fliessen
	{
		temp = (rand() % (100 - max));
		break;
	}
	default: {
		temp = (rand() % 100);
		break;
	}
	}

	if (temp < min) {
		direction -= 1;
	} else if (temp > (100 - 1 - max)) {
		direction += 1;
	}
	return direction;
}

void Waterdrop::addJoinedDrop(Waterdrop* drop) {
	inactivatedDueToJoined.push_back(drop);
}

Waterdrop::~Waterdrop() {
}

