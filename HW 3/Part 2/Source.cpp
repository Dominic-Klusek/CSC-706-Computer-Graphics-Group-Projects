// CSC 706 HW 3 Part 2
// Robert Kigobe, Dominic Klusek, Novichenko Konstantin
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <Windows.h>

#define W 600
#define H 600

float rotationAngle = 5.0;

void setLights(void) {
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
}

/*
void setLights(void) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_POLYGON_SMOOTH);

	float spotExponent = 1.0;
	float spotCutoff = 90;

	// bottom right light
	GLfloat light1_ambient[] = { 0.40, 0.0, 0.33, 1.0 };
	GLfloat light1_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0 };
	//GLfloat light1_diffuse[] = { 0.40, 0.0, 0.33, 1.0 };
	GLfloat light1_specular[] = { 0.8f, 0.8f, 0.8f, 1.0 };
	GLfloat light1_position[] = { 500.0, -550.0, 500.0f, 1.0 };
	GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent);

	glEnable(GL_LIGHT1);

	// top right light
	GLfloat light2_ambient[] = { 0.9, 0.9, 0.0, 1.0 };
	GLfloat light2_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0 };
	//GLfloat light2_diffuse[] = { 0.9, 0.9, 0.0, 1.0 };
	GLfloat light2_specular[] = { 0.8f, 0.8f, 0.8f, 1.0 };
	GLfloat light2_position[] = { 500.0, 550.0, 500.0f, 1.0 };

	glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutoff);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent);

	glEnable(GL_LIGHT2);

	// top left light
	GLfloat light3_ambient[] = { 0.40, 1.00, 0.70, 1.0 };
	GLfloat light3_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0 };
	//GLfloat light3_diffuse[] = { 0.40, 1.00, 0.70, 1.0 };
	GLfloat light3_specular[] = { 0.8f, 0.8f, 0.8f, 1.0 };
	GLfloat light3_position[] = { -500.0, 550.0, 500.0f, 1.0 };

	glLightfv(GL_LIGHT3, GL_AMBIENT, light3_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light3_specular);
	glLightfv(GL_LIGHT3, GL_POSITION, light3_position);

	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, spotCutoff);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, spotExponent);

	glEnable(GL_LIGHT3);

	// bottom left light
	GLfloat light4_ambient[] = { 0.00, 0.1, 0.6, 1.0 };
	GLfloat light4_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0 };
	//GLfloat light4_diffuse[] = { 0.00, 0.1, 0.6, 1.0 };
	GLfloat light4_specular[] = { 0.8f, 0.8f, 0.8f, 1.0 };
	GLfloat light4_position[] = { -500.0, -550.0, 500.0f, 1.0 };

	glLightfv(GL_LIGHT4, GL_AMBIENT, light4_ambient);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, light4_diffuse);
	glLightfv(GL_LIGHT4, GL_SPECULAR, light4_specular);
	glLightfv(GL_LIGHT4, GL_POSITION, light4_position);

	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, spotCutoff);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, spotExponent);

	glEnable(GL_LIGHT4);
}
*/

void displaySolid(void)
{
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glOrtho(-W, W, -H, H, -W, W);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(0, 0, 10, 0, 0, 0, 0.0, 1.0, 0.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set up teapot materials
	GLfloat mat_ambient[] = { 0.4f, 0.4f, 0.6f, 1.0f };
	GLfloat mat_diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 150.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


	// draw all teapots and arrange them in a grid
	int teapotSize = 40;
	int x = -W + teapotSize * 2;
	int y = -H + teapotSize;
	
	float R = 0;
	float G = 0; 
	float B = 1.0;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			// change color accordinagly
			R = R + j * 0.12;
			G = G + i * 0.12;
			B = B - (i + j) / 2 * 0.12;
			glColor3f(R, G, B);

			glPushMatrix();
			glTranslatef(x, y, 0);
			glRotatef(rotationAngle, 0, 1, 0);
			glutSolidTeapot(teapotSize);
			glPopMatrix();

			// change x position
			x += teapotSize * 3.75;

			// reset RGB color
			R = 0;
			G = 0;
			B = 1.0;
		}

		// change y position, and reset x position
		x = -W + teapotSize * 2;
		y += teapotSize * 3.95;
	}

	// flush and swap buffers
	glutSwapBuffers();
}

bool spin = 0;
void timer(int val) {
	// increment rotation angle
	rotationAngle += 5;

	// call function again with delay
	if(spin)
		glutTimerFunc(16, timer, 0);

	// recall display function
	glutPostRedisplay();
}


void mainMenu(int value) {
	switch (value) {
	case 1:
		spin = 1;
		glutTimerFunc(0, timer, 0);
		break;
	case 2:
		spin = 0;
		break;
	default:
		exit(0);
		break;
	}
}

int main(int argc, char** argv)
{
	// initialize GLUT
	glutInit(&argc, argv);

	// set up display mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// intitialize window size
	glutInitWindowSize(1000, 1000);

	// set window position
	glutInitWindowPosition(100, 100);

	// create window
	glutCreateWindow("My Teapot");

	// set up spotlights
	setLights();

	// call display function
	glutDisplayFunc(displaySolid);

	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

	// create menu
	int baseMenu = glutCreateMenu(mainMenu);  // the base menu

	glutSetMenu(baseMenu);

	// add final exit option
	glutAddMenuEntry("Spin Teapots", 1);
	glutAddMenuEntry("Stop Teapots", 2);

	// set button to open menu (in this case its the right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glViewport(0, 0, W, H);

	glutMainLoop();
	return 1;
}