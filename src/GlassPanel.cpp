/*
 * GlassPanel.cpp
 *
 *  Created on: 27.12.2016
 *      Author: kiara
 */

#include "../include/GlassPanel.h"
#include <cmath>
#include "../maps/map01.h"
#include "../maps/map02.h"
#include "../maps/map03.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */

GlassPanel::GlassPanel() {
	// TODO Auto-generated constructor stub
	for (int x = 0; x < WINDOW_WIDTH; x++) {
		for (int y = 0; y < WINDOW_HEIGHT; y++) {
			Panel[x][y] = 0.f;
		}
	}
}

bool GlassPanel::isBetween(int from, int to, char value) {
	//int char_int = static_cast<int>(value);
	char cfrom = static_cast<char>(from);
	char cto = static_cast<char>(to);
	return ((cfrom <= value) && (cto <= to));
}

void GlassPanel::initPanel(unsigned char* mp, int len) {
	int countPixs = (WINDOW_WIDTH  * WINDOW_HEIGHT);
	double pixel =  len / (double)countPixs;
	int nenner = (int)pixel;
	pixel = pixel - nenner;

	double nextpixel = 0;
	int idx = 0;
	int x = 0, y = WINDOW_HEIGHT-1;
	GLfloat h = 0.f;
	countPixs = 0;
	while (idx < len) {
		countPixs++;
		if (isBetween(0,27,mp[idx])) {
			h += -1.f;
		} else if (isBetween(28,55,mp[idx])) {
			h += -0.8f;
		} else if (isBetween(56,83,mp[idx])) {
			h += -0.6f;
		} else if (isBetween(84,111,mp[idx])) {
			h += -0.2f;
		} else if (isBetween(144,171,mp[idx])) {
			h += 0.2f;
		} else if (isBetween(172,199,mp[idx])) {
			h += 0.6f;
		} else if (isBetween(200,227,mp[idx])) {
			h += 0.8f;
		} else if (isBetween(288,255,mp[idx])) {
			h += 1.0f;
		}
		int pixs = nenner + (int)nextpixel;
		if (nextpixel >= 1) {
			nextpixel = 0.f;
		}
		if (pixs >= 1) {
			h = h / countPixs;
			for (int pix = 0; pix < pixs; pix++) {
				this->Panel[x][y] = h;
				x++;
				if (x >= WINDOW_WIDTH) {
					y--;
					if (y < 0) {
						return;
					}
					x = 0;
				}
				nextpixel += pixel;
			}
			h = 0.f;
			countPixs = 0;
		} else {
			nextpixel = 0;
		}
		idx++;
	}
}

GlassPanel::GlassPanel(int mapIdx) { // 1 => map01; 2 => map02; 3 => map03
	switch (mapIdx) {
		case 1: {
			initPanel(MagickImage01, (sizeof(MagickImage01)/sizeof(*MagickImage01)));
			break;
		}
		case 2: {
			initPanel(MagickImage02, (sizeof(MagickImage02)/sizeof(*MagickImage02)));
			break;
		}
		case 3: {
			initPanel(MagickImage03, (sizeof(MagickImage03)/sizeof(*MagickImage03)));
			break;
		}
	}
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
	GLfloat rad = 0.f;
	result.radiant = mp.getDirection();
	GLfloat oldRad = result.radiant;
	while (((rad + oldRad) < 6.0f) && ((oldRad - rad) > 3.2f)) {
		// left
		int x = (int)ceil((mp.getXpos() + mp.getRadius()) * cos(oldRad - rad) * 2);
		int y = (int)ceil((mp.getYpos() + mp.getRadius()) * sin(oldRad - rad));
		if (this->isInPanel(x,y)) {
			if (this->Panel[x][y] < oldheight) {
				oldheight = this->Panel[x][y];
				result.radiant = rad;
			}
		}

		// right
		x = (int)ceil((mp.getXpos() + mp.getRadius()) * -cos(rad + oldRad) * 2);
		y = (int)ceil((mp.getYpos() + mp.getRadius()) * sin(rad + oldRad));
		if (this->isInPanel(x,y)) {
			if (this->Panel[x][y] < oldheight) {
				oldheight = this->Panel[x][y];
				result.radiant = rad;
			}
		}
		rad = rad + 0.2f;
	}

	return result;
}
