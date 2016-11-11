#include <GL/glut.h>	// OpenGL und GLUT
#include <iostream>	// für cout und cin
#include <math.h>		// für SIN, COS
#include <stdio.h>		//für sprintf
#include <vector>
#include <sys/time.h>
#include "Globals.h"
#include "Waterdrop.h"

#define pi 3.14159265358979323846
#define PI 3.14159265358979323846

//************************************************************

//********VARIABLEN
GLfloat t = 0; 				// Winkel
GLfloat r = 7;				//Radius Kreis, 7 pixel
std::vector<Waterdrop> waterdrops;

float clamp(float value, float min, float max) {
	return std::max(min, std::min(max, value));
}

bool detectCollision(Waterdrop* drop1, Waterdrop *drop2) {
	float dst = sqrt(
			pow((drop2->xpos - drop1->xpos), 2)
					+ pow((drop2->ypos - drop1->ypos), 2));
	float dst2 = dst - drop1->radius - drop2->radius;

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
	float flDrop1 = sqrt(((pow(drop1->radius, 2) * PI) + (pow(drop2->radius, 2) * PI)) / PI);

	drop1->setRadius(sqrt(((pow(drop1->radius, 2) * PI) + (pow(drop2->radius, 2) * PI)) / PI));
	drop1->addJoinedDrop(drop2);
	drop2->setIsActive(false);
	drop2->setXpos(-200); // hiding joined drops

}

//*********************Kreis****************************
void drawCircle(GLfloat xcoord, GLfloat ycoord, GLfloat radius) // Koordinaten x,y, radius und gefüllt mit Farbe
		{
	GLfloat angle = 0; //Winkel
	// Kreis zeichnen
	glBegin(GL_POLYGON);  // gefüllt
	for (angle = 0; angle < 2 * pi; angle += 0.1f) { //Winkel vergrößern
		glVertex2i(xcoord + radius * cos(angle), ycoord + radius * sin(angle)); //berechne alle Kreispunkte
	}
	glEnd();
}

//************************ myInit ************************
void myInit(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);   // set background color
	glPointSize(4.0);					// Punktgröße in Pixel
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();					// lade Einheitsmatrix
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);// Koordinatenursprung in die Mitte

}

//************************ myIdle ************************
void myIdle(void) {
	for (std::vector<Waterdrop>::iterator it = waterdrops.begin();
			it != waterdrops.end(); ++it) {
		Waterdrop & drop = *it;
		if (drop.isActive == true) {
			drop.xpos -= ((drop.xmov + drop.Deceleration) * drop.Direction());
			if ((drop.xpos + (drop.radius) < 0.0f) || (drop.xpos - (drop.radius) > WINDOW_WIDTH)) {
				drop.reset();
			}
			drop.ypos -= (drop.ymov + drop.Deceleration);
			if (drop.ypos + (drop.radius)  < 0.0f) {
				drop.reset();
			}

			for (std::vector<Waterdrop>::iterator it2 = waterdrops.begin();
					it2 != waterdrops.end(); ++it2) {
				if (it != it2) {
//				printf("%i <--> %i - ", it,  it2);
					Waterdrop & drop1 = *it;
					Waterdrop & drop2 = *it2;
					if (drop1.isActive == true && drop2.isActive == true) {
						bool x = detectCollision(&drop1, &drop2);
						if (x == true) {
							joinDrops(&drop1, &drop2);
						}
					}
				}
			}
		}
	}

	glutPostRedisplay(); // neuzeichenen wenn noch rotiert wird
}

//*********************** myDisplay **********************
void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);	// Bildschirm leeren
	int size = waterdrops.size();
	for (int idx = 0; idx < size; idx++) {
		Waterdrop drop = waterdrops[idx];
		glColor3f(drop.red, drop.green, drop.blue);	//blau
		drawCircle(drop.xpos, drop.ypos, drop.radius);
	}

	glutSwapBuffers();	// wegen Double-Buffering
	glFlush();			// send all output to display
}

//************************* main *************************
int main(int argc, char** argv) {
	timeval t1;
	gettimeofday(&t1, NULL);
	srand(t1.tv_usec * t1.tv_sec);
	// GLUT
	glutInit(&argc, argv);								// initialize glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);		// setze display mode
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);	// Fenstergrösse
	glutInitWindowPosition(100, 100);		// Fensterposoiton auf Bildschirm
	glutCreateWindow("Raining");						// Fenster generieren
	for (int idx = 0; idx < 75; idx++) {
		Waterdrop drop;
		waterdrops.push_back(drop);
	}
	glutDisplayFunc(myDisplay);							// Redraw-Funktion

	myInit();										// persönliche Einstellungen

	glutIdleFunc(myIdle);							// ANIMATION

	glutMainLoop(); 								// Loop
	return 0;
}
