/*
 * Random.cpp
 *
 *  Created on: 18.11.2016
 *      Author: jannis
 */
#include <GL/glut.h>

#include "../include/Random.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


GLfloat Random::randGlfloat(GLfloat max, GLfloat min = 0.0f) {
    return ( min + static_cast <GLfloat> (rand()) /( static_cast <GLfloat> (RAND_MAX/(max-min))));
}

int Random::getRandom(int min, int max){
	  int iSecret, iGuess;

	  /* initialize random seed: */
	  srand (time(NULL));

	  /* generate secret number between 1 and 10: */
	  iSecret = rand() % max + min;

	  return iSecret;
}
