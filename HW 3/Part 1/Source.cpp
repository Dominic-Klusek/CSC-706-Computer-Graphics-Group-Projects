// house.cpp
//#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
using namespace std;

void createCylinder(float trunkRadius, float trunkHeight) {
	/* while looking for ideas I found a function to draw a tree
	* didn't use that function but modified his cylinder function
	* Source Link: http://www.mhzn.net/index.php/8-c-opengl/2-first-post
	*/
	// create quadratic object
	GLUquadric* obj = gluNewQuadric();

	// draw tree part
	glPushMatrix();

	glRotatef(-90, 1.0, 0.0, 0.0); // always necessary since cylinder is drawn along z-axis
	gluCylinder(obj, trunkRadius, trunkRadius/2.0, trunkHeight, 20, 20);
	glPopMatrix();
}

void createTree(float transX, float transZ) {
	/*
	* Function to create a tree
	* Made from simple solid Toruses, and a Cylinder
	*/
	// tree leaves
	float transY = 0.6; // have a variable to hold y translation
	float innerRadius = 0.14;
	float outerRadius = 0.28;
	glColor3f(0, 0.2, 0.0); // set color
	for (int i = 0; i < 7; i++) {
		glPushMatrix();
		glTranslatef(transX, transY, transZ);
		glRotatef(-90, 1, 0, 0);
		glutSolidTorus(innerRadius, outerRadius, 20, 20);
		glPopMatrix();

		transY = transY + 0.1;
		innerRadius = innerRadius / 1.2;
		outerRadius = outerRadius / 1.2;
	}

	// trunk
	glColor3f(0.2, 0.2, 0);
	glPushMatrix();
	glTranslatef(transX, 0, transZ);
	createCylinder(0.15, 0.7);
	glPopMatrix();
}

void createFlower() {
	/*
	* Function to create a flower
	* Stem is made from a cylinder
	* Leaves are rotated solid Toruses
	* the bulb is made from rotated teapots
	*/
	// create stem
	glPushMatrix();
	glColor3f(0, 0.3, 0.15);
	createCylinder(0.2, 2);
	glPopMatrix();

	// create leaves (stretched torus)
	float angle;
	for (int i = 0; i < 4; i++) {
		angle = rand() % 180 - 90;
		glPushMatrix();
		glRotatef(angle, 0, 0, 1);
		glRotatef(-45, 1, 1, 1);
		glScalef(0.5, 2, 0.5);
		glutSolidTorus(0.25, 0.3, 20, 20);
		glPopMatrix();
	}

	// create bulb
	glColor3f(1.00, 0.40, 0.84);
	angle = 0;
	for (int i = 0; i < 12; i++) {
		glPushMatrix();
		glTranslatef(0, 2.25, 0);
		glRotatef(35, 1, 0, 0);
		glRotatef(angle, 0, 1, 0);
		glutSolidTeapot(0.5);
		glPopMatrix();
		angle += 30;
	}

}

