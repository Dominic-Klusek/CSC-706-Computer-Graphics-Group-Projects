// CSC 706 HW 2 Part 2
// Robert Kigobe, Dominic Klusek, Novichenko Konstantin
#define _USE_MATH_DEFINES
#include <GL/glut.h> // (or others, depending on the system in use)
#include <cmath>

// Constants
const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 600;
const int WINDOW_X_OFFSET = 100;
const int WINDOW_Y_OFFSET = 100;

// Initiate
void init(void)
{
	glClearColor(0.8, 0.8, 0.8, 0.0); // Set display-window color to light gray
	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	gluOrtho2D(0.0, WINDOW_HEIGHT, 0.0, WINDOW_WIDTH);
}

// Draw a circle or part of the circle
void drawCircle(int originX, int originY, int start, int end, int radius)
{
	glBegin(GL_POLYGON);
	glVertex2d(originX, originY);
	for (double i = start; i <= end; i++)
	{
		glVertex2d(originX + cos((i * M_PI) / 180) * radius, originY + sin((i * M_PI) / 180) * radius);
	}
	glEnd();
}
// Render Yin Yang centered in the screen
void drawYinYang(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.	

	// *******************Black half circle (upper half)*******************	
	glColor3f(0.0, 0.0, 0.0); // Set color	
	// Center in the middle of the screen usign window height and width divided by half as a coordinates
	double centerX = WINDOW_HEIGHT / 2, centerY = WINDOW_WIDTH / 2;
	// Set radius to a third size of the screen
	double	radius = WINDOW_WIDTH / 3;
	// Render upper half circle (0 to 180 degrees)
	drawCircle(centerX, centerY, 0, 180, radius);

	// *******************White half circle (lower half)*******************
	glColor3f(1.0, 1.0, 1.0); // Set color
	// Render lower half circle (180 to 360 degrees)
	drawCircle(centerX, centerY, 180, 360, radius);

	// *******************Black circle on the left side with the radius half of the original radius*******************
	glColor3f(0.0, 0.0, 0.0); // Set color	
	int radius_m = radius / 2; // Set the radius to be a half of the original radius
	centerX = (double)(WINDOW_WIDTH / 2) - radius_m; // Shift the origin to	the left
	// Render left medium circle
	drawCircle(centerX, centerY, 0, 360, radius_m);

	// *******************White circle on the right side with the radius half of the original radius*******************	
	glColor3f(1.0, 1.0, 1.0); // Set color
	centerX = (double)(WINDOW_WIDTH / 2) + radius_m; // shift the origin to	the right	
	// Render right medium circle
	drawCircle(centerX, centerY, 0, 360, radius_m);

	// *******************Black small circle on the right side with the radius 1/8 of the original radius*******************
	glColor3f(0.0, 0.0, 0.0); // Set color
	int radius_s = radius / 8;
	// Render right small circle
	drawCircle(centerX, centerY, 0, 360, radius_s);

	// *******************White small circle on the left side with the radius 1/8 of the original radius*******************
	glColor3f(1.0, 1.0, 1.0); // Set color
	centerX = (double)(WINDOW_WIDTH / 2) - radius_m; // shift the origin to	the left
	// Render left small circle
	drawCircle(centerX, centerY, 0, 360, radius_s);

	glFlush(); // Process all OpenGL routines as quickly as possible.
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // Initialize GLUT.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode.

	glutInitWindowPosition(WINDOW_X_OFFSET, WINDOW_Y_OFFSET); // Set top-left display-window position.

	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Set display-window width and height.

	glutCreateWindow("Drawing Yin Yang using polygons"); // Create display window.

	init(); // Execute initialization procedure.

	glutDisplayFunc(drawYinYang); // Send graphics to display window.

	glutMainLoop(); // Display everything and wait.
}