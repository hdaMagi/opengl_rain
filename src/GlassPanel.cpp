/*
 * GlassPanel.cpp
 *
 *  Created on: 27.12.2016
 *      Author: kiara
 */

#include "../include/GlassPanel.h"
#include <cmath>

GlassPanel::GlassPanel() {
	// TODO Auto-generated constructor stub
	for (int x = 0; x < WINDOW_WIDTH; x++) {
		for (int y = 0; y < WINDOW_HEIGHT; y++) {
			Panel[x][y] = 0.f;
		}
	}
}

GlassPanel::GlassPanel(std::string path) { // lade eine Hoehenmappe
}

GlassPanel::GlassPanel(int mapIdx) { // 1 => map01; 2 => map02; 3 => map03
	std::string progPath = "";
}

GlassPanel::~GlassPanel() {
	// TODO Auto-generated destructor stub
}

bool GlassPanel::isInPanel(int x, int y) {
	return ((x >= 0) && (x < WINDOW_WIDTH) && (y >= 0) && (y < WINDOW_HEIGHT));
}

GLfloat GlassPanel::getFriction(int x, int y) {
	if (this->isInPanel(x,y)) {
		return (this->Panel[x][y] + 1) * GRAVITIY;
	}
	return 0;
}

physic GlassPanel::moveWaterdrop(Waterdrop drop) {
	physic result;
	result.speed = 0.f;
	result.radiant = 4.7f;

	MassPoint mp = drop.at(0);
	GLfloat oldheight = this->getFriction(mp.getXpos(), mp.getYpos());
	// Neue Geschwindigkeit berechnen
	GLfloat mass = drop.getDropMass();
	GLfloat a = ((GRAVITIY * mass) - oldheight) / mass;
	result.speed = mp.getSpeed() + a;
	if (result.speed < 0) {
		result.speed = 0;
	}

	// Fliessrichtung bestimmen
	GLfloat rad = 3.5f;
	result.radiant = mp.getDirection();
	while (rad < 6.f) {
		int x = (int)ceil((mp.getXpos() + mp.getRadius()) * cos(rad));
		int y = (int)ceil((mp.getYpos() + mp.getRadius()) * sin(rad));
		if (this->isInPanel(x,y)) {
			if (this->Panel[x][y] < oldheight) {
				oldheight = this->Panel[x][y];
				result.radiant = rad;
			}
		}
		rad = rad + 0.1f;
	}

	return result;
}
