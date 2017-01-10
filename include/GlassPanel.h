/*
 * glasspanel.h
 *
 *  Created on: 27.12.2016
 *      Author: kiara
 */

#ifndef GLASSPANEL_H_
#define GLASSPANEL_H_

#include <GL/glut.h>
#include <string>
#include "Globals.h"
#include "Waterdrop.h"
#include "Globals.h"

#define GRAVITIY 6.67408

class GlassPanel {
private:
	GLfloat Panel[WINDOW_WIDTH][WINDOW_HEIGHT];
	bool isInPanel(int x, int y);
public:
	GlassPanel(); // perfekte Scheibe
	GlassPanel(std::string path); // lade eine Hoehenmappe
	GlassPanel(int mapIdx); // 1 => map01; 2 => map02; 3 => map03
	virtual ~GlassPanel();
	GLfloat getFriction(int x, int y);

	physic moveWaterdrop(Waterdrop drop);
};

#endif /* GLASSPANEL_H_ */
