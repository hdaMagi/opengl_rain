/*
 * Waterdrop.h
 *
 *  Created on: 31.10.2016
 *      Author: kiara
 */

#ifndef WATERDROP_H_

#define WATERDROP_H_

#include <GL/glut.h>
#include <vector>
#include <queue>
#include "Globals.h"
#include "GlassPanel.h"
#include "MassPoint.h"

class Waterdrop {
private:
	bool isActive;
	GLfloat red, green, blue;	// Color
	std::vector<Waterdrop*>  inactivatedDueToJoined;
	std::vector<point2d> freeShape;
	std::vector<MassPoint> vecMassPoints;

public:
	Waterdrop();
	virtual ~Waterdrop();

	int Direction();			// The angle of rotation
	bool updatePosition(GlassPanel* gp);
	void reset();
	void addJoinedDrop(Waterdrop* drop);
	bool detectCollision(Waterdrop *drop2);
	void joinDrops(Waterdrop* drop2);

	GLfloat getMass();

	GLfloat getBlue() const {
		return blue;
	}

	void setBlue(GLfloat blue) {
		this->blue = blue;
	}

	GLfloat getGreen() const {
		return green;
	}

	void setGreen(GLfloat green) {
		this->green = green;
	}

	GLfloat getRed() const {
		return red;
	}

	void setRed(GLfloat red) {
		this->red = red;
	}

	bool isIsActive() const {
		return isActive;
	}

	void setIsActive(bool isActive) {
		this->isActive = isActive;
	}

	const std::vector<point2d>& getFreeShape() const {
		return freeShape;
	}

	void setFreeShape(const std::vector<point2d>& freeShape) {
		this->freeShape = freeShape;
	}

	void clearFreeShape() {
		this->freeShape.clear();
	}

	void setColor(GLfloat red, GLfloat green, GLfloat blue) {
		this->red = red;
		this->green = green;
		this->blue = blue;
	}
};

#endif /* WATERDROP_H_ */
