// CSC 706 Project 1 Part 2
// Robert Kigobe, Dominic Klusek, Novichenko Konstantin

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "drawingFunctions.h"
using namespace std;

void display() {
	/////////// clear window ///////////
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/////////// future matrix manipulations should affect ///////////
	/////////// the modelview matrix ///////////
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	/////////// draw scene ///////////

	// Nightime Light Parameters
	/*GLfloat light0_ambient[] = { 0.25, 0.55, 0.85, 1.0 };
	GLfloat light0_diffuse[] = { 0.0f, 0.15f, 0.30f, 1.0 };
	GLfloat light0_specular[] = { 0.60f, 0.8f, 1.0f, 1.0 };
	GLfloat light0_position[] = { 0.8f, 0.8f, 0.5f, 1.0 };*/

	/////////// Light Parameters ///////////
	GLfloat light0_ambient[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat light0_diffuse[] = { 0.6f, 0.5f, 0.6f, 1.0 };
	GLfloat light0_specular[] = { 0.8f, 0.8f, 0.8f, 1.0 };
	GLfloat light0_position[] = { 0.8f, 0.8f, 0.5f, 1.0 };

	/////////// Set Light Parameters and enable light ///////////
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glEnable(GL_LIGHT0);

	/////////// set material ///////////
	GLfloat ambientLight[] = { 0.10588, 0.058824, 0.0113725 };
	GLfloat diffuseLight[] = { 0.427451, 0.470588, 0.541176 };
	GLfloat specularLight[] = { 0.3333, 0.3333, 0.521569 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientLight);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ambientLight);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ambientLight);

	/////////// ground ///////////
	glPushMatrix();
	glColor3f(0.13, 0.40, 0.00);
	glTranslatef(-1.5, -1.5, -1.5);
	glScalef(45, 0.25, 45);
	glutSolidCube(0.25);
	glPopMatrix();

	/////////// scenery ///////////
	// tree 1
	glPushMatrix();
	glTranslatef(-4.0, -1.5, 0.0);
	glScalef(2.0, 2.0, 2.0);
	createTree(0, 0);
	glPopMatrix();

	// tree 2
	glPushMatrix();
	glTranslatef(-2.5, -1.5, -4.0);
	glScalef(2.0, 2.0, 2.0);
	createTree(0, 0);
	glPopMatrix();

	// tree 3
	glPushMatrix();
	glTranslatef(-4.5, -1.5, -3.0);
	glScalef(2.0, 2.0, 2.0);
	createTree(0, 0);
	glPopMatrix();

	// sidewalk
	glPushMatrix();
	glTranslatef(0.0, -1.5, -6.5);
	glScalef(0.5, 1.0, 0.5);
	createSideWalk();
	glPopMatrix();

	// swingset 
	glPushMatrix();
	glTranslatef(2.0, 1.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	createSwingSet();
	glPopMatrix();

	// spinner
	glPushMatrix();
	glTranslatef(-3.0, -1.4, -2.5);
	glRotatef(spinnerRotationAngle, 0, 1, 0);
	glScalef(1.25, 1.25, 1.25);
	createSpinner();
	glPopMatrix();

	/////////// people ///////////
	// draw child on swingset
	glPushMatrix();
	glTranslatef(0.0, 1.0, 0.0);
	glRotatef(swingRotationAngle, 1, 0, 0);
	glTranslatef(2.0, -1.8, 0.0);
	glScalef(0.5, 0.5, 0.5);
	drawSwingingChildRobot();
	glPopMatrix();

	// draw clapping child
	glPushMatrix();
	glTranslatef(-1.0, -1.50, -1.0);
	glScalef(0.5, 0.5, 0.5);
	drawClappingChildRobot();
	glPopMatrix();

	// draw dancing adult
	glPushMatrix();
	glTranslatef(-1.0, -0.75, 1.0);
	glScalef(0.5, 0.5, 0.5);
	drawDancingRobot();
	glPopMatrix();

	glPopMatrix();

	/* flush drawing routines to the window */

	glFlush();
}

