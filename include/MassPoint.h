/*
 * MassPoint.h
 *
 *  Created on: 06.12.2016
 *      Author: jannis
 */

#ifndef MASSPOINT_H_
#define MASSPOINT_H_

#include <GL/glut.h>
#include <vector>
#include <queue>
#include "Globals.h"

class MassPoint {
public:
	MassPoint();
	void reset();
	int Direction(void);

	bool updatePosition(physic p);
	virtual ~MassPoint();

	GLfloat getBlue() const {
		return blue;
	}

	void setBlue(GLfloat blue) {
		this->blue = blue;
	}

	GLfloat getDirection() const {
		return direction;
	}

	void setDirection(GLfloat direction) {
		this->direction = direction;
	}


	GLfloat getGreen() const {
		return green;
	}

	void setGreen(GLfloat green) {
		this->green = green;
	}

	bool isIsActive() const {
		return isActive;
	}

	void setIsActive(bool isActive) {
		this->isActive = isActive;
	}

	GLfloat getRadius() const {
		return radius;
	}

	GLfloat getRed() const {
		return red;
	}

	void setRed(GLfloat red) {
		this->red = red;
	}

	const std::vector<MassPoint>& getVecMassPoints() const {
		return vecMassPoints;
	}

	void setVecMassPoints(const std::vector<MassPoint>& vecMassPoints) {
		this->vecMassPoints = vecMassPoints;
	}

	GLfloat getXpos() const {
		return xpos;
	}

	void setXpos(GLfloat xpos) {
		this->xpos = xpos;
	}

	GLfloat getYpos() const {
		return ypos;
	}

	void setYpos(GLfloat ypos) {
		this->ypos = ypos;
	}

	GLfloat getSpeed() const {
		return speed;
	}

	void setSpeed(GLfloat speed) {
		this->speed = speed;
	}

	GLfloat getMass() {
		return this->mass;
	}

	void setMass(GLfloat mass);
	GLfloat addToMass(int mass);

private:
	bool isActive;

	GLfloat direction;				// RAD: (3.5 - 4.6) => left; 4.7 => ahead; (4.8 - 5.9) => right
	GLfloat xpos, ypos;				// Positions
	GLfloat speed;				// Moves
	GLfloat radius;				// Radius in Pixel
	GLfloat mass;				// Masse/Volumen
	GLfloat red, green, blue;	// Color
	std::vector<MassPoint> vecMassPoints;
	void calcRadiusFromMass();
};

#endif /* MASSPOINT_H_ */
