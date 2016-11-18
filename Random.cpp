/*
 * Random.cpp
 *
 *  Created on: 18.11.2016
 *      Author: jannis
 */
#include <GL/glut.h>

#include "Random.h"


GLfloat Random::randGlfloat(GLfloat max, GLfloat min = 0.0f) {
    return ( min + static_cast <GLfloat> (rand()) /( static_cast <GLfloat> (RAND_MAX/(max-min))));
}

