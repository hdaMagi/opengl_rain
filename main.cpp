#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <sys/time.h>

#include "Globals.h"
#include "Waterdrop.h"

std::vector<Waterdrop> waterdrops;

float clamp(float value, float min, float max) {
	return std::max(min, std::min(max, value));
}

bool detectCollision(Waterdrop* drop1, Waterdrop *drop2) {
	float dst = sqrt(
			pow((drop2->getXpos() - drop1->getXpos()), 2)
					+ pow((drop2->getYpos() - drop1->getYpos()), 2));
	float dst2 = dst - drop1->getRadius() - drop2->getRadius();

//	printf(
//			"D1X: %02f, \t D1Y: %02f, \t D2X: %02f, \t D2Y: %02f\n",
//			drop1->xpos, drop1->ypos, drop2->xpos, drop2->ypos);
	if (dst2 < 0) {
//		printf("collided\n");
		return true;
	}
	return false;
}

void joinDrops(Waterdrop* drop1, Waterdrop* drop2) {
//	printf("JOINING");

	drop1->setRadius(sqrt(((pow(drop1->getRadius(), 2) * PI) + (pow(drop2->getRadius(), 2) * PI)) / PI));
	drop1->addJoinedDrop(drop2);
	drop2->setIsActive(false);
	drop2->setXpos(-200); // hiding "looser" joined drops

}

void drawCircle(GLfloat xcoord, GLfloat ycoord, GLfloat radius)
		{
	GLfloat angle = 0;
	glBegin(GL_POLYGON);
	for (angle = 0; angle < 2 * PI; angle += 0.1f) {
		glVertex2i(xcoord + radius * cos(angle), ycoord + radius * sin(angle));
	}
	glEnd();
}


/*
 * Actual idea: instead of drawing perfect circles we draw ellipsoids
 * with speed parameter as added to y parameter.
 * sin / cos ?
 */
void drawDrop(GLfloat xcoord, GLfloat ycoord, GLfloat radius, GLfloat xSpeed, GLfloat ySpeed)
		{
	GLfloat angle = 0;
	glBegin(GL_POLYGON);
	for (angle = 0; angle < 2 * PI; angle += 0.1f) {
		glVertex2i(xcoord + radius * cos(angle) * xSpeed * 20, ycoord + radius * sin(angle) * ySpeed * 20);
	}
	glEnd();
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPointSize(4.0);					// Punktgröße in Pixel
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();					// lade Einheitsmatrix
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);// Koordinatenursprung in die Mitte

}

void idle(void) {
	for (std::vector<Waterdrop>::iterator it = waterdrops.begin();
			it != waterdrops.end(); ++it) {
		Waterdrop & drop = *it;
		if (drop.isIsActive() == true) {
			GLfloat newXpos = drop.getXpos() - ((drop.getXSpeed() + drop.getDeceleration()) * drop.Direction());

			drop.setXpos(newXpos);

			if ((drop.getXpos() + (drop.getRadius()) < 0.0f) || (drop.getXpos() - (drop.getRadius()) > WINDOW_WIDTH)) {
				drop.reset();
			}

			drop.setYpos(drop.getYpos() - (drop.getYSpeed() + drop.getDeceleration()));
			if (drop.getYpos() + (drop.getRadius())  < 0.0f) {
				drop.reset();
			}

			for (std::vector<Waterdrop>::iterator it2 = waterdrops.begin();
					it2 != waterdrops.end(); ++it2) {
				if (it != it2) {
//				printf("%i <--> %i - ", it,  it2);
					Waterdrop & drop1 = *it;
					Waterdrop & drop2 = *it2;
					if (drop1.isIsActive()== true && drop2.isIsActive() == true) {
						bool x = detectCollision(&drop1, &drop2);
						if (x == true) {
							joinDrops(&drop1, &drop2);
						}
					}
				}
			}
		}
	}

	glutPostRedisplay();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	int size = waterdrops.size();
	for (int idx = 0; idx < size; idx++) {
		Waterdrop drop = waterdrops[idx];
		glColor3f(drop.getRed(), drop.getGreen(), drop.getBlue());
		drawDrop(drop.getXpos(), drop.getYpos(), drop.getRadius(), drop.getXSpeed(), drop.getYSpeed());
	}

	glutSwapBuffers();
	glFlush();
}

int main(int argc, char** argv) {
	timeval t1;
	gettimeofday(&t1, NULL);
	srand(t1.tv_usec * t1.tv_sec);
	// GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Raining");
	for (int idx = 0; idx < 75; idx++) {
		Waterdrop drop;
		waterdrops.push_back(drop);
	}
	glutDisplayFunc(display);

	init();

	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}
