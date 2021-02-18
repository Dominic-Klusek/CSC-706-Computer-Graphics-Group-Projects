#include "masks.h"
#include <GL/glut.h> // (or others, depending on the system in use)
#include<SOIL/SOIL.h>
#include<iostream>
using namespace std;

// glocal variables
double windowHeight;
double windowWidth;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // Set display-window color to white.
	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	glEnable(GL_TEXTURE_2D);
	gluOrtho2D(0.0, 800, 0.0, 800);
	windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	windowWidth = glutGet(GLUT_WINDOW_WIDTH);
}

GLuint glInitTexture(char* filename)
{
	GLuint t = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	glBindTexture(GL_TEXTURE_2D, t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return t;
}

void drawRoad() {
	// draw a quad slanted to the right

}

void drawLand() {
	// draw grass
	glColor3f(0.08, 0.50, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(0, windowHeight / 3.0);
		glVertex2f(windowWidth / 2.0, windowHeight / 6.0);
		glVertex2f(windowWidth, windowHeight / 2.0);
		glVertex2f(windowWidth, 0);
	glEnd();

	glColor3f(0.12, 0.70, 0.0);
	glEnable(GL_POLYGON_STIPPLE); // Enable POLYGON STIPPLE
	glPolygonStipple(grassMask);
	glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(0, windowHeight / 3.0);
		glVertex2f(windowWidth / 2.0, windowHeight / 6.0);
		glVertex2f(windowWidth, windowHeight / 2.0);
		glVertex2f(windowWidth, 0);
	glEnd();
	glDisable(GL_POLYGON_STIPPLE);

	// draw "dirt cliff"
	glColor3f(0.40, 0.20, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(0, windowHeight / 8.0);
		glVertex2f(windowWidth / 2.0, windowHeight / 16.0);
		glVertex2f(windowWidth, windowHeight / 8.0);
		glVertex2f(windowWidth, 0);
	glEnd();
}

void drawSun(float sunCenterX = 400.0, float sunCenterY = 400.0, float sunRadius = 50.0) {
	glColor3f(0.90, 0.90, 0.0);
	drawACircleWith(sunCenterX, sunCenterY, 0, 360, sunRadius, sunRadius, GL_POLYGON);
}

void drawSky() {
	// TODO, implement sky function
	float sunCenterX = 400.0;
	float sunCenterY = 400.0;
	float sunRadius = windowWidth / 5.0;


	cout << "Window Height: " << windowHeight << endl;
	cout << "Window Wodth: " << windowWidth << endl;

	glColor3f(0.50, 0.83, 1.00);
	glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(windowWidth, 0);
		glColor3f(1.0, 0.85, 0.10);
		//glColor3f(1.0, 0.0, 0.00);
		glVertex2f(windowWidth, windowHeight);
		glColor3f(0.50, 0.83, 1.00);
		glVertex2f(0, windowHeight);
	glEnd();

	drawSun(800, 800);

	glFlush();
}

void drawDoor(float x, float y, float width, float height) {
	// door parameters
	float doorX = round(x + width / 3);
	float doorY = round(y + height / 1.5);

	// draw door
	glColor3f(0.29, 0.19, 0.0);
	glBegin(GL_LINE_STRIP);
		glVertex2f(doorX, y);
		glVertex2f(doorX + width / 4, y);
		glVertex2f(doorX + width / 4, doorY);
		glVertex2f(doorX, doorY);
		glVertex2f(doorX, y);
	glEnd();

	// door know parameters
	float knobX = doorX + width / 5;
	float knobY = y + height / 3;
	float knobRadius = width / 30.0;

	glColor3f(0.0, 0.0, 0.0);
	// draw door knob
	drawACircleWith(knobX, knobY, 0, 360, knobRadius, knobRadius, GL_POLYGON);

	// draw door knob lock
	glColor3f(0.35, 0.35, 0.35);
	drawACircleWith(knobX, knobY, 0, 360, knobRadius / 4.0, knobRadius / 4.0, GL_POLYGON);
	
	// reset color to black
	glColor3f(0.0, 0.0, 0.0);
}

void drawWindow(float x, float y, float width, float height) {
	// draw window area
	float offset = round(x + width / 3);
	float windowX = offset + width / 3.0;
	float windowY = y + height / 2;
	float windowWidth = width / 3.5;
	float windowHeight = height / 3.0;
	float sillOffset = width / 30.0;
	float sillThickness = height / 20.0;
	float frameThickness = sillThickness / 4.0;

	// glass background
	glColor3f(0.50, 0.75, 1.00);
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
		glVertex2f(windowX + windowWidth, windowY + windowHeight + frameThickness * 2.0);
		glColor3f(0.5, 0.5, 0.5);
		glVertex2f(windowX + windowWidth + frameThickness, windowY + windowHeight + frameThickness * 2.0);
		glVertex2f(windowX + windowWidth + frameThickness, windowY);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2f(windowX + windowWidth, windowY);
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
		glColor3f(0.5, 0.5, 0.5);
		glVertex2f(windowX + windowWidth + sillOffset, windowY);
		glColor3f(0.0, 0.0, 0.0);
	glEnd();
}

void drawHome(float x, float y, float width, float height,
	float colorR = 1.0, float colorG = 1.0, float colorB = 1.0) {
	// draw house main body
	glColor3f(colorR, colorG, colorB);
	glBegin(GL_POLYGON);
		glVertex2i(x, y);
		glVertex2i(x + width, y);
		glColor3f(0.5, 0.5, 0.5);
		glVertex2i(x + width, y + height);
		glColor3f(colorR, colorG, colorB);
		glVertex2i(x, y + height);
		glVertex2i(x, y);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
		glVertex2i(x, y);
		glVertex2i(x + width, y);
		glVertex2i(x + width, y + height);
		glVertex2i(x, y + height);
		glVertex2i(x, y);
	glEnd();

	// draw house roof
	// constant are to account for some space between roof and house main body, as well as to extend the roof past the walls of the house
	glBegin(GL_POLYGON);
		glVertex2i(x - width / 6, y + height - 2);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2i(x + width / 2, round(y + height * 1.45)); // control roof tallness
		glVertex2i(x + width + width / 6, y + height - 2);
		glColor3f(0, 0, 0);
	glEnd();


	glEnable(GL_POLYGON_STIPPLE); // Enable POLYGON STIPPLE
	glPolygonStipple(roofMask);
	glBegin(GL_POLYGON);
		glVertex2i(x - width / 6, y + height - 2);
		glColor3f(0.23, 0.23, 0.23);
		glVertex2i(x + width / 2, round(y + height * 1.45)); // control roof tallness
		glVertex2i(x + width + width  / 6, y + height - 2);
		glColor3f(0, 0, 0);
	glEnd();
	glDisable(GL_POLYGON_STIPPLE);

	drawDoor(x, y, width, height);

	drawWindow(x, y, width, height);

	glFlush(); // Process all OpenGL routines as quickly as possible.
}

void drawShapes(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

	drawSky();
	drawLand();
	drawHome(65, 100, 80, 80);
	//drawHome(150, 20, 250, 250);

	glFlush(); // Process all OpenGL routines as quickly as possible.

	//glEnable(GL_TEXTURE_2D); // renable textures in case of resizing window
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // Initialize GLUT.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode.

	glutInitWindowPosition(200, 100); // Set top-left display-window position.

	glutInitWindowSize(1000, 1000); // Set display-window width and height.

	glutCreateWindow("Drawing a Neightborhood"); // Create display window.

	init(); // Execute initialization procedure.

	glutDisplayFunc(drawShapes); // Send graphics to display window.

	glutMainLoop(); // Display everything and wait.
}