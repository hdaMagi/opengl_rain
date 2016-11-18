/*
 * Random.h
 *
 *  Created on: 18.11.2016
 *      Author: jannis
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <GL/glut.h>

class Random {
public:
	Random();
	virtual ~Random();
	static GLfloat randGlfloat(GLfloat max, GLfloat min);

};

#endif /* RANDOM_H_ */
