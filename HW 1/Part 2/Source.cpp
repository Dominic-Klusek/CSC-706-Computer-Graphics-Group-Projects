#include "masks.h"
#include <GL/glut.h>
#include<iostream>
using namespace std;

// glocal variables
double windowHeight;
double windowWidth;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // Set display-window color to white.
	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	gluOrtho2D(0.0, 800, 0.0, 800);
	windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	srand(time(NULL));
}

void drawMountain(float mountainCenterX, float mountainCenterY) {
	// draw randomly created mountains
	/* Mountains are randomly created by using a triangle fan with randomly
	offset x and y coordinate; also chang the color to create a more dynamic look
	
	Mountains are made more dynamic by creating 1 light set of mountains and 1 darker
	set of mountains; again with color change to make it more dynamic.

	Mountains are modeled somewhat on a bell curve; taller in the middle, 
	then getting shorter further away from the middle
	*/
	glColor3f(0.19, 0.19, 0.19);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(mountainCenterX, mountainCenterY);
	glVertex2f(mountainCenterX + 100, mountainCenterY + (rand() % 25 + 10));
	glVertex2f(mountainCenterX + 75, mountainCenterY + (rand() % 75 + 20));
	glColor3f(0.66, 0.66, 0.66);
	glVertex2f(mountainCenterX + 25, mountainCenterY + (rand() % 100 + 35));
	glVertex2f(mountainCenterX, mountainCenterY + rand() % 100 + 40);
	glColor3f(0.19, 0.19, 0.19);
	glVertex2f(mountainCenterX - 25, mountainCenterY + (rand() % 100 + 35));
	glVertex2f(mountainCenterX - 75, mountainCenterY + (rand() % 75 + 20));
	glVertex2f(mountainCenterX - 100, mountainCenterY + (rand() % 25 + 10));
	glEnd();

	glColor3f(0.36, 0.36, 0.36);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(mountainCenterX, mountainCenterY);
	glVertex2f(mountainCenterX + 100, mountainCenterY + (rand() % 25 + 10));
	glVertex2f(mountainCenterX + 75, mountainCenterY + (rand() % 75 + 20));
	glColor3f(0.69, 0.69, 0.69);
	glVertex2f(mountainCenterX + 25, mountainCenterY + (rand() % 100 + 35));
	glVertex2f(mountainCenterX, mountainCenterY + rand() % 100 + 40);
	glColor3f(0.36, 0.36, 0.36);
	glVertex2f(mountainCenterX - 25, mountainCenterY + (rand() % 100 + 35));
	glVertex2f(mountainCenterX - 75, mountainCenterY + (rand() % 75 + 20));
	glVertex2f(mountainCenterX - 100, mountainCenterY + (rand() % 25 + 10));
	glEnd();
}

