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
#include "MassPoint.h"
#include "BoundingBox.h"

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
	bool updatePosition(physic p);
	void reset();
	void addJoinedDrop(Waterdrop* drop);
	GLboolean detectCollision(Waterdrop *drop2);
	void joinDrops(Waterdrop* drop2);

	bool Intersect(Waterdrop *drop2);
	void AxisSeparatePolygons(std::vector<point2d> whatever, std::vector<point2d> A, std::vector<point2d> B);
	GLfloat getDropMass();

	GLfloat getBlue() const {
		return blue;
	}

	void setBlue(GLfloat blue) {
		this->blue = blue;
	}

	BoundingBox * b;

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

	int getCountMass(void) {
		return this->vecMassPoints.size();
	}

	MassPoint at(int idx) {
		return this->vecMassPoints.at(idx);
	}
};

#endif /* WATERDROP_H_ */
