/*
 * GlassPanel.cpp
 *
 *  Created on: 07.12.2016
 *      Author: kiara
 */

#include "GlassPanel.h"
#include <algorithm>
#include <GL/glut.h>

GlassPanel::GlassPanel() {
	// TODO Auto-generated constructor stub
	for (int width = 0; width < WINDOW_WIDTH; width++) {
		for (int height = 0; height < WINDOW_HEIGHT; height++) {
			this->glassPane[width][height].height = 0;
			this->glassPane[width][height].mass = 0;
		}
	}

	// Einen Kratzer in die Scheibe
	for (int x = 1; x < 300; x++) {
		this->setVale(x, 300);
	}
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
	for (int x = 311; x < WINDOW_WIDTH; x++) {
		this->setVale(x, 304);
	}



	// Ein Schmutzpartikel auf der Scheibe
	this->setHill(10, 10);
	this->setHill(400, 10);
	this->setHill(400, 400);
	this->setHill(50, 70);
}

GlassPanel::~GlassPanel() {
	// TODO Auto-generated destructor stub
}

void GlassPanel::setHeight(int x, int y, bool isVale, GLfloat height) {
	if (this->isInMatrix(x, y) && (height > 0)) {
		GLfloat h = (1 / 8) * height * this->maxMass;
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

void GlassPanel::setVale(int x, int y) {
	this->glassPane[x][y].height = -1.0 * this->maxMass;
	this->setHeight(x-1, y-1, true, 7);
	this->setHeight(x  , y-1, true, 7);
	this->setHeight(x+1, y-1, true, 7);

	this->setHeight(x-1, y, true, 7);
	this->setHeight(x+1, y, true, 7);


	this->setHeight(x-1, y+1, true, 7);
	this->setHeight(x  , y+1, true, 7);
	this->setHeight(x+1, y+1, true, 7);
}

void GlassPanel::setHill(int x, int y) {
	this->glassPane[x][y].height = 1.0 * this->maxMass;
	this->setHeight(x-1, y-1, false, 7);
	this->setHeight(x  , y-1, false, 7);
	this->setHeight(x+1, y-1, false, 7);

	this->setHeight(x-1, y, false, 7);
	this->setHeight(x+1, y, false, 7);


	this->setHeight(x-1, y+1, false, 7);
	this->setHeight(x  , y+1, false, 7);
	this->setHeight(x+1, y+1, false, 7);
}

GLfloat GlassPanel::getHeightAtPoint(int x, int y) {
	return this->glassPane[x][y].height;
}

GLfloat GlassPanel::getMassAtPoint(int x, int y) {
	return this->glassPane[x][y].mass;
}

void GlassPanel::addMassAtPoint(int x, int y, GLfloat mass) {
	if (this->isInMatrix(x, y)) {
		this->glassPane[x][y].mass += mass;
		if (this->glassPane[x][y].mass < 0) {
			this->glassPane[x][y].mass = 0;
		}
	}
}

bool GlassPanel::isInMatrix(int x, int y) {
	return ((x >= 0) && (x < WINDOW_WIDTH) && (y >= 0) && (y < WINDOW_HEIGHT));
}

GLfloat GlassPanel::calcSpeed(GLfloat mass, int x, int y) {
	if (isInMatrix(x, y)) {
		return (((mass * this->gravitation) - this->glassPane[x][y].height) / mass);
	} else {
		return 1.f;
	}
}
