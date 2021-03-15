#include "masks.h"
#include <fstream>
#include <iostream>
#include <GL/glut.h> // (or others, depending on the system in use)
using namespace std;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // Set display-window color to white.
	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	gluOrtho2D(0.0, 200.0, 0.0, 250.0);
}

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
			glVertex2i(x, y);
		}
		glEnd();
	}
	glFlush();
	inStream.close();
}

void drawShapes(void)
{
	// basic idea of problem 1
	// 1. Define a glViewport
	// 2. Draw dinosaur using drawPolyLineFile
	// 3. Perform transformations
	// 4. Do it again
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
	
	glColor3f(0.5, 0.5, 0.5); // set color
	
	// make a loop that goes around in a circle
	int originX = 100;
	int originY = 100;
	float radius = 75.0;
	char data[] = "brontoi.dat"; // define polyline file
	glScaled(0.15, 0.15, 0); // scale drawing
	for (int i = 0; i < 360; i += 45) {
		cout << originX + cos((i * pi) / 180)<< ", " << originY + sin((i * pi) / 180) << endl;
		glViewport(originX + cos((i * pi) / 180) * radius, originY + sin((i * pi) / 180) * radius, 100, 100); // set viewPort
		drawPolyLineFile(data);
	}
	/*
	glViewport(50, 50, 100, 100); // set viewPort

	glTranslated(40, 40, 0); // need to translate to fit drawing when rotated
	glRotated(45, 0, 0, 1); // rotate
	glScaled(0.15, 0.15, 0); // scale drawing
	drawPolyLineFile(data); // draw the dinosaur*/
	glFlush(); // Process all OpenGL routines as quickly as possible.
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // Initialize GLUT.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode.

	glutInitWindowPosition(50, 100); // Set top-left display-window position.

	glutInitWindowSize(400, 300); // Set display-window width and height.

	glutCreateWindow("CHANGE ME TO APPROPRIATE TITLE"); // Create display window.

	init(); // Execute initialization procedure.

	glutDisplayFunc(drawShapes); // Send graphics to display window.

	glutMainLoop(); // Display everything and wait.
}