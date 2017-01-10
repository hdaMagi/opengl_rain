/*
 * MassPoint.cpp
 *
 *  Created on: 06.12.2016
 *      Author: jannis
 */

#include "../include/MassPoint.h"
#include <math.h>

#include "../include/Waterdrop.h"
#include "../include/Globals.h"
#include "../include/Random.h"
#include "../include/Waterdrops.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void MassPoint::reset() {
	this->isActive = true;
	this->setMass(Random::randGlfloat(3.3f, 1.0f));
	this->xpos = Random::randGlfloat(WINDOW_WIDTH - this->radius, this->radius);
	this->ypos = WINDOW_HEIGHT;
	this->speed = 0.f;
	this->red = Random::randGlfloat(1.0f, 0.0f);
	this->green = Random::randGlfloat(1.0f, 0.0f);
	this->blue = 1.0f;
	this->direction = 4.7f;
}

MassPoint::MassPoint() {
	this->reset();
	this->ypos = Random::randGlfloat(WINDOW_HEIGHT - this->radius,
			this->radius);
}

/**
 * Assuming we're updating all positions at once.
 * return: 1 if update was succsessful
 * 		   0 if not (e.g. running out of canvas)
 */
bool MassPoint::updatePosition(physic p) {

	//xpos = xpos - (xSpeed + Deceleration);
	xpos += (p.speed * cos(p.radiant));
	if (xpos + radius < 0.0f || (xpos - radius > WINDOW_WIDTH)) {
		reset();
		return 0;
	}

	//ypos = ypos - (ySpeed + Deceleration);
	ypos -= p.speed;
	if (ypos + radius < 0.0f) {
		reset();
		return 0;
	}

	return 1;
}

/**
 * @todo: rand --> random class
 */
int MassPoint::Direction(void) {
	/*int temp = 0;
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
	}*/
	if (direction < 4.7) {
		return -1;
	} else if (direction > 4.7) {
		return 1;
	}
	return 0;
}

GLfloat MassPoint::addToMass(int mass) {
	this->mass += mass;
	calcRadiusFromMass();
	return this->mass;
}

void MassPoint::setMass(GLfloat mass) {
	this->mass = mass;
	calcRadiusFromMass();
}

void MassPoint::calcRadiusFromMass() {
	this->radius = this->mass;
	this->radius *= 1.5; // two third
	this->radius /= PI;
	this->radius = powf(this->radius, (1.f/3.f));

	this->radius *= 6; // Damit es auf dem Bildschirm besser sichtbar ist
}

MassPoint::~MassPoint() {
	// TODO Auto-generated destructor stub
}
