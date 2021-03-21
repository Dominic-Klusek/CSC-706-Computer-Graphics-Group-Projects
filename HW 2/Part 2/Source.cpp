#include "masks.h"
#include <fstream>
#include <iostream>
#include <GL/glut.h> // (or others, depending on the system in use)
#include "Canvas_freeglut.h"
using namespace std;

char title[] = "Working with Canvas";
Canvas window = Canvas(500, 500, title);

void drawCircle(float originX, float originY, float radius, float start, float end, GLenum style) {
	glBegin(style);
	for (int i = start; i <= end; i += 1) {
		glVertex2f(originX + cos((i * pi) / 180) * radius, originY + sin((i * pi) / 180) * radius);
	}
	glEnd();
}

void drawYingYang(void) {
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

	// draw top half of symbol
	glColor3f(0, 0, 0); // set color
	drawCircle(250, 250, 200, 0, 180, GL_POLYGON);

	// draw bottom half of symbol
	glColor3f(1, 1, 1); // set color
	drawCircle(250, 250, 200, 180, 360, GL_POLYGON);

	// draw circle to create curve of top half
	glColor3f(0, 0, 0); // set color
	drawCircle(350, 250, 100, 0, 360, GL_POLYGON);

	// draw circle to create curve of bottom half
	glColor3f(1, 1, 1); // set color
	drawCircle(150, 250, 100, 0, 360, GL_POLYGON);

	// draw "center" dot
	glColor3f(1, 1, 1); // set color
	drawCircle(350, 250, 25, 0, 360, GL_POLYGON);

	// draw "center" dot
	glColor3f(0, 0, 0); // set color
	drawCircle(150, 250, 25, 0, 360, GL_POLYGON);

	//draw outline
	glColor3f(0, 0, 0); // set color
	drawCircle(250, 250, 200, 0, 360, GL_LINE_STRIP);

	glutSwapBuffers();
}

void main(int argc, char** argv)
{
	window.setWindow(0, 500, 0, 500);

	glutDisplayFunc(drawYingYang);

	glutMainLoop(); // Display everything and wait.
}