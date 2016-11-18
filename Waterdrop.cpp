/*
 * Waterdrop.cpp
 *
 *  Created on: 31.10.2016
 *      Author: kiara
 */

#include "Waterdrop.h"
#include "Globals.h"
#include "Random.h"



Waterdrop::Waterdrop() {
	this->isActive = true;
	this->radius = Random::randGlfloat(7.0f, 5.0f);
	this->xpos = Random::randGlfloat(WINDOW_WIDTH - this->radius, this->radius);
	this->ypos = Random::randGlfloat(WINDOW_HEIGHT - this->radius, this->radius);
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

}

void Waterdrop::addJoinedDrop(Waterdrop* drop) {
	this->inactivatedDueToJoined.push_back(drop);
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

Waterdrop::~Waterdrop() {
}

