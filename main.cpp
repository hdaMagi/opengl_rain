#include <GL/glut.h>	// OpenGL und GLUT
#include <iostream>	// für cout und cin
#include <math.h>		// für SIN, COS
#include <stdio.h>		//für sprintf
#include <vector>
#include <sys/time.h>
#include "Globals.h"
#include "Waterdrop.h"

#define pi 3.14159265358979323846

//************************************************************

//********VARIABLEN
GLfloat t=0; 				// Winkel
GLfloat r=7;				//Radius Kreis, 7 pixel
std::vector<Waterdrop>		waterdrops;



//*********************Kreis****************************
void drawCircle(GLfloat xcoord, GLfloat ycoord, GLfloat radius) // Koordinaten x,y, radius und gefüllt mit Farbe
{
	GLfloat angle=0; //Winkel
	// Kreis zeichnen
	glBegin(GL_POLYGON);  // gefüllt
	for (angle=0; angle<2*pi; angle+=0.1f) { //Winkel vergrößern
		glVertex2i(xcoord+radius*cos(angle), ycoord+radius*sin(angle)); //berechne alle Kreispunkte
	}
	glEnd();
}

//************************ myInit ************************
void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);   // set background color
  	glPointSize(4.0);					// Punktgröße in Pixel
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();					// lade Einheitsmatrix
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);	// Koordinatenursprung in die Mitte

}



//************************ myIdle ************************
void myIdle(void)
{
	for (std::vector<Waterdrop>::iterator it = waterdrops.begin(); it != waterdrops.end(); ++it)
	{
		Waterdrop & drop = *it;
		drop.xpos -= drop.xmov;
		if (drop.xpos < 0.0f) {
			drop.xpos = WINDOW_WIDTH;
		}
		drop.ypos -= drop.ymov;
		if (drop.ypos < 0.0f) {
			drop.ypos = WINDOW_HEIGHT;
		}
	}
	glutPostRedisplay(); // neuzeichenen wenn noch rotiert wird
}

//*********************** myDisplay **********************
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// Bildschirm leeren
	int size = waterdrops.size();
	for (int idx = 0; idx < size; idx++)
	{
		Waterdrop drop = waterdrops[idx];
		glColor3f(drop.red, drop.green, drop.blue);	//blau
		drawCircle(drop.xpos,drop.ypos, drop.radius);
	}

	glutSwapBuffers();	// wegen Double-Buffering
	glFlush();			// send all output to display
}



//************************* main *************************
int main(int argc, char** argv)
{
    timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
	// GLUT
	glutInit(&argc, argv);								// initialize glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);		// setze display mode
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);	// Fenstergrösse
	glutInitWindowPosition(100, 100);					// Fensterposoiton auf Bildschirm
	glutCreateWindow("Raining");						// Fenster generieren
	for (int idx = 0; idx < 50; idx++)
	{
		Waterdrop drop;
		waterdrops.push_back(drop);
	}
	glutDisplayFunc(myDisplay);							// Redraw-Funktion

	myInit();										// persönliche Einstellungen

	glutIdleFunc(myIdle);							// ANIMATION

	glutMainLoop(); 								// Loop
	return 0;
}
