// CSC 706 HW 2 Part 1
// Robert Kigobe, Dominic Klusek, Novichenko Konstantin

#include "masks.h"
#include <fstream>
#include <iostream>
#include <GL/glut.h> // (or others, depending on the system in use)
#include "Canvas_freeglut.h"
using namespace std;

char title[] = "Working with Canvas";
Canvas window = Canvas(1000, 1000, title);

void drawPolyLineFile(char* fileName)
{
	fstream inStream;
	inStream.open(fileName, ios::in); // open the file
	if (inStream.fail())
		return;
	//glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	GLint numpolys, numLines, x, y;
	inStream >> numpolys; // read the number of polylines
	for (int j = 0; j < numpolys; j++) // read each polyline
	{
		inStream >> numLines;
		glBegin(GL_LINE_STRIP); // draw the next polyline
		for (int i = 0; i < numLines; i++)
		{
			inStream >> x >> y; // read the next x, y pair
			glVertex2f(x, y);
		}
		glEnd();
	}
	inStream.close();
}

void drawRegularDino(void)
{
	//glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

	glColor3f(0.5, 0.5, 0.5); // set color

	// make a loop that goes around in a circle
	int originX = 250;
	int originY = 750;
	float radius = 150;
	char data[] = "brontoi.dat"; // define polyline file
	for (int i = 0; i < 360; i += 30) {
		//cout << originX + cos((i * pi) / 180) << ", " << originY + sin((i * pi) / 180) << endl;
		window.setViewport(originX + cos((i * pi) / 180) * radius, originY + sin((i * pi) / 180) * radius, 1000, 1000);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glScaled(0.2, 0.2, 0); // scale drawing
		drawPolyLineFile(data);
	}

	//glutSwapBuffers();
}

void drawDownDino(void)
{
	//glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

	glColor3f(0.5, 0.5, 0.5); // set color

	// make a loop that goes around in a circle
	int originX = -150;
	int originY = -150;
	float radius = 150;
	char data[] = "brontoi.dat"; // define polyline file
	float currentAngle = -180;
	float angleMod = 0;
	int offsetIndex = 0;
	for (int i = 0; i < 360; i += 30) {
		window.setViewport(originX + cos((i * pi) / 180) * radius, originY + sin((i * pi) / 180) * radius, 1000, 1000);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-500, 500, -500, 500, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(currentAngle, 0, 0, 1);
		glScalef(0.2, 0.2, 0);
		drawPolyLineFile(data);
		offsetIndex++;
		currentAngle += angleMod;
	}

	//glutSwapBuffers();
}

void draw45Dino(void)
{
	//glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

	glColor3f(0.5, 0.5, 0.5); // set color

	// make a loop that goes around in a circle
	int originX = 250;
	int originY = -200;
	float radius = 150;
	char data[] = "brontoi.dat"; // define polyline file
	float currentAngle = -90;
	float angleMod = 30;
	int offsetIndex = 0;
	for (int i = 0; i < 360; i += 30) {
		window.setViewport(originX + cos((i * pi) / 180) * radius, originY + sin((i * pi) / 180) * radius, 1000, 1000);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-500, 500, -500, 500, -1, 1);
		cout << currentAngle << endl;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glTranslatef(offsetX[offsetIndex], offsetY[offsetIndex], 0);
		glRotatef(currentAngle, 0, 0, 1);
		glScalef(0.2, 0.2, 0);
		drawPolyLineFile(data);
		offsetIndex++;
		currentAngle += angleMod;
	}

	//glutSwapBuffers();
}

void draw4UpsideDownDino(void)
{
	//glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

	glColor3f(0.5, 0.5, 0.5); // set color

	// make a loop that goes around in a circle
	int originX = 250;
	int originY = 250;
	float radius = 150;
	char data[] = "brontoi.dat"; // define polyline file
	float currentAngle = -270;
	float angleMod = 30;
	int offsetIndex = 0;
	for (int i = 0; i < 360; i += 30) {
		window.setViewport(originX + cos((i * pi) / 180) * radius, originY + sin((i * pi) / 180) * radius, 1000, 1000);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-500, 500, -500, 500, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(currentAngle, 0, 0, 1);
		glScalef(0.2, 0.2, 0);
		drawPolyLineFile(data);
		offsetIndex++;
		currentAngle += angleMod;
	}

	//glutSwapBuffers();
}

void drawSections(void) {
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
	drawRegularDino();
	drawDownDino();
	draw45Dino();
	draw4UpsideDownDino();
	glutSwapBuffers();
}

void main(int argc, char** argv)
{
	window.setWindow(0, 1000, 0, 1000);

	glutDisplayFunc(drawSections);

	glutMainLoop(); // Display everything and wait.
}