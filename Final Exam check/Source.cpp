#include "masks.h"
#include <GL/glut.h> // (or others, depending on the system in use)


void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // Set display-window color to white.
	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	gluOrtho2D(-5.0, 10.0, -5.0, 10.0);
}

void drawShapes(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
	
	glPointSize(5.0);
	glColor3f(0,0,0);

	glPushMatrix();
	glPushMatrix();

	glPushMatrix();
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2, 1111000011110000);
	glBegin(GL_LINES);
	glVertex2f(0, -2.0);
	glVertex2f(0, 10.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(10.0, 0);
	glEnd();
	glPopMatrix();

	glDisable(GL_LINE_STIPPLE);

	glPushMatrix();
	
	glTranslatef(3, -3, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0, 3.0);
	glVertex2f(0.0, 5.0);
	glVertex2f(-3.0, 3.0);
	glEnd();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	glFlush(); // Process all OpenGL routines as quickly as possible.

}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // Initialize GLUT.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode.

	glutInitWindowPosition(50, 100); // Set top-left display-window position.

	glutInitWindowSize(400, 300); // Set display-window width and height.

	glutCreateWindow("Creatively Drawing Polygons"); // Create display window.

	init(); // Execute initialization procedure.

	glutDisplayFunc(drawShapes); // Send graphics to display window.

	glutMainLoop(); // Display everything and wait.
}