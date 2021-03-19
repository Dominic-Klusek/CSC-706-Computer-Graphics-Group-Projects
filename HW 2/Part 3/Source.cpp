#include "masks.h"
#include <fstream>
#include <iostream>
#include <GL/glut.h> // (or others, depending on the system in use)
#include "Canvas_freeglut.h"
using namespace std;

char title[] = "Working with Canvas";
Canvas window = Canvas(500, 500, title);
GLenum mode = GL_POLYGON;
GLfloat colorCodes[9] = {0.55, 0.55, 0.55, 0, 0, 0, 0.25, 0.25, 0.25};
int currentFigure = 1;
GLenum style = GL_POLYGON;

void FigureA(void) {
	window.clearScreen(); //clear the window

	// variables to define individual shape parameteres
	float originX = 0;
	float originY = 0;
	float radius = 160;
	float numSides = 3;
	float rotAngle = -30;
	double angle = rotAngle * pi / 180;  // initial angle
	double angleInc = 2 * pi / numSides; //angle increment

	////////  Background polygon ////////
	// change color of backgrounf polygon
	glColor3f(colorCodes[0], colorCodes[1], colorCodes[2]);

	// set up viewport which can be manipulated if needed
	window.setViewport(0, 0, 500, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw background polygon
	glBegin(style);
	glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
	for (int k = 0; k < numSides; k++) // repeat n times
	{
		angle += angleInc;
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
	}
	glEnd();

	// variables to define individual shape parameteres
	originX = 0;
	originY = 0;
	radius = 64;
	numSides = 3;
	rotAngle = 0;
	angle = rotAngle * pi / 180;  // initial angle
	angleInc = 2 * pi / numSides; //angle increment

	// variables for drawing multiple shapes
	float numShapes = 3;
	float shapeAngle = 90;
	float shapeAngleMod = 120;
	float transX = 64;
	float scaleX = 1.5;
	float scaleY = 0.5;

	//////// Star ////////
	// change color of star points
	glColor3f(colorCodes[3], colorCodes[4], colorCodes[5]);

	// draw points of star; which is actually multiple triangles
	for (int i = 0; i < numShapes; i++) {
		// set up viewport
		window.setViewport(0, 0, 500, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// transformations
		glRotatef(shapeAngle, 0, 0, 1);
		glTranslatef(transX, 0, 0);
		glScalef(scaleX, scaleY, 1.0);

		// draw shape
		glBegin(style);
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
		for (int k = 0; k < numSides; k++) // repeat n times
		{
			angle += angleInc;
			glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
			//cout << "Coord: " << "(" << radius * cos(angle) + originX << ", " << radius * sin(angle) + originY << ")" << endl;
		}
		glEnd();

		// change angle for next triangle
		shapeAngle += shapeAngleMod;
	}

	//////// Center shape ////////
	// variables to define individual shape parameteres
	originX = 0;
	originY = 0;
	radius = 32;
	numSides = 3;
	rotAngle = 30;
	angle = rotAngle * pi / 180;  // initial angle
	angleInc = 2 * pi / numSides; //angle increment

	// change color center shape
	glColor3f(colorCodes[6], colorCodes[7], colorCodes[8]);

	// draw center shape, in this case its a triangle
	// set up viewport
	window.setViewport(0, 0, 500, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw inner shape
	glBegin(style);
	glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
	for (int k = 0; k < numSides; k++) // repeat n times
	{
		angle += angleInc;
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
	}
	glEnd();

	glutSwapBuffers();
}

void FigureB(void) {
	window.clearScreen(); //clear the window

	// variables to define shape parameteres
	float originX = 0;
	float originY = 0;
	float radius = 150;
	float numSides = 5;
	float rotAngle = 18;
	double angle = rotAngle * pi / 180;  // initial angle
	double angleInc = 2 * pi / numSides; //angle increment

	////////  Background polygon ////////
	// change color of backgrounf polygon
	glColor3f(colorCodes[0], colorCodes[1], colorCodes[2]);

	// set up viewport which can be manipulated if needed
	window.setViewport(0, 0, 500, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw background polygon
	glBegin(style);
	glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
	for (int k = 0; k < numSides; k++) // repeat n times
	{
		angle += angleInc;
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
	}
	glEnd();

	//////// Star ////////
	// variables to define individual shape parameteres
	originX = 0;
	originY = 0;
	radius = 61;
	numSides = 3;
	rotAngle = 0;
	angle = rotAngle * pi / 180;  // initial angle
	angleInc = 2 * pi / numSides; //angle increment

	// variables to define individual shape parameteres
	float numShapes = 5;
	float shapeAngle = -54;
	float shapeAngleMod = 72;
	float transX = 60;
	float scaleX = 1.5;
	float scaleY = 0.2;

	// change color of star points
	glColor3f(colorCodes[3], colorCodes[4], colorCodes[5]);

	// draw points of star; which is actually multiple triangles
	for (int i = 0; i < numShapes; i++) {
		// set up viewport
		window.setViewport(0, 0, 500, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// transformations
		glRotatef(shapeAngle, 0, 0, 1);
		glTranslatef(transX, 0, 0);
		glScalef(scaleX, scaleY, 1.0);

		// draw shape
		glBegin(style);
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
		for (int k = 0; k < numSides; k++) // repeat n times
		{
			angle += angleInc;
			glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
			//cout << "Coord: " << "(" << radius * cos(angle) + originX << ", " << radius * sin(angle) + originY << ")" << endl;
		}
		glEnd();

		// change angle for next triangle
		shapeAngle += shapeAngleMod;
	}

	//////// Center shape ////////
	// variables to define individual shape parameteres
	originX = 0;
	originY = 0;
	radius = 18;
	numSides = 5;
	rotAngle = 54;
	angle = rotAngle * pi / 180;  // initial angle
	angleInc = 2 * pi / numSides; //angle increment

	// change color center shape
	glColor3f(colorCodes[6], colorCodes[7], colorCodes[8]);

	// draw center shape, in this case its a pentagon
	// set up viewport
	window.setViewport(0, 0, 500, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw inner shape
	glBegin(style);
	glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
	for (int k = 0; k < numSides; k++) // repeat n times
	{
		angle += angleInc;
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
	}
	glEnd();

	glutSwapBuffers();
}

void FigureC(void) {
	window.clearScreen(); //clear the window

	//////// Star ////////
	// variables to define individual shape parameteres
	float originX = 0;
	float originY = 0;
	float radius = 60;
	float numSides = 3;
	float rotAngle = 0;
	float angle = rotAngle * pi / 180;  // initial angle
	float angleInc = 2 * pi / numSides; //angle increment

	// variables to define individual shape parameteres
	float numShapes = 7;
	float shapeAngle = -62;
	float shapeAngleMod = 51;
	float transX = 70;
	float scaleX = 1.5;
	float scaleY = 0.24;

	// change color of star points
	glColor3f(colorCodes[3], colorCodes[4], colorCodes[5]);

	// draw points of star; which is actually multiple triangles
	for (int i = 0; i < numShapes; i++) {
		// set up viewport
		window.setViewport(0, 0, 500, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// transformations
		glRotatef(shapeAngle, 0, 0, 1);
		glTranslatef(transX, 0, 0);
		glScalef(scaleX, scaleY, 1.0);

		// draw shape
		glBegin(style);
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
		for (int k = 0; k < numSides; k++) // repeat n times
		{
			angle += angleInc;
			glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
			//cout << "Coord: " << "(" << radius * cos(angle) + originX << ", " << radius * sin(angle) + originY << ")" << endl;
		}
		glEnd();

		// change angle for next triangle
		shapeAngle += shapeAngleMod;
	}

	//////// Center shape ////////
	// variables to define individual shape parameteres
	originX = 0;
	originY = 0;
	radius = 29;
	numSides = 7;
	rotAngle = 13;
	angle = rotAngle * pi / 180;  // initial angle
	angleInc = 2 * pi / numSides; //angle increment

	// change color center shape depends on the style
	if (style == GL_LINE_STRIP || style == GL_LINE_STIPPLE) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3f(colorCodes[3], colorCodes[4], colorCodes[5]);
	}

	// draw center shape, in this case its a sectagon
	// set up viewport
	window.setViewport(0, 0, 500, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw inner shape (must be polygon for easier covering of center
	glBegin(GL_POLYGON);
	glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
	for (int k = 0; k < numSides; k++) // repeat n times
	{
		angle += angleInc;
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
	}
	glEnd();

	glutSwapBuffers();
}

void FigureD(void) {
	window.clearScreen(); //clear the window

	// variables to define shape parameteres
	float originX = 0;
	float originY = 0;
	float radius = 150;
	float numSides = 6;
	float rotAngle = 90;
	double angle = rotAngle * pi / 180;  // initial angle
	double angleInc = 2 * pi / numSides; //angle increment

	////////  Background polygon ////////
	// change color of backgrounf polygon
	glColor3f(colorCodes[0], colorCodes[1], colorCodes[2]);

	// set up viewport which can be manipulated if needed
	window.setViewport(0, 0, 500, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw background polygon
	glBegin(style);
	glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
	for (int k = 0; k < numSides; k++) // repeat n times
	{
		angle += angleInc;
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
	}
	glEnd();

	//////// Star ////////
	// variables to define individual shape parameteres
	originX = 0;
	originY = 0;
	radius = 50;
	numSides = 3;
	rotAngle = 0;
	angle = rotAngle * pi / 180;  // initial angle
	angleInc = 2 * pi / numSides; //angle increment

	// variables to define individual shape parameteres
	float numShapes = 6;
	float shapeAngle = -90;
	float shapeAngleMod = 60;
	float transX = 71;
	float scaleX = 1.6;
	float scaleY = 0.5;

	// change color of star points
	glColor3f(colorCodes[3], colorCodes[4], colorCodes[5]);

	// draw points of star; which is actually multiple triangles
	for (int i = 0; i < numShapes; i++) {
		// set up viewport
		window.setViewport(0, 0, 500, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// transformations
		glRotatef(shapeAngle, 0, 0, 1);
		glTranslatef(transX, 0, 0);
		glScalef(scaleX, scaleY, 1.0);

		// draw shape
		glBegin(style);
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
		for (int k = 0; k < numSides; k++) // repeat n times
		{
			angle += angleInc;
			glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
			//cout << "Coord: " << "(" << radius * cos(angle) + originX << ", " << radius * sin(angle) + originY << ")" << endl;
		}
		glEnd();

		// change angle for next triangle
		shapeAngle += shapeAngleMod;
	}

	//////// Center shape ////////
	// variables to define individual shape parameteres
	originX = 0;
	originY = 0;
	radius = 40;
	numSides = 6;
	rotAngle = 0;
	angle = rotAngle * pi / 180;  // initial angle
	angleInc = 2 * pi / numSides; //angle increment

	// draw center shape, in this case its a pentagon
	// set up viewport
	window.setViewport(0, 0, 500, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw inner shape

	if (style == GL_LINE_STRIP || style == GL_LINE_STIPPLE) {
		// change color center shape(must be white to match background)
		glColor3f(1, 1, 1);
		// need to hide inner triangle edges
		glBegin(GL_POLYGON);
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
		for (int k = 0; k < 360; k++) // repeat n times
		{
			glVertex2d(originX + cos((k * pi) / 180) * radius, originY + sin((k * pi) / 180) * radius);
		}
		glEnd();

		// change color center shape
		glColor3f(colorCodes[6], colorCodes[7], colorCodes[8]);

		// draw center shape
		glBegin(style);
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
		for (int k = 0; k < 360; k++) // repeat n times
		{
			glVertex2d(originX + cos((k * pi) / 180) * radius, originY + sin((k * pi) / 180) * radius);
		}
		glEnd();
	}
	else {
		// change color center shape outline
		glColor3f(colorCodes[6], colorCodes[7], colorCodes[8]);

		// draw center shape
		glBegin(style);
		glVertex2f(radius * cos(angle) + originX, radius * sin(angle) + originY);
		for (int k = 0; k < 360; k++) // repeat n times
		{
			glVertex2d(originX + cos((k * pi) / 180) * radius, originY + sin((k * pi) / 180) * radius);
		}
		glEnd();
	}

	glutSwapBuffers();
}

void clearScreen() {
	window.clearScreen();
	glutSwapBuffers();
}

void mainMenu(int value) {
	switch (value) {
		case 1:
			clearScreen();
			break;
		default:
			exit(0);
			break;
	}
}

void figureMenu(int value) {
	/* This function is both for the menu, and acts as a redraw function 
	when used in conjunction with the global currentFigure variable*/
	if (value == 1) {
		FigureA();
	}
	else if (value == 2) {
		FigureB();
	}
	else if (value == 3) {
		FigureC();
	}
	else if (value == 4) {
		FigureD();
	}

	// change current figure
	currentFigure = value;
	
}

void backgroundColorMenu(int value) {
	if (value == 1) {
		// change color to black
		colorCodes[0] = 0;
		colorCodes[1] = 0;
		colorCodes[2] = 0;
	}
	else if (value == 2) {
		// change color to red
		colorCodes[0] = 1;
		colorCodes[1] = 0;
		colorCodes[2] = 0;
	}
	else if (value == 3) {
		// change color to green
		colorCodes[0] = 0;
		colorCodes[1] = 1;
		colorCodes[2] = 0;
	}
	else if (value == 4) {
		// change color to blue
		colorCodes[0] = 0;
		colorCodes[1] = 0;
		colorCodes[2] = 1;
	}
	else if (value == 5) {
		// change color to white
		colorCodes[0] = 1;
		colorCodes[1] = 1;
		colorCodes[2] = 1;
	}

	// redraw figure with new color
	figureMenu(currentFigure);

}

void starColorMenu(int value) {
	if (value == 1) {
		// change color to black
		colorCodes[3] = 0;
		colorCodes[4] = 0;
		colorCodes[5] = 0;
	}
	else if (value == 2) {
		// change color to red
		colorCodes[3] = 1;
		colorCodes[4] = 0;
		colorCodes[5] = 0;
	}
	else if (value == 3) {
		// change color to green
		colorCodes[3] = 0;
		colorCodes[4] = 1;
		colorCodes[5] = 0;
	}
	else if (value == 4) {
		// change color to blue
		colorCodes[3] = 0;
		colorCodes[4] = 0;
		colorCodes[5] = 1;
	}
	else if (value == 5) {
		// change color to white
		colorCodes[3] = 1;
		colorCodes[4] = 1;
		colorCodes[5] = 1;
	}

	// redraw figure with new color
	figureMenu(currentFigure);

}

void centerColorMenu(int value) {
	if (value == 1) {
		// change color to black
		colorCodes[6] = 0;
		colorCodes[7] = 0;
		colorCodes[8] = 0;
	}
	else if (value == 2) {
		// change color to red
		colorCodes[6] = 1;
		colorCodes[7] = 0;
		colorCodes[8] = 0;
	}
	else if (value == 3) {
		// change color to green
		colorCodes[6] = 0;
		colorCodes[7] = 1;
		colorCodes[8] = 0;
	}
	else if (value == 4) {
		// change color to blue
		colorCodes[6] = 0;
		colorCodes[7] = 0;
		colorCodes[8] = 1;
	}
	else if (value == 5) {
		// change color to white
		colorCodes[6] = 1;
		colorCodes[7] = 1;
		colorCodes[8] = 1;
	}

	// redraw figure with new color
	figureMenu(currentFigure);

}

void styleMenu(int value) {
	if (value == 1) {
		glLineWidth(1.0);
		glDisable(GL_LINE_STIPPLE);
		style = GL_POLYGON;
	} 
	else if (value == 2) {
		glLineWidth(1.0);
		glDisable(GL_LINE_STIPPLE);
		style = GL_LINE_STRIP;
	} 
	else if (value == 3) {
		style = GL_LINE_STRIP;
		glLineStipple(5, 111000111000);
		glEnable(GL_LINE_STIPPLE);
		glLineWidth(2.0);
	}

	// redraw figure with new style
	figureMenu(currentFigure);

}

void testMenu(int value) {

}

void main(int argc, char** argv)
{
	window.setWindow(-250, 250, -250, 250);

	glutDisplayFunc(FigureA);

	// create menu
	int baseMenu = glutCreateMenu(mainMenu);  // the base menu
	int figSubMenu = glutCreateMenu(figureMenu); // submenu for drawing different figures
	int colorSubMenu = glutCreateMenu(testMenu); // submenu for color submenus
	int backColorSubMeny = glutCreateMenu(backgroundColorMenu); // the submenu for choosing the background polygon color(if applicable)
	int starColorSubMenu = glutCreateMenu(starColorMenu); // the submenu for choosing the star color
	int centerColorSubMenu = glutCreateMenu(centerColorMenu); // the submenu for chooseing the middle polygon color
	int styleSubMenu = glutCreateMenu(styleMenu); // the submenu to choose drawing style

	// start menu
	glutSetMenu(baseMenu);
	glutAddMenuEntry("Clear Screen", 1);

	// add figure sub menu
	glutAddSubMenu("Figure Menu", figSubMenu);
	glutSetMenu(figSubMenu);
	glutAddMenuEntry("Draw Figure A", 1);
	glutAddMenuEntry("Draw Figure B", 2);
	glutAddMenuEntry("Draw Figure C", 3);
	glutAddMenuEntry("Draw Figure D", 4);
	glutSetMenu(baseMenu);

	// add color submenu for various parts
	glutAddSubMenu("Color Menu", colorSubMenu);
	glutSetMenu(colorSubMenu);
	glutAddSubMenu("Background Poly Color Menu", backColorSubMeny);
	glutSetMenu(backColorSubMeny);
	glutAddMenuEntry("Black", 1);
	glutAddMenuEntry("Red", 2);
	glutAddMenuEntry("Green", 3);
	glutAddMenuEntry("Blue", 4);
	glutAddMenuEntry("White", 5);
	glutSetMenu(baseMenu);

	glutSetMenu(colorSubMenu);
	glutAddSubMenu("Star Color Menu", starColorSubMenu);
	glutSetMenu(starColorSubMenu);
	glutAddMenuEntry("Black", 1);
	glutAddMenuEntry("Red", 2);
	glutAddMenuEntry("Green", 3);
	glutAddMenuEntry("Blue", 4);
	glutAddMenuEntry("White", 5);
	glutSetMenu(baseMenu);

	glutSetMenu(colorSubMenu);
	glutAddSubMenu("Center Polygon Color Menu", centerColorSubMenu);
	glutSetMenu(centerColorSubMenu);
	glutAddMenuEntry("Black", 1);
	glutAddMenuEntry("Red", 2);
	glutAddMenuEntry("Green", 3);
	glutAddMenuEntry("Blue", 4);
	glutAddMenuEntry("White", 5);
	glutSetMenu(baseMenu);

	// add style submenu
	glutAddSubMenu("Style Menu", styleSubMenu);
	glutSetMenu(styleSubMenu);
	glutAddMenuEntry("Polygon", 1);
	glutAddMenuEntry("Line Strip", 2);
	glutAddMenuEntry("Line Stipple", 3);
	glutSetMenu(baseMenu);

	// add final exit option
	glutAddMenuEntry("Exit", 6);

	// set button to open menu (in this case its the right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop(); // Display everything and wait.
}