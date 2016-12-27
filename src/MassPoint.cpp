/*
 * MassPoint.cpp
 *
 *  Created on: 06.12.2016
 *      Author: jannis
 */

#include "MassPoint.h"
#include <math.h>

#include "Waterdrop.h"
#include "Globals.h"
#include "Random.h"
#include "Waterdrops.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

MassPoint::MassPoint() {
	this->isActive = true;
	this->radius = Random::randGlfloat(15.0f, 5.0f);
	this->xpos = Random::randGlfloat(WINDOW_WIDTH - this->radius, this->radius);
	this->ypos = Random::randGlfloat(WINDOW_HEIGHT - this->radius,
			this->radius);
	this->xSpeed = Random::randGlfloat(0.1, -0.1);
	this->ySpeed = 0.1f;
	this->red = Random::randGlfloat(1.0f, 0.0f);
	this->green = Random::randGlfloat(1.0f, 0.0f);
	this->blue = 1.0f;
	this->Deceleration = Random::randGlfloat(0.05f, 0.05f);
	this->direction = 0; // gerade runter fließen
}

void MassPoint::reset() {
	this->isActive = true;
	this->radius = Random::randGlfloat(7.0f, 5.0f);
	this->xpos = Random::randGlfloat(WINDOW_WIDTH - this->radius, this->radius);
	this->ypos = WINDOW_HEIGHT;
	this->xSpeed = Random::randGlfloat(0.1, -0.1);
	this->ySpeed = 0.1f;
	this->red = Random::randGlfloat(1.0f, 0.0f);
	this->green = Random::randGlfloat(1.0f, 0.0f);
	this->blue = 1.0f;
	this->Deceleration = Random::randGlfloat(0.05f, 0.05f);
	this->direction = 0;
//	for (std::vector<Waterdrop*>::iterator it =
//			this->inactivatedDueToJoined.begin();
//			it != this->inactivatedDueToJoined.end(); ++it) {
//		Waterdrop & drop = **it;
//		drop.reset();
//	}
//	this->inactivatedDueToJoined.clear();
//	freeShape.clear();
}

/**
 * Assuming we're updating all positions at once.
 * return: 1 if update was succsessful
 * 		   0 if not (e.g. running out of canvas)
 */
bool MassPoint::updatePosition() {

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

//	freeShape.clear();
//
//	point2d x;
//	int iter = 0;
//	for (GLfloat i = 0; i < PI; i = i + 0.1) {
//		if (iter % 2 == 0) {
//			x.xcoord = xpos + sin(i) * 10;
//		} else {
//			x.xcoord = xpos - sin(i) * 10;
//		}
//		if(i < PI / 2){
//		x.ycoord = ypos - i * (1 - iter);
//		}else{
//			x.ycoord = ypos + i * iter;
//		}
//		freeShape.push_back(x);
//		iter++;
//	}
	return 1;
}

/**
 * @todo: rand --> random class
 */
int MassPoint::Direction(void) {
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

MassPoint::~MassPoint() {
	// TODO Auto-generated destructor stub
}
