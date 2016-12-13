/*
 * Physics.cpp
 *
 *  Created on: 07.12.2016
 *      Author: kiara
 */

#include "Physics.h"
#include <algorithm>
#include <GL/glut.h>

Physics::Physics() {
	// TODO Auto-generated constructor stub
	for (int width = 0; width < WINDOW_WIDTH; width++) {
		for (int height = 0; height < WINDOW_HEIGHT; height++) {
			this->glassPane[width][height].height = 0;
			this->glassPane[width][height].mass = 0;
		}
	}

	// Einen Kratzer in die Scheibe
	this->setVale(300, 300);
	this->setVale(301, 301);
	this->setVale(302, 301);
	this->setVale(303, 301);
	this->setVale(304, 302);
	this->setVale(305, 302);
	this->setVale(306, 302);
	this->setVale(307, 302);
	this->setVale(308, 302);
	this->setVale(309, 303);
	this->setVale(310, 303);



	// Ein Schmutzpartikel auf der Scheibe
	this->setHill(10, 10);
	this->setHill(400, 10);
	this->setHill(400, 400);
	this->setHill(50, 70);
}

Physics::~Physics() {
	// TODO Auto-generated destructor stub
}

void Physics::setHeight(int x, int y, bool isVale, GLfloat height) {
	if (this->isInMatrix(x, y) && (height > 0)) {
		GLfloat h = (1 / 8) * height;
		if (isVale) {
			h *= -1;
			if (h < this->glassPane[x][y].height) {
				this->glassPane[x][y].height = h;

			}
		} else if (h > this->glassPane[x][y].height) {
			this->glassPane[x][y].height = h;
		}
		this->setHeight(x-1, y-1, isVale, height-1);
		this->setHeight(x  , y-1, isVale, height-1);
		this->setHeight(x+1, y-1, isVale, height-1);

		this->setHeight(x-1, y, isVale, height-1);
		this->setHeight(x+1, y, isVale, height-1);


		this->setHeight(x-1, y+1, isVale, height-1);
		this->setHeight(x  , y+1, isVale, height-1);
		this->setHeight(x+1, y+1, isVale, height-1);
	}
}

void Physics::setVale(int x, int y) {
	this->glassPane[x][y].height = -1.0;
	this->setHeight(x-1, y-1, true, 7);
	this->setHeight(x  , y-1, true, 7);
	this->setHeight(x+1, y-1, true, 7);

	this->setHeight(x-1, y, true, 7);
	this->setHeight(x+1, y, true, 7);


	this->setHeight(x-1, y+1, true, 7);
	this->setHeight(x  , y+1, true, 7);
	this->setHeight(x+1, y+1, true, 7);
}

void Physics::setHill(int x, int y) {
	this->glassPane[x][y].height = 1.0;
	this->setHeight(x-1, y-1, false, 7);
	this->setHeight(x  , y-1, false, 7);
	this->setHeight(x+1, y-1, false, 7);

	this->setHeight(x-1, y, false, 7);
	this->setHeight(x+1, y, false, 7);


	this->setHeight(x-1, y+1, false, 7);
	this->setHeight(x  , y+1, false, 7);
	this->setHeight(x+1, y+1, false, 7);
}

GLfloat Physics::getHeightAtPoint(int x, int y) {
	return this->glassPane[x][y].height;
}

GLfloat Physics::getMassAtPoint(int x, int y) {
	return this->glassPane[x][y].mass;
}

void Physics::addMassAtPoint(int x, int y, GLfloat mass) {
	if (this->isInMatrix(x, y)) {
		this->glassPane[x][y].mass += mass;
		if (this->glassPane[x][y].mass < 0) {
			this->glassPane[x][y].mass = 0;
		}
	}
}

bool Physics::isInMatrix(int x, int y) {
	return ((x >= 0) && (x < WINDOW_WIDTH) && (y >= 0) && (y < WINDOW_HEIGHT));
}
