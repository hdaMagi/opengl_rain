/*
 * Globals.cpp
 *
 *  Created on: 31.10.2016
 *      Author: kiara
 */

#include "Globals.h"
#include <ctime>
#include <cstdlib>

GLfloat randGlfloat(GLfloat max, GLfloat min = 0.0f) {
    return ( min + static_cast <GLfloat> (rand()) /( static_cast <GLfloat> (RAND_MAX/(max-min))));
}
