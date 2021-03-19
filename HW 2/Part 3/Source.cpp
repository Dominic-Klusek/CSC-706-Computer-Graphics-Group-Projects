#include "masks.h"
#include <fstream>
#include <iostream>
#include <GL/glut.h> // (or others, depending on the system in use)
#include "Canvas_freeglut.h"
using namespace std;

char title[] = "Working with Canvas";
Canvas window = Canvas(500, 500, title);
GLenum mode = GL_POLYGON;

void FigureA(void) {
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

	// variables to define individual shape parameteres
	float originX = 0;
	float originY = 0;
	float radius = 50;
	float numSides = 3;
	float rotAngle = 60;
	double angle = rotAngle * pi / 180;  // initial angle
	double angleInc = 2 * pi / numSides; //angle increment

	// variables for drawing multiple shapes
	float numShapes = 3;
	float shapeAngle = 30;
	float shapeAngleMod = 120;
	float transX = 42;
	float scaleX = 0.5;
	float scaleY = 2.2;

	for (int i = 0; i < numShapes; i++) {
		window.setViewport(0, 0, 500, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(shapeAngle, 0, 0, 1);
		glTranslatef(transX, 0, 0);
		glScalef(scaleX, scaleY, 1.0);

		glBegin(GL_LINE_STRIP);
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
		for (int k = 0; k < numSides; k++) // repeat n times
		{
			angle += angleInc;
			glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
			cout << "Coord: " << "(" << radius * cos(angle) + originX << ", " << radius * sin(angle) + originY << ")" << endl;
		}
		glEnd();

		shapeAngle += shapeAngleMod;
	}

	//embedded star
	// lines meet above halfway point of each line segment
	// could also just draw a triangle and then rotate and transform it

	glutSwapBuffers();
}

void FigureB(void) {
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

	// variables to define shape parameteres
	float originX = 0;
	float originY = 0;
	float radius = 50;
	float numSides = 3;
	float rotAngle = 60;
	double angle = rotAngle * pi / 180;  // initial angle
	double angleInc = 2 * pi / numSides; //angle increment

	float numShapes = 5;
	float shapeAngle = -90;
	float shapeAngleMod = 72;
	float transX = 100;
	float scaleX = 1.4;
	float scaleY = 2.3;

	for (int i = 0; i < numShapes; i++) {
		window.setViewport(0, 0, 500, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(shapeAngle, 0, 0, 1);
		glTranslatef(transX, 0, 0);
		glScalef(scaleX, scaleY, 1.0);

		glBegin(GL_LINE_STRIP);
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
		for (int k = 0; k < numSides; k++) // repeat n times
		{
			angle += angleInc;
			glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
			cout << "Coord: " << "(" << radius * cos(angle) + originX << ", " << radius * sin(angle) + originY << ")" << endl;
		}
		glEnd();

		shapeAngle += shapeAngleMod;
	}

	glutSwapBuffers();
}

void FigureC(void) {
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

	// variables to define individual shape parameteres
	float originX = 0;
	float originY = 0;
	float radius = 50;
	float numSides = 3;
	float rotAngle = 60;
	double angle = rotAngle * pi / 180;  // initial angle
	double angleInc = 2 * pi / numSides; //angle increment

	// variables for drawing multiple shapes
	float numShapes = 5;
	float shapeAngle = -90;
	float shapeAngleMod = 72;
	float transX = 102;
	float scaleX = 1.4;
	float scaleY = 2.3;

	for (int i = 0; i < numShapes; i++) {
		window.setViewport(0, 0, 500, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(shapeAngle, 0, 0, 1);
		glTranslatef(transX, 0, 0);
		glScalef(scaleX, scaleY, 1.0);

		glBegin(GL_LINE_STRIP);
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
		for (int k = 0; k < numSides; k++) // repeat n times
		{
			angle += angleInc;
			glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
			cout << "Coord: " << "(" << radius * cos(angle) + originX << ", " << radius * sin(angle) + originY << ")" << endl;
		}
		glEnd();

		shapeAngle += shapeAngleMod;
	}

	glFlush();

	//draw white n-gons to remove border
	// variables for drawing multiple shapes
	originX = 0;
	originY = 0;
	radius = 169;
	numSides = 5;
	rotAngle = 18;
	angle = rotAngle * pi / 180;  // initial angle
	angleInc = 2 * pi / numSides; //angle increment

	glLineWidth(2.0);
	glEnable(GL_LINE_SMOOTH);
	//glColor3f(0.6, 0.25, 0.45);
	glColor3f(1, 1, 1);
	window.setViewport(0, 0, 500, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_LINE_STRIP);
	glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
	for (int k = 0; k < numSides; k++) // repeat n times
	{
		angle += angleInc;
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
		cout << "Coord: " << "(" << radius * cos(angle) + originX << ", " << radius * sin(angle) + originY << ")" << endl;
	}
	glEnd();

	glLineWidth(1.0);

	glutSwapBuffers();
}

void FigureD(void) {
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

	// variables to define shape parameteres
	float originX = 0;
	float originY = 0;
	float radius = 50;
	float numSides = 3;
	float rotAngle = 60;
	double angle = rotAngle * pi / 180;  // initial angle
	double angleInc = 2 * pi / numSides; //angle increment

	float numShapes = 6;
	float shapeAngle = -30;
	float shapeAngleMod = 60;
	float transX = 100;
	float scaleX = 1.4;
	float scaleY = 1.8;

	for (int i = 0; i < numShapes; i++) {
		window.setViewport(0, 0, 500, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(shapeAngle, 0, 0, 1);
		glTranslatef(transX, 0, 0);
		glScalef(scaleX, scaleY, 1.0);

		glBegin(GL_LINE_STRIP);
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
		for (int k = 0; k < numSides; k++) // repeat n times
		{
			angle += angleInc;
			glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
			cout << "Coord: " << "(" << radius * cos(angle) + originX << ", " << radius * sin(angle) + originY << ")" << endl;
		}
		glEnd();

		shapeAngle += shapeAngleMod;
	}

	glutSwapBuffers();
}

void mymenu(int value) {
	switch (value) {
		case 1:
			glColor3f(1, 1, 1);
				glBegin(GL_POLYGON);
				glVertex2f(-250, -250);
				glVertex2f(250, -250);
				glVertex2f(250, 250);
				glVertex2f(-250, 250);
			glEnd();
			glutSwapBuffers();
			glColor3f(0, 0, 0);
		case 2:
			FigureA();
			break;
		case 3:
			FigureB();
			break;
		case 4:
			FigureC();
			break;
		case 5:
			FigureD();
			break;
		case 6:
			exit(0);
			break;
		default:
			cout << "Invalid menu option selected." << endl;
			exit(0);
	}
	if (value == 6)
		exit(0);
}

void main(int argc, char** argv)
{
	window.setWindow(-250, 250, -250, 250);

	glutDisplayFunc(FigureD);

	glutCreateMenu(mymenu);  // single menu, no need for id
	glutAddMenuEntry("Draw Figure A", 1);
	glutAddMenuEntry("Draw Figure B", 2);
	glutAddMenuEntry("Draw Figure C", 3);
	glutAddMenuEntry("Draw Figure D", 4);
	glutAddMenuEntry("Clear Screen", 5);
	glutAddMenuEntry("Exit", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop(); // Display everything and wait.
}