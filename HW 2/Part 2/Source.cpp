#include "masks.h"
#include <fstream>
#include <iostream>
#include <GL/glut.h> // (or others, depending on the system in use)
#include "Canvas_freeglut.h"
using namespace std;

char title[] = "Working with Canvas";
Canvas window = Canvas(500, 500, title);

void drawYingYang(void) {
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
	// variables that control circle size and location
	float originX = 250;
	float originY = 250;
	float radius = 200;

	// draw top half of symbol
	glColor3f(0, 0, 0); // set color
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 180; i += 1) {
		glVertex2f(originX + cos((i * pi) / 180) * radius, originY + sin((i * pi) / 180) * radius);
	}
	glEnd();

	// draw bottom half of symbol
	glColor3f(1, 1, 1); // set color
	glBegin(GL_POLYGON);
	for (int i = 180; i <= 360; i += 1) {
		glVertex2f(originX + cos((i * pi) / 180) * radius, originY + sin((i * pi) / 180) * radius);
	}
	glEnd();

	// draw circle to create curve of top half
	originX = 350;
	originY = 250;
	radius = 100;
	glColor3f(0, 0, 0); // set color
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i += 1) {
		glVertex2f(originX + cos((i * pi) / 180) * radius, originY + sin((i * pi) / 180) * radius);
	}
	glEnd();

	// draw circle to create curve of bottom half
	originX = 150;
	originY = 250;
	radius = 100;
	glColor3f(1, 1, 1); // set color
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i += 1) {
		glVertex2f(originX + cos((i * pi) / 180) * radius, originY + sin((i * pi) / 180) * radius);
	}
	glEnd();

	// draw "center" dot
	originX = 350;
	originY = 250;
	radius = 25;
	glColor3f(1, 1, 1); // set color
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i += 1) {
		glVertex2f(originX + cos((i * pi) / 180) * radius, originY + sin((i * pi) / 180) * radius);
	}
	glEnd();

	// draw "center" dot
	originX = 150;
	originY = 250;
	radius = 25;
	glColor3f(0, 0, 0); // set color
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i += 1) {
		glVertex2f(originX + cos((i * pi) / 180) * radius, originY + sin((i * pi) / 180) * radius);
	}
	glEnd();

	//draw outline
	originX = 250;
	originY = 250;
	radius = 200;
	glColor3f(0, 0, 0); // set color
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 360; i += 1) {
		glVertex2f(originX + cos((i * pi) / 180) * radius, originY + sin((i * pi) / 180) * radius);
	}
	glEnd();

	glutSwapBuffers();
}

void main(int argc, char** argv)
{
	window.setWindow(0, 500, 0, 500);

	glutDisplayFunc(drawYingYang);

	glutMainLoop(); // Display everything and wait.
}