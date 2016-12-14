/*
 * GlassPanel.h
 *
 *  Created on: 07.12.2016
 *      Author: kiara
 */

#ifndef GlassPanel_H_
#define GlassPanel_H_

#include <GL/glut.h>
#include "Globals.h"
#include <vector>

struct PaneInfo {
	GLfloat height; // Between -1.0 to 1.0;
	GLfloat mass;
};

class GlassPanel {
private:
	PaneInfo glassPane [WINDOW_WIDTH][WINDOW_HEIGHT];
	void setHeight(int x, int y, bool min, GLfloat height);
	void setVale(int x, int y);
	void setHill(int x, int y);
	bool isInMatrix(int x, int y);
public:
	const static GLfloat gravitation = 9.81; 	//Erdbeschleunigung [für Deutschland: g ≈ 9,81 m/s²]
	const static GLfloat maxMass = 2.f; 		//Maximale Masse bevor ein Tropfen beginnt zu fließen //Im Netz 4.2
	GlassPanel();
	virtual ~GlassPanel();
	GLfloat getHeightAtPoint(int x, int y);
	GLfloat getMassAtPoint(int x, int y);
	void addMassAtPoint(int x, int y, GLfloat mass);
	GLfloat calcSpeed(GLfloat mass, int x, int y);
};

#endif /* GlassPanel_H_ */