void drawLand() {
	// build random mountain from outer edges in;
	// that way the mountain in the middle can cover the outer mountains spaces and rougher edges

	// outer most
	drawMountain(750, 310);
	drawMountain(50, 265);

	// level 1 mountains
	drawMountain(680, 275);
	drawMountain(130, 235);

	// level 2 mountains
	drawMountain(550, 215);
	drawMountain(250, 215);

	// level 3 mountains
	drawMountain(450, 200);
	drawMountain(350, 180);

	// draw grass
	glColor3f(0.08, 0.50, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(0, windowHeight / 3.0);
		glColor3f(0.33, 1.00, 0.0);
		glVertex2f(windowWidth / 2.0, windowHeight / 6.0);
		glColor3f(0.08, 0.50, 0.0);
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
		glColor3f(0.20, 0.17, 0.0);
		glVertex2f(windowWidth / 2.0, windowHeight / 16.0);
		glVertex2f(windowWidth, windowHeight / 8.0);
		glColor3f(0.40, 0.20, 0.0);
		glVertex2f(windowWidth, 0);
	glEnd();

	// draw road
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(0, 50);
		glVertex2f(0, 0);
		glVertex2f(225, 0);
		glVertex2f(190, 101);
		glVertex2f(25, 122);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(340, 82);
		glVertex2f(300, 150);
		glVertex2f(220, 110);
		glVertex2f(230, 95);
	glEnd();

	// draw road markings
	glColor3f(0.9, 0.9, 0.0);
	glBegin(GL_QUADS);
		glVertex2f(102, 15);
		glVertex2f(118, 13);
		glVertex2f(117, 99);
		glVertex2f(102, 101);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex2f(295, 86);
		glVertex2f(277, 120);
		glVertex2f(270, 115);
		glVertex2f(285, 88);
	glEnd();
}

void drawSun(float sunCenterX = 400.0, float sunCenterY = 400.0, float sunRadius = 50.0) {
	// Sun is just a circle of a certain color
	glColor3f(0.90, 0.90, 0.0);
	drawACircleWith(sunCenterX, sunCenterY, 0, 360, sunRadius, sunRadius, GL_POLYGON);
}

void drawSky() {
	// cariables to define, and modify sun
	float sunCenterX = 800.0;
	float sunCenterY = 800.0;
	float sunRadius = 50.0;

	// the sky is just a blue polygon, with a yellow corner
	glColor3f(0.50, 0.83, 1.00);
	glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(windowWidth, 0);
		glColor3f(1.0, 0.85, 0.10);
		glVertex2f(windowWidth, windowHeight);
		glColor3f(0.50, 0.83, 1.00);
		glVertex2f(0, windowHeight);
	glEnd();

	// call drawSun function to draw sun over the sky.
	drawSun(sunCenterX, sunCenterY, sunRadius);

	glFlush();
}

void drawDoor(float x, float y, float width, float height) {
	// door parameters
	float doorX = round(x + width / 3);
	float doorY = round(y + height / 1.5);

	// draw door
	glColor3f(0.60, 0.30, 0.0);
	glBegin(GL_POLYGON);
		glVertex2f(doorX, y);
		glColor3f(0.29, 0.19, 0.0);
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
		// add light 
		glColor3f(0.5, 0.5, 0.5);
		glVertex2f(windowX + windowWidth + sillOffset, windowY);
		glColor3f(0.0, 0.0, 0.0);
	glEnd();
}

void drawHome(float x, float y, float width, float height) {
	// draw house main body background
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
		glVertex2i(x, y);
		glVertex2i(x + width, y);
		glVertex2i(x + width, y + height);
		glVertex2i(x, y + height);
		glVertex2i(x, y);
	glEnd();

	// draw house siding
	glEnable(GL_POLYGON_STIPPLE); // Enable POLYGON STIPPLE
	glColor3f(0.30, 0, 0);
	glPolygonStipple(brick);
	glBegin(GL_POLYGON);
		glVertex2i(x, y);
		glVertex2i(x + width, y);
		glColor3f(0.10, 0.0, 0.0);
		glVertex2i(x + width, y + height);
		glColor3f(0.30, 0, 0);
		glVertex2i(x, y + height);
		glVertex2i(x, y);
	glEnd();
	glDisable(GL_POLYGON_STIPPLE);

	// add outline to main house body
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
		glVertex2i(x, y);
		glVertex2i(x + width, y);
		glVertex2i(x + width, y + height);
		glVertex2i(x, y + height);
		glVertex2i(x, y);
	glEnd();

	// draw house roof background
	// constant are to account for some space between roof and house main body, as well as to extend the roof past the walls of the house
	glBegin(GL_POLYGON);
		glVertex2i(x - width / 6, y + height - 2);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2i(x + width / 2, round(y + height * 1.45)); // control roof tallness
		glVertex2i(x + width + width / 6, y + height - 2);
		glColor3f(0, 0, 0);
	glEnd();

	// draw roof lines
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

	// call function to draw door
	drawDoor(x, y, width, height);

	// call function to draw window.
	drawWindow(x, y, width, height);

	glFlush(); // Process all OpenGL routines as quickly as possible.
}

void drawLeaves(float x, float y, float radius = 5) {
	// leaves are a polygonal circle with random offsets to the edges
	int intRadius = radius / 2;
	glColor3f(0.15, 0.30, 0.0);
	glBegin(GL_POLYGON);
		glVertex2d(x, y);
		glColor3f(0.24, 0.48, 0.0);
		for (double i = 0; i <= 360; i++)
		{
			glVertex2d(x + cos((i * pi) / 180) * radius + (rand() % int(intRadius * 2)) - intRadius, y + sin((i * pi) / 180) * radius + (rand() % int(intRadius * 2)) - intRadius);
		}
	glEnd();
}

void drawBranch(float beginX, float beginY, float endX, float endY, int thickness, int numVertices = 25) {
	// bramnches are drawn from beginning x and y coordinates
	// calculate slope from beginning coordinates to the center of the leave ball
	float modX = (endX - beginX) / numVertices;
	float modY = (endY - beginY) / numVertices;

	// to keep the thickness consisten; check which direction will the offset make more sense(x or y)
	// also to make the branch seem more "realistic", change the color on each odd and even vertex
	if (abs(modX) > abs(modY)) {
		// if modX is larger than modY; the x slope is more extreme, so easier make thickness in the y direction
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i < numVertices; i++) {

			if (i % 2 == 0) {
				glColor3f(0.34, 0.22, 0.0);
				glVertex2f(beginX + modX * i, beginY + modY * i + rand() % thickness + thickness / 1.1);
			}
			else {
				glColor3f(0.45, 0.30, 0.0);
				glVertex2f(beginX + modX * i, beginY + modY * i + rand() % thickness - thickness / 1.1);
			}
		}
		glEnd();
	}
	else {
		// else, easier make thickness in the x direction
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i < numVertices; i++) {

			if (i % 2 == 0) {
				glColor3f(0.34, 0.22, 0.0);
				glVertex2f(beginX + modX * i + rand() % thickness + thickness / 1.1, beginY + modY * i);
			}
			else {
				glColor3f(0.45, 0.30, 0.0);
				glVertex2f(beginX + modX * i + rand() % thickness - thickness / 1.1, beginY + modY * i);
			}
		}
		glEnd();
	}
}

