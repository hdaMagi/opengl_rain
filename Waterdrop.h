/*
 * Waterdrop.h
 *
 *  Created on: 31.10.2016
 *      Author: kiara
 */

#ifndef WATERDROP_H_
#define WATERDROP_H_

#include <GL/glut.h>	// OpenGL und GLUT

class Waterdrop {
public:
	Waterdrop();
	virtual ~Waterdrop();
	GLfloat xpos, ypos;			// Positions
	GLfloat xmov, ymov;			// Moves
	GLfloat radius;				// Radius in Pixel
	GLfloat red, green, blue;	// Color
	GLfloat Direction;			// The angle of rotation
	GLfloat Acceleration;		// How fast it accelerates
	GLfloat Deceleration;		// How fast it decelerates downwards
	GLfloat Scalez;				// How much we wish to scale it
};

#endif /* WATERDROP_H_ */
