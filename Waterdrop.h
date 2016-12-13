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
#include "Globals.h"
class Waterdrop {
private:
	int direction;
	bool isActive;
	GLfloat xpos, ypos;			// Positions
	GLfloat xSpeed, ySpeed;		// Moves
	GLfloat radius;				// Radius in Pixel
	GLfloat red, green, blue;	// Color
	GLfloat Acceleration;		// How fast it accelerates
	GLfloat Deceleration;		// How fast it decelerates downwards
	GLfloat Scalez;				// How much we wish to scale it
	GLfloat mass;				//
	std::vector<Waterdrop*>  inactivatedDueToJoined;


	std::vector<point2d> freeShape; // = new std::vector();

public:
	Waterdrop();
	virtual ~Waterdrop();

	int Direction();			// The angle of rotation
	bool updatePosition();
	void reset();
	void addJoinedDrop(Waterdrop* drop);
	bool detectCollision(Waterdrop *drop2);
	void joinDrops(Waterdrop* drop2);

	GLfloat getAcceleration() const {
		return Acceleration;
	}

	void setAcceleration(GLfloat acceleration) {
		Acceleration = acceleration;
	}

	GLfloat getMass() const {
		return mass;
	}

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

	GLfloat getScalez() const {
		return Scalez;
	}

	void setScalez(GLfloat scalez) {
		Scalez = scalez;
	}

	GLfloat getXSpeed() const {
		return xSpeed;
	}

	void setXSpeed(GLfloat xmov) {
		this->xSpeed = xSpeed;
	}

	GLfloat getXpos() const {
		return xpos;
	}

	void setXpos(GLfloat xpos) {
		this->xpos = xpos;
	}

	GLfloat getYSpeed() const {
		return ySpeed;
	}

	void setYSpeed(GLfloat ymov) {
		this->ySpeed = ySpeed;
	}

	GLfloat getYpos() const {
		return ypos;
	}

	void setYpos(GLfloat ypos) {
		this->ypos = ypos;
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
