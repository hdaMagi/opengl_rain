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

GLfloat getRadiusFromMass(GLfloat mass) {
	GLfloat tmp = 0;
	tmp = 2.f / 3.f;
	tmp = (PI * tmp);
	tmp = (mass / tmp);
	tmp = powf(tmp, (1.f/3.f));
	return tmp * 3;
}

Waterdrop::Waterdrop() {
	this->isActive = true;
	this->mass = Random::randGlfloat(4.2, 0.1);
	this->radius = getRadiusFromMass(this->mass);
	this->xpos = Random::randGlfloat(WINDOW_WIDTH - this->radius, this->radius);
	this->ypos = Random::randGlfloat(WINDOW_HEIGHT - this->radius, this->radius);
	this->xSpeed = Random::randGlfloat(1.0f, 0.0f);
	this->ySpeed = Random::randGlfloat(1.0f, this->xSpeed);
	this->red = Random::randGlfloat(1.0f, 0.0f);
	this->green = Random::randGlfloat(1.0f, 0.0f);
	this->blue = 1.0f;
	this->Acceleration = 0.0f;
	this->Deceleration = 0.0f;
	this->Scalez = 0.0f;
	this->direction = 0; // gerade runter fliessen
}

void Waterdrop::reset() {
	this->isActive = true;
	this->mass = Random::randGlfloat(4.2, 0.1);
	this->radius = getRadiusFromMass(this->mass);
	this->xpos = Random::randGlfloat(WINDOW_WIDTH - this->radius, this->radius);
	this->ypos = WINDOW_HEIGHT - this->radius;
	this->xSpeed = Random::randGlfloat(1.0f, 0.0f);
	this->ySpeed = Random::randGlfloat(1.0f, this->xSpeed);
	this->red = Random::randGlfloat(1.0f, 0.0f);
	this->green = Random::randGlfloat(1.0f, 0.0f);
	this->blue = 1.0f;
	this->Acceleration = 0.0f;
	this->Deceleration = 0.0f;
	this->Scalez = 0.0f;
	this->direction = 0;
	freeShape.clear();
}

/**
 * for free shape joining will be much more complicated so we're leaving the method here
 * drop2 is the looser
 */
void Waterdrop::joinDrops(Waterdrop* drop2) {
	this->mass += drop2->getMass();
	this->radius = getRadiusFromMass(this->mass);
	drop2->reset();

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
		return false;
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
	return true;
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

