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

	bool updatePosition();
	virtual ~MassPoint();

	GLfloat getBlue() const {
		return blue;
	}

	void setBlue(GLfloat blue) {
		this->blue = blue;
	}

	GLfloat getDeceleration() const {
		return Deceleration;
	}

	void setDeceleration(GLfloat deceleration) {
		Deceleration = deceleration;
	}

	int getDirection() const {
		return direction;
	}

	void setDirection(int direction) {
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

	void setRadius(GLfloat radius) {
		this->radius = radius;
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

	GLfloat getxSpeed() const {
		return xSpeed;
	}

	void setxSpeed(GLfloat speed) {
		xSpeed = speed;
	}

	GLfloat getYpos() const {
		return ypos;
	}

	void setYpos(GLfloat ypos) {
		this->ypos = ypos;
	}

	GLfloat getySpeed() const {
		return ySpeed;
	}

	void setySpeed(GLfloat speed) {
		ySpeed = speed;
	}

private:
	bool isActive;

	int direction;
	GLfloat xpos, ypos;			// Positions
	GLfloat xSpeed, ySpeed;			// Moves
	GLfloat radius;				// Radius in Pixel
	GLfloat red, green, blue;	// Color
	GLfloat Deceleration;		// How fast it decelerates downwards
	std::vector<MassPoint> vecMassPoints;
};

#endif /* MASSPOINT_H_ */
