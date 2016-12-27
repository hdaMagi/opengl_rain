#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <sys/time.h>
#include <math.h>
#include "Globals.h"
#include "Waterdrop.h"
#include "Waterdrops.h"
#include "main.h"
#include <algorithm>  // min / max
//#include <cmath> // <ctgmath>

Waterdrops drops;

float clamp(float value, float min, float max) {
	return std::max(min, std::min(max, value));
}

void drawFreeShape(Waterdrop drop) {
	glPolygonMode( GL_FRONT, GL_LINE);
	glBegin(GL_TRIANGLE_FAN);
	std::vector<point2d> shape = drop.getFreeShape();
	for (unsigned int i = 0; i < shape.size(); i++) {
		point2d point = shape.at(i);
		glVertex2i(point.xcoord, point.ycoord);
		fflush(stdout);
	}

	glEnd();
}

void drawBoundingBox(Waterdrop drop) {

	point2d pAC = drop.b->pAC;
	point2d pAF = drop.b->pAF;

	glPolygonMode( GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(drop.b->p1.xcoord, drop.b->p1.ycoord, 0.0); // std::min(pAC.xcoord, pAF.xcoord), std::min(pAC.ycoord, pAF.ycoord), 0.0);
	glVertex3f(drop.b->p2.xcoord, drop.b->p1.ycoord, 0.0); // std::max(pAF.xcoord, pAC.xcoord), std::min(pAC.ycoord, pAF.ycoord), 0.0);
	glVertex3f(drop.b->p2.xcoord, drop.b->p2.ycoord, 0.0); // std::max(pAF.xcoord, pAC.xcoord), std::max(pAF.ycoord, pAC.ycoord), 0.0);
	glVertex3f(drop.b->p1.xcoord, drop.b->p2.ycoord, 0.0); // std::min(pAC.xcoord, pAF.xcoord), std::max(pAF.ycoord, pAC.ycoord), 0.0);

	glEnd();
}

void drawCircle(GLfloat xcoord, GLfloat ycoord, GLfloat radius) {
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
void drawDrop(GLfloat xcoord, GLfloat ycoord, GLfloat radius, GLfloat xSpeed,
		GLfloat ySpeed) {
	GLfloat angle = 0;
	glBegin(GL_POLYGON);
	for (angle = 0; angle < 2 * PI; angle += 0.1f) {
		glVertex2i(xcoord + radius * cos(angle) * xSpeed * 20,
				ycoord + radius * sin(angle) * ySpeed * 20);
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
	drops.update();
	glutPostRedisplay();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	/* ugly but working for the moment */
	std::vector<Waterdrop> waterdrops = drops.getWaterdrops();
	for (unsigned int idx = 0; idx < waterdrops.size(); idx++) {
		Waterdrop drop = waterdrops[idx];
		glColor3f(drop.getRed(), drop.getGreen(), drop.getBlue());
		drawFreeShape(drop);
		glColor3f(1.0, 0.0, 0.0);
		drawBoundingBox(drop);
		fflush(stdout);

	}
	glutSwapBuffers();
	glFlush();
}

int main(int argc, char** argv) {
	timeval t1;
	fflush(stdout);
	gettimeofday(&t1, NULL);
	srand(t1.tv_usec * t1.tv_sec);
	// GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Raining");
	Waterdrops drops();
	glutDisplayFunc(display);

	init();

	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}