void drawTree(float x, float y, float width, float height, float branchThickness = 10,  int numLeaves = 6, int numVertices = 20) {
	// some constant to help with drawing the tree
	int trunkModX = round(width / 5.0);
	int trunkModX2 = round(width / 30.0);
	float trunkModY = height / numVertices;

	// draw trunktrunk is a triangle strip with random offsets in the x direction to make the trunk more dynamic
	// the triangle strip has a number of vertices equal to numVertices
	// on each odd and even vertex, the color is changed to give a more realistic color
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < numVertices; i++) {
		if (i % 2 == 0) {
			glColor3f(0.34, 0.22, 0.0);
			glVertex2f(x + (rand() % trunkModX2), y + trunkModY * i);
		}
		else {
			glColor3f(0.45, 0.30, 0.0);
			glVertex2f(x + trunkModX + (rand() % trunkModX2), y + trunkModY * i);
		}
	}
	glEnd();


	// draw leaves
	// some constants
	int leavesY = y + height / 3 * 2;
	int leavesModX = width / 2;
	int leavesModY = height / 4;
	int radiusMod = width / 4;
	float leafCenterX, leafCenterY;
	if (leavesModX < 1)
		leavesModX = 1;

	// each tree has 4 sets of leaves, which are randomly placed, and have branches going toward them
	// 2 sets are skewed to the right, and 2 to the left

	for (int i = 0; i < numLeaves / 2; i++) {
		//generate coords
		leafCenterX = x - rand() % (int(width) * 2) + width;
		leafCenterY = leavesY + rand() % leavesModY * 2 + leavesModY;

		// draw leaves, and branch
		drawLeaves(leafCenterX, leafCenterY, rand() % radiusMod * 2 + radiusMod);
		drawBranch(x + width / 8, y + trunkModY * numVertices, leafCenterX, leafCenterY, branchThickness);
	}

	for (int i = 0; i < numLeaves / 2; i++) {
		//generate coords
		leafCenterX = x + rand() % int(width) + width / 2;
		leafCenterY = leavesY + rand() % leavesModY * 2 + leavesModY;

		// draw leaves, and branch
		drawLeaves(leafCenterX, leafCenterY, rand() % radiusMod * 2 + radiusMod);
		drawBranch(x + width / 8, y + trunkModY * numVertices, leafCenterX, leafCenterY, branchThickness);
	}
}

void drawShapes(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

	// call functions to draw main objects of scene
	// Objects drawn in the order Sky -> Ground -> Houses and Trees
	drawSky();
	drawLand();
	drawHome(400, 20, 250, 250);
	drawTree(700, 20, 120, 360, 5, 12);


	drawHome(65, 220, 25, 25);
	drawTree(100, 220, 20, 45, 1, 24);

	drawHome(135, 165, 35, 35);
	drawTree(170, 165, 25, 50, 1, 24);

	glFlush(); // Process all OpenGL routines as quickly as possible.
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