void timer(int val) {
	// cycle between the character  "dancing" up and down
	// of increase increment the offsets and angles
	// else decrease offsets amd amg;es
	if (increase) {
		rotationAngle += 2 * animationSpeedRatio;
		spinnerRotationAngle += 2 * animationSpeedRatio;
		bodyYOffset += (0.02 * animationSpeedRatio);
		footXOffset += (0.005 * animationSpeedRatio);
		legXOffset += (0.01 * animationSpeedRatio);
		legRotationAngle += (1.25 * animationSpeedRatio);
		if (bodyYOffset >= 0.2)
			increase = false;
	}
	else {
		rotationAngle += 2 * animationSpeedRatio;
		spinnerRotationAngle += 2 * animationSpeedRatio;
		bodyYOffset -= (0.02 * animationSpeedRatio);
		footXOffset -= (0.005 * animationSpeedRatio);
		legXOffset -= (0.01 * animationSpeedRatio);
		legRotationAngle -= (1.25 * animationSpeedRatio);
		if (bodyYOffset <= 0.0)
			increase = true;
	}

	if (swingIncrease) {
		swingRotationAngle += (2.5);
		swingLegRotationAngle += (3.5);
		if (swingRotationAngle >= 45.0)
			swingIncrease = false;
	}
	else {
		swingRotationAngle -= (2.5);
		swingLegRotationAngle -= (3.5);

		if (swingRotationAngle <= -45.0)
			swingIncrease = true;
	}

	if (clappingIncrease) {
		armsClappingRotation += (5.0);

		if (armsClappingRotation >= 115.0)
			clappingIncrease = false;
	}
	else {
		armsClappingRotation -= (5.0);

		if (armsClappingRotation <= 45.0)
			clappingIncrease = true;
	}

	// recall display function
	glutPostRedisplay();

	// call function again with delay
	if (spin)
		glutTimerFunc(40, timer, 0);
}

void mainMenu(int value) {
	switch (value) {
	default:
		exit(0);
		break;
	}
}

void animMenu(int value) {
	if (value == 1) {
		spin = true;
		glutTimerFunc(0, timer, 0);
	}
	else if (value == 2) {
		animationSpeedRatio += 0.25;
	}
	else if (value == 3) {
		animationSpeedRatio -= 0.25;
	}
	else if (value == 4) {
		spin = false;
	}
}

void rotationMenu(int value) {
	if (value == 1) {
		cameraRotation = true;
		glutTimerFunc(30, cameraRotationFunction, 0);
	}
	else if (value == 2) {
		cameraRotation = false;
	}
}

void shadeMenu(int value) {
	if (value == 1) {
		glShadeModel(GL_FLAT);
	}
	else if (value == 2) {
		glShadeModel(GL_SMOOTH);
	}

	// recall display function
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	// seed rand function
	srand(time(NULL));

	/* initialize GLUT, using any commandline parameters passed to the program*/
	glutInit(&argc, argv);

	/* setup the size, position, and display mode for new windows */
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

	/* create and set up a window */
	glutCreateWindow("Normal Day at the Park.");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	/* set up depth-buffering */
	glEnable(GL_DEPTH_TEST);

	/* turn on default lighting */
	glEnable(GL_LIGHTING);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);

	// Enable shading
	glShadeModel(GL_FLAT); // GL_FLAT is a rough shading 
	
	/* define the projection transformation */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, 1, 4, 20);

	/* define the viewing transformation */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glutTimerFunc(0, timer, 0);

	// create menu
	int baseMenu = glutCreateMenu(mainMenu);  // the base menu
	int animSubMenu = glutCreateMenu(animMenu); // submenu for drawing different figures
	int shadeSubMenu = glutCreateMenu(shadeMenu); // submenu for color submenus
	int rotationSubMenu = glutCreateMenu(rotationMenu); // the submenu for choosing the background polygon color(if applicable)

	// start menu
	glutSetMenu(baseMenu);

	// add animation sub menu
	glutAddSubMenu("Animation Menu", animSubMenu);
	glutSetMenu(animSubMenu);
	glutAddMenuEntry("Start Animation", 1);
	glutAddMenuEntry("Speed Up Animation", 2);
	glutAddMenuEntry("Slow Down Animation", 3);
	glutAddMenuEntry("Stop Animation", 4);
	glutSetMenu(baseMenu);

	// add shaing submenu
	glutAddSubMenu("Shading Menu", shadeSubMenu);
	glutSetMenu(shadeSubMenu);
	glutAddMenuEntry("Flat", 1);
	glutAddMenuEntry("Smooth", 2);
	glutSetMenu(baseMenu);

	// add camera rotation menu
	glutAddSubMenu("Rotation Menu", rotationSubMenu);
	glutSetMenu(rotationSubMenu);
	glutAddMenuEntry("Rotate On", 1);
	glutAddMenuEntry("Rotate Off", 2);
	glutSetMenu(baseMenu);

	// add final exit option
	glutAddMenuEntry("Exit", 6);

	// set button to open menu (in this case its the right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/* tell GLUT to wait for events */
	glutMainLoop();
	return 0;
}