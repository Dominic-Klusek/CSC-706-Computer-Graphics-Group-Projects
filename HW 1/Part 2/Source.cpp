#include "masks.h"
#include <GL/glut.h> // (or others, depending on the system in use)
#include<SOIL/SOIL.h>
#include<iostream>
using namespace std;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // Set display-window color to white.
	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	glEnable(GL_TEXTURE_2D);
	gluOrtho2D(0.0, 200.0, 0.0, 250.0);
}

GLuint glInitTexture(char* filename)
{
	GLuint t = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	glBindTexture(GL_TEXTURE_2D, t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return t;
}

void drawDoor(float x, float y, float width, float height) {
	// draw door
	float doorX = round(x + width / 3);
	float doorY = round(y + height / 1.25);
	glBegin(GL_LINE_STRIP);
		glVertex2f(doorX, y);
		glVertex2f(doorX + width / 4, y);
		glVertex2f(doorX + width / 4, doorY);
		glVertex2f(doorX, doorY);
		glVertex2f(doorX, y);
	glEnd();

	// draw door knob
	float knobX = doorX + width / 5;
	float knobY = y + height / 3;
	float knobRadius = ((doorX + width / 4) - doorX) * doorX / (doorX + width / 4) / 4;
	glBegin(GL_LINE_STRIP);
	for (double i = 0; i <= 360; i++)
	{
		glVertex2f(knobX + cos((i * pi) / 180) * knobRadius, knobY + sin((i * pi) / 180) * knobRadius);
	}
	glEnd();
}

void drawWindow(float x, float y, float width, float height) {
	float offset = round(x + width / 3);
	// draw window area
	float windowX = offset + width / 3.0;
	float windowY = y + height / 2;
	float windowWidth = width / 3.5;
	float windowHeight = height / 3.0;
	float sillOffset = width / 30.0;
	float sillThickness = height / 20.0;
	//float frameOffset = sillOffset / 4.0;
	float frameThickness = sillThickness / 4.0;

	// glass background
	glColor3f(0.40, 0.80, 1.00);
	glBegin(GL_QUADS);
		glVertex2f(windowX, windowY + windowHeight);
		glVertex2f(windowX, windowY);
		glVertex2f(windowX + windowWidth, windowY);
		// add light source
		glColor3f(0.70, 0.90, 1.00);
		glVertex2f(windowX + windowWidth, windowY + windowHeight);
	glEnd();

	// revert color to black
	glColor3f(0.0, 0.0, 0.00);

	// draw window frame
	glBegin(GL_QUADS);
		glVertex2f(windowX - frameThickness, windowY + windowHeight + frameThickness);
		glVertex2f(windowX - frameThickness, windowY);
		glVertex2f(windowX, windowY);
		glVertex2f(windowX, windowY + windowHeight + frameThickness);
	glEnd();

	glBegin(GL_QUADS);
		glVertex2f(windowX - frameThickness, windowY + windowHeight + frameThickness * 2.0);
		glVertex2f(windowX + windowWidth + frameThickness, windowY + windowHeight + frameThickness * 2.0);
		glVertex2f(windowX + windowWidth + frameThickness, windowY + windowHeight);
		glVertex2f(windowX - frameThickness, windowY + windowHeight);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(windowX + windowWidth, windowY + windowHeight + frameThickness);
	glVertex2f(windowX + windowWidth + frameThickness, windowY + windowHeight + frameThickness);
	glVertex2f(windowX + windowWidth + frameThickness, windowY);
	glVertex2f(windowX + windowWidth, windowY);
	glEnd();

	// draw window
	glBegin(GL_LINE_STRIP);
		glVertex2f(windowX, windowY);
		glVertex2f(windowX + windowWidth, windowY);
		glVertex2f(windowX + windowWidth, windowY + windowHeight);
		glVertex2f(windowX, windowY + height / 3);
		glVertex2f(windowX, windowY);
	glEnd();

	// draw window supports
	glBegin(GL_LINE_STRIP);
		glVertex2f(windowX + windowWidth / 2.0, windowY);
		glVertex2f(windowX + windowWidth / 2.0, windowY + windowHeight / 2.0);
		glVertex2f(windowX, windowY + windowHeight / 2.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex2f(windowX + windowWidth / 2.0, windowY + windowHeight / 2.0);
		glVertex2f(windowX + windowWidth / 2.0, windowY + windowHeight);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex2f(windowX + windowWidth / 2.0, windowY + windowHeight / 2.0);
		glVertex2f(windowX + windowWidth, windowY + windowHeight / 2.0);
	glEnd();

	// draw window sill
	glBegin(GL_QUADS);
		glVertex2f(windowX - sillOffset, windowY);
		glVertex2f(windowX - sillOffset, windowY - sillThickness);
		glVertex2f(windowX + windowWidth + sillOffset, windowY - sillThickness);
		glVertex2f(windowX + windowWidth + sillOffset, windowY);
	glEnd();
}

void drawHome(float x, float y, float width, float height,
	float colorR = 0.0, float colorG = 0.0, float colorB = 0.0) {
	// draw house main body
	glColor3f(colorR, colorG, colorB);
	glBegin(GL_LINE_STRIP);
		glVertex2i(x, y);
		glVertex2i(x + width, y);
		glVertex2i(x + width, y + height);
		glVertex2i(x, y + height);
		glVertex2i(x, y);
	glEnd();

	// draw house roof
	// constant are to account for some space between roof and house main body, as well as to extend the roof past the walls of the house
	glBegin(GL_TRIANGLES);
		glVertex2i(x - width / 6, y + height - 2);
		glColor3f(colorR+ 0.5, colorG + 0.5, colorB + 0.5);
		glVertex2i(x + width / 2, round(y + height * 1.45)); // control roof tallness
		glColor3f(colorR, colorG, colorB);
		glVertex2i(x + width + width  / 6, y + height - 2);
	glEnd();

	drawDoor(x, y, width, height);

	drawWindow(x, y, width, height);

	glFlush(); // Process all OpenGL routines as quickly as possible.
}

void drawShapes(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

	drawHome(20, 20, 80, 80);
	drawHome(150, 20, 30, 30);

	glFlush(); // Process all OpenGL routines as quickly as possible.

	glEnable(GL_TEXTURE_2D); // renable textures in case of resizing window
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // Initialize GLUT.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode.

	glutInitWindowPosition(50, 100); // Set top-left display-window position.

	glutInitWindowSize(400, 300); // Set display-window width and height.

	glutCreateWindow("Drawing a Neightborhood"); // Create display window.

	init(); // Execute initialization procedure.

	glutDisplayFunc(drawShapes); // Send graphics to display window.

	glutMainLoop(); // Display everything and wait.
}