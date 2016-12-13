/*
 * Physics.h
 *
 *  Created on: 07.12.2016
 *      Author: kiara
 */

#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <GL/glut.h>
#include "Waterdrop.h"
#include "Globals.h"
#include <vector>

struct PaneInfo {
	GLfloat height; // Between -1.0 to 1.0;
	GLfloat mass;
};

class Physics {
private:
	PaneInfo glassPane [WINDOW_WIDTH][WINDOW_HEIGHT];
	void setHeight(int x, int y, bool min, GLfloat height);
	void setVale(int x, int y);
	void setHill(int x, int y);
	bool isInMatrix(int x, int y);
public:
	const GLfloat gravitation = 9.81; 	//Erdbeschleunigung [für Deutschland: g ≈ 9,81 m/s²]
	const GLfloat maxMass = 0.42; 		//Maximale Masse bevor ein Tropfen beginnt zu fließen
	const GLfloat frictional = maxMass * gravitation; //Reibungskraft
	Physics();
	virtual ~Physics();
	GLfloat getHeightAtPoint(int x, int y);
	GLfloat getMassAtPoint(int x, int y);
	void addMassAtPoint(int x, int y, GLfloat mass);
};

#endif /* PHYSICS_H_ */
