/*
 * Waterdrop.h
 *
 *  Created on: 31.10.2016
 *      Author: kiara
 */

#ifndef WATERDROP_H_
#define WATERDROP_H_

#include <GL/glut.h>	// OpenGL und GLUT
#include <vector>
class Waterdrop {
private:
	int direction;
public:
	Waterdrop();
	virtual ~Waterdrop();
	bool isActive;
	GLfloat xpos, ypos;			// Positions
	GLfloat xmov, ymov;			// Moves
	GLfloat radius;				// Radius in Pixel
	GLfloat red, green, blue;	// Color
	GLfloat Acceleration;		// How fast it accelerates
	GLfloat Deceleration;		// How fast it decelerates downwards
	GLfloat Scalez;				// How much we wish to scale it
	std::vector<Waterdrop*>  inactivatedDueToJoined;
	int Direction();			// The angle of rotation
	void reset();
	void addJoinedDrop(Waterdrop* drop);

	GLfloat getAcceleration() const {
		return Acceleration;
	}

	void setAcceleration(GLfloat acceleration) {
		Acceleration = acceleration;
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

	GLfloat getXmov() const {
		return xmov;
	}

	void setXmov(GLfloat xmov) {
		this->xmov = xmov;
	}

	GLfloat getXpos() const {
		return xpos;
	}

	void setXpos(GLfloat xpos) {
		this->xpos = xpos;
	}

	GLfloat getYmov() const {
		return ymov;
	}

	void setYmov(GLfloat ymov) {
		this->ymov = ymov;
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
};

#endif /* WATERDROP_H_ */