void display() {
	/////////// clear window ///////////
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/////////// future matrix manipulations should affect ///////////
	/////////// the modelview matrix ///////////
	glMatrixMode(GL_MODELVIEW);

	/////////// draw scene ///////////
	glPushMatrix();

	// Nightime Light Parameters
	/*GLfloat light0_ambient[] = { 0.25, 0.55, 0.85, 1.0 };
	GLfloat light0_diffuse[] = { 0.0f, 0.15f, 0.30f, 1.0 };
	GLfloat light0_specular[] = { 0.60f, 0.8f, 1.0f, 1.0 };
	GLfloat light0_position[] = { 0.8f, 0.8f, 0.5f, 1.0 };*/

	/////////// Light Parameters ///////////
	GLfloat light0_ambient[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat light0_diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0 };
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
	glTranslatef(0, -1.5, 0.0);
	glScalef(25, 0.25, 25);
	glutSolidCube(0.25);
	glPopMatrix();
		
	/////////// driveway ///////////
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0.8, -1.45, 1.7);
	glScalef(15, 0.25, 5);
	glutSolidCube(0.25);
	glPopMatrix();

	/////////// flowers ///////////
	float transX;
	float transZ;

	transX = 2.0;
	transZ = 0.75;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			glPushMatrix();
			glTranslatef(transX, 0, transZ);
			glScalef(0.1, 0.1, 0.1);
			createFlower();
			glPopMatrix();
			transZ += 0.3;
		}

		transZ = 0.75;
		transX += 0.3;
	}

	/////////// flower box ///////////
	glColor3f(0.20, 0.03, 0.00);
	glPushMatrix();
	glTranslatef(1.75, 0, 1.15);
	glRotatef(90, 0, 1, 0);
	glScalef(1.4, 0.1, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.4, 0, 0.50);
	glRotatef(180, 0, 1, 0);
	glScalef(1.4, 0.1, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(3.05, 0, 1.15);
	glRotatef(90, 0, 1, 0);
	glScalef(1.4, 0.1, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(2.40, 0, 1.85);
	glRotatef(180, 0, 1, 0);
	glScalef(1.4, 0.1, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();
	
	/////////// tree ///////////
	glPushMatrix();
	glScalef(1.2, 1.8, 1.2);
	createTree(2.0, -0.5);
	glPopMatrix();

	/////////// door ///////////
	glPushMatrix();
	glColor3f(0.66, 0.76, 0.83);
	glTranslatef(-0.35, -0.35, 1.0);
	glScalef(3, 5, 0.25);
	glutSolidCube(0.25);
	glPopMatrix();

	/////////// door handle ///////////
	glPushMatrix();
	glTranslatef(-0.10, -0.3, 1.1);
	glutSolidSphere(0.05, 128, 128);
	glPopMatrix();

	/////////// house ///////////
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(2); // building
	glPopMatrix();

	// window
	glPushMatrix();
	glColor3f(0.6, 0.8, 1);
	glTranslatef(0.55, 0.35, 0.97);
	glScaled(3, 3, 0.25);
	glutSolidCube(0.25); 
	glPopMatrix();

	// window supports
	glPushMatrix();
	glColor3f(0.15, 0.19, 0.0);
	glTranslatef(0.55, 0.35, 0.99);
	glRotatef(180, 0, 1, 0);
	glScalef(1.5, 0.1, 0.1);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.15, 0.19, 0.0);
	glTranslatef(0.55, 0.35, 0.99);
	glRotatef(90, 0, 0, 1);
	glRotatef(180, 0, 1, 0);
	glScalef(1.5, 0.1, 0.1);
	glutSolidCube(0.5);
	glPopMatrix();

	// roof
	glPushMatrix();
	glColor3f(0.56, 0.63, 0.7);
	glTranslated(0, 1.35, 0);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(1.5, 1, 16, 8);
	glPopMatrix();

	// chimney
	glPushMatrix();
	glColor3f(0.28, 0.32, 0.35);
	glTranslated(1, 2, -0.5);
	glScaled(1, 3, 1);
	glutSolidCube(.25);
	glPopMatrix();

	/////////// car ///////////
	// body
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslated(1, 0, 2.25);
	glScaled(2, 1, 1);
	glutSolidCube(.5);
	glPopMatrix();

	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(1.45,-0.25,2.55);
	glScaled(1, 1, 1);
	glutSolidTorus(.05, .1, 8, 8); // wheel
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.55, -0.25, 2.55);
	glScaled(1, 1, 1);
	glutSolidTorus(.05, .1, 8, 8); // wheel
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.45, -0.25, 1.95);
	glScaled(1, 1, 1);
	glutSolidTorus(.05, .1, 8, 8); // wheel
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.55, -0.25, 1.95);
	glScaled(1, 1, 1);
	glutSolidTorus(.05, .1, 8, 8); // wheel
	glPopMatrix();

	glPopMatrix();

	/* flush drawing routines to the window */
	glFlush();
}

void reshape(int width, int height) {
	/* define the viewport transformation */
	glViewport(0, 0, width, height);
}

int main(int argc, char* argv[]) {
	// seed rand function
	srand(time(NULL));

	/* initialize GLUT, using any commandline parameters passed to the program*/
	glutInit(&argc, argv);

	/* setup the size, position, and display mode for new windows */
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

	/* create and set up a window */
	glutCreateWindow("Hello, 3D House!");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	/* set up depth-buffering */
	glEnable(GL_DEPTH_TEST);

	/* turn on default lighting */
	glEnable(GL_LIGHTING);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);

	// Enable shading
	glShadeModel(GL_SMOOTH); // GL_FLAT is a rough shading 
	
	/* define the projection transformation */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, 1, 4, 20);

	/* define the viewing transformation */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	/* tell GLUT to wait for events */
	glutMainLoop();
	return 0;
}