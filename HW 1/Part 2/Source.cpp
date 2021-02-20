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
	srand(time(NULL));
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

void drawMountain(float mountainCenterX, float mountainCenterY) {
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
	srand(time(NULL));
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
		glColor3f(0.5, 0.5, 0.5);
		glVertex2f(windowX + windowWidth + sillOffset, windowY);
		glColor3f(0.0, 0.0, 0.0);
	glEnd();
}

void drawHome(float x, float y, float width, float height,
	float colorR = 0.95, float colorG = 0.95, float colorB = 0.95) {
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

	glEnable(GL_POLYGON_STIPPLE); // Enable POLYGON STIPPLE
	glColor3f(0.39, 0.39, 0.39);
	glPolygonStipple(frontHouse);
	glBegin(GL_POLYGON);
		glVertex2i(x, y);
		glVertex2i(x + width, y);
		//glColor3f(0.5, 0.5, 0.5);
		glVertex2i(x + width, y + height);
		glColor3f(colorR, colorG, colorB);
		glVertex2i(x, y + height);
		glVertex2i(x, y);
	glEnd();
	glDisable(GL_POLYGON_STIPPLE);

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


void drawLeaves(float x, float y, float radius = 5) {
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
	float modX = (endX - beginX) / numVertices;
	float modY = (endY - beginY) / numVertices;

	if (modX > modY) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i < numVertices; i++) {
			//cout << "Next Coodinates: " << "(" << beginX + modX * i << ", " << beginY + modY * i << ")" << endl;

			if (i % 2 == 0) {
				glColor3f(0.34, 0.22, 0.0);
				glVertex2f(beginX + modX * i, beginY + modY * i + rand() % thickness + thickness / 2);
			}
			else {
				glColor3f(0.45, 0.30, 0.0);
				glVertex2f(beginX + modX * i, beginY + modY * i + rand() % thickness - thickness / 2);
			}
		}
		glEnd();
	}
	else {
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i < numVertices; i++) {
			//cout << "Next Coodinates: " << "(" << beginX + modX * i << ", " << beginY + modY * i << ")" << endl;

			if (i % 2 == 0) {
				glColor3f(0.34, 0.22, 0.0);
				glVertex2f(beginX + modX * i + rand() % thickness + thickness / 2, beginY + modY * i);
			}
			else {
				glColor3f(0.45, 0.30, 0.0);
				glVertex2f(beginX + modX * i + rand() % thickness - thickness / 2, beginY + modY * i);
			}
		}
		glEnd();
	}
}

void drawTree(float x, float y, float width, float height, float branchThickness = 10,  int numVertices = 20) {
	int trunkModX = round(width / 5.0);
	int trunkModX2 = round(width / 30.0);
	float trunkModY = height / numVertices;
	// draw trunk

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
	int leavesY = y + height / 2;
	int leavesModX = width / 2;
	int leavesModY = height / 4;
	int radiusMod = width / 5;
	float leafCenterX, leafCenterY;

	//generate coords
	leafCenterX = x - rand() % leavesModX;
	leafCenterY = leavesY + rand() % leavesModY * 2 + leavesModY;

	// draw leaves, and branch
	drawLeaves(leafCenterX, leafCenterY, rand() % radiusMod + radiusMod);
	drawBranch(x + width / 8, y + trunkModY * numVertices / 2, leafCenterX, leafCenterY, branchThickness);

	//generate coords
	leafCenterX = x - rand() % leavesModX;
	leafCenterY = leavesY + rand() % leavesModY * 2 + leavesModY;

	// draw leaves, and branch
	drawLeaves(leafCenterX, leafCenterY, rand() % radiusMod + radiusMod);
	drawBranch(x + width / 8, y + trunkModY * numVertices / 2, leafCenterX, leafCenterY, branchThickness);

	//generate coords
	leafCenterX = x + rand() % leavesModX;
	leafCenterY = leavesY + rand() % leavesModY * 2 + leavesModY;
	
	// draw leaves, and branch
	drawLeaves(leafCenterX, leafCenterY, rand() % radiusMod + radiusMod);
	drawBranch(x + width / 8, y + trunkModY * numVertices / 2, leafCenterX, leafCenterY, branchThickness);

	//generate coords
	leafCenterX = x + rand() % leavesModX;
	leafCenterY = leavesY + rand() % leavesModY * 2 + leavesModY;

	// draw leaves, and branch
	drawLeaves(leafCenterX, leafCenterY, rand() % radiusMod + radiusMod);
	drawBranch(x + width / 8, y + trunkModY * numVertices / 2, leafCenterX, leafCenterY, branchThickness);

}

void drawShapes(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

	//drawSky();
	//drawLand();
	//drawHome(65, 100, 80, 80);
	//drawHome(150, 20, 250, 250);
	drawTree(100, 250, 120, 150, 10, 25);
	drawTree(150, 250, 80, 120, 8, 25);
	drawTree(200, 250, 200, 250, 15, 50);

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