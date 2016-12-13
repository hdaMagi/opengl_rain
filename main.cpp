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

Waterdrops drops;

float clamp(float value, float min, float max) {
	return std::max(min, std::min(max, value));
}

void drawFreeShape(Waterdrop drop) {

	glBegin(GL_POLYGON);
	std::vector<point2d> shape = drop.getFreeShape();
	for (int i = 0; i < shape.size(); i++) {
		point2d point = shape.at(i);
		glVertex2i(point.xcoord, point.ycoord);
	}

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
	glClearColor(0.5, 0.5, 0.5, 0.5);
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
	int size = waterdrops.size();
	for (int idx = 0; idx < size; idx++) {
		Waterdrop drop = waterdrops[idx];
		glColor3f(drop.getRed(), drop.getGreen(), drop.getBlue());
		drawFreeShape(drop);
	}
	glutSwapBuffers();
	glFlush();
}

int main(int argc, char** argv) {
	//programPath = argv[0];
	timeval t1;
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
