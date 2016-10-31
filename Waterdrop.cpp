/*
 * Waterdrop.cpp
 *
 *  Created on: 31.10.2016
 *      Author: kiara
 */

#include "Waterdrop.h"
#include "Globals.h"

Waterdrop::Waterdrop() {
	this->radius = randGlfloat(7.0f, 5.0f);
	this->xpos = randGlfloat(WINDOW_WIDTH-this->radius, this->radius);
	this->ypos = randGlfloat(WINDOW_HEIGHT-this->radius, this->radius);
	this->xmov = 0.0f;
	this->ymov = 0.1f;
	this->red = randGlfloat(1.0f, 0.0f);
	this->green = randGlfloat(1.0f, 0.0f);
	this->blue = 1.0f;
	this->Direction = 0.0f;
	this->Acceleration = 0.0f;
	this->Deceleration = 0.0f;
	this->Scalez = 0.0f;
}

Waterdrop::~Waterdrop() {}

