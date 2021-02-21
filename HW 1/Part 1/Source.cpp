#include "masks.h"
#include <GL/glut.h> // (or others, depending on the system in use)

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // Set display-window color to white.
	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	gluOrtho2D(0.0, 200.0, 0.0, 250.0);
}

void drawRectangle(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.


	// Part a) At least 2 geometric figures filled with solid colors
	// figure 1 Rectangle 
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_QUADS);
		// define vertices
		glVertex2i(20, 20);
		glVertex2i(20, 60);
		glVertex2i(60, 60);
		glVertex2i(60, 20);
	glEnd();

	// figure 2 Triangle
	glColor3f(0.5, 0.5, 1.0);
	glBegin(GL_TRIANGLES);
		// define vertices
		glVertex2i(100, 30);
		glVertex2i(130, 80);
		glVertex2i(160, 30);
	glEnd();

	// Part b) At least 2 more filled with more than one color (color interpolation)

	// figure 1 Triangle Strip
	// initial color
	glColor3f(0.5, 0.2, 0.5);
	glBegin(GL_TRIANGLE_STRIP);
		// define vertices
		glVertex2i(30, 80);
		glVertex2i(50, 100);
		// change color
		glColor3f(0.1, 0.2, 0.5);
		glVertex2i(70, 65);
		// change color back
		glColor3f(0.5, 0.2, 0.5);
		glVertex2i(90, 110);
		glVertex2i(110, 55);
	glEnd();

	// figure 2 Circle using Polygon
	// initial color
	glColor3f(0.55, 0.55, 0.58);
	glBegin(GL_POLYGON);
		double centerX = 120, centerY = 120, radius = 20;
		glVertex2d(centerX, centerY);
		glColor3f(0.0, 0.0, 0.0);
		for (double i = 0; i <= 360; i++)
		{
			glVertex2d(centerX + cos((i * pi) / 180) * radius, centerY + sin((i * pi) / 180) * radius);
		}
	glEnd();

	// Part c) At least 3 more filled with given masks
	// Figure 1 Half Circle using Polygon w/ stipple
	// create background to visualize mask better
	glColor3f(0.30, 0.00, 0.9);
	glBegin(GL_POLYGON);
	centerX = 180, centerY = 180, radius = 15;
		glVertex2d(centerX, centerY);
		for (double i = 0; i <= 270; i++)
		{
			glVertex2d(centerX + cos((i * pi) / 180) * radius, centerY + sin((i * pi) / 180) * radius);
		}
	glEnd();

	// place mask pattern
	glColor3f(0.98, 0.69, 1.00);
	glEnable(GL_POLYGON_STIPPLE); // Enable POLYGON STIPPLE
	glPolygonStipple(street);
	glBegin(GL_POLYGON);
		centerX = 180, centerY = 180, radius = 15;
		glVertex2d(centerX, centerY);
		for (double i = 0; i <= 270; i++)
		{
			glVertex2d(centerX + cos((i * pi) / 180) * radius, centerY + sin((i * pi) / 180) * radius);
		}
	glEnd();
	glDisable(GL_POLYGON_STIPPLE);

	// Figure 2 Triangle Fan w/ stipple
	// create background to visualize mask better
	glColor3f(1.00, 1.00, 0.50);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2i(75, 75);
		glVertex2i(65, 65);
		glVertex2i(55, 65);
		glVertex2i(45, 75);
		glVertex2i(55, 85);
		glVertex2i(65, 85);
	glEnd();

	// place mask pattern
	glColor3f(0.20, 0.66, 0.28);
	glEnable(GL_POLYGON_STIPPLE); // Enable POLYGON STIPPLE
	glPolygonStipple(frontHouse);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2i(75, 75);
		glVertex2i(65, 65);
		glVertex2i(55, 65);
		glVertex2i(45, 75);
		glVertex2i(55, 85);
		glVertex2i(65, 85);
	glEnd();
	glDisable(GL_POLYGON_STIPPLE);

	// Figure 3 Rotated Rectangle w/ stipple
	// create background to visualize mask better
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
		glVertex2i(20, 150);
		glVertex2i(50, 180);
		glVertex2i(80, 150);
		glVertex2i(50, 120);
	glEnd();
	//ce mask pattern
	glColor3f(0.66, 0.31, 0.13);
	glEnable(GL_POLYGON_STIPPLE); // Enable POLYGON STIPPLE
	glPolygonStipple(grassMask);
	glBegin(GL_QUADS);
		glVertex2i(20, 150);
		glVertex2i(50, 180);
		glVertex2i(80, 150);
		glVertex2i(50, 120);
	glEnd();
	glDisable(GL_POLYGON_STIPPLE);

	glFlush(); // Process all OpenGL routines as quickly as possible.

}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // Initialize GLUT.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode.

	glutInitWindowPosition(50, 100); // Set top-left display-window position.

	glutInitWindowSize(400, 300); // Set display-window width and height.

	glutCreateWindow("An Example OpenGL Program"); // Create display window.

	init(); // Execute initialization procedure.

	glutDisplayFunc(drawRectangle); // Send graphics to display window.

	glutMainLoop(); // Display everything and wait.
}