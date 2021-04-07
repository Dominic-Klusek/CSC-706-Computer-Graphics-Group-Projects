// house.cpp
#include <windows.h>
#include <iostream>
#include <GL/glut.h>

void display() {
	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* future matrix manipulations should affect the modelview matrix */
	glMatrixMode(GL_MODELVIEW);

	/* draw scene */
	glPushMatrix();

	GLfloat light0_ambient[] = { 0.49, 0.55, 0.61, 1.0 };
	GLfloat light0_diffuse[] = { 0.25f, 0.25f, 0.25f, 1.0 };
	GLfloat light0_specular[] = { 0.8f, 0.8f, 0.8f, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	//glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glEnable(GL_LIGHT0);

	// door
	glPushMatrix();
	glColor3f(0.25, 0.21, 0.04);
	glTranslatef(-0.35, -0.35, 1.0);
	glScalef(3, 5, 0.25);
	glutSolidCube(0.25);
	glPopMatrix();

	// door handle
	glPushMatrix();
	glTranslatef(-0.10, -0.3, 1.1);
	glutSolidSphere(0.05, 128, 128);
	glPopMatrix();

	// house
	//GLfloat ambientLight[] = { 0.10588, 0.058824, 0.0113725};
	//GLfloat diffuseLight[] = { 0.427451, 0.470588, 0.541176 };
	//GLfloat specularLight[] = { 0.3333, 0.3333, 0.521569 };
	//glMaterialfv(GL_FRONT, GL_AMBIENT, ambientLight);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, ambientLight);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, ambientLight);

	glPushMatrix();
	glColor3f(0, 1, 0);
	glutSolidCube(2); // building
	glPopMatrix();

	// window
	glPushMatrix();
	glColor3f(0.8, 0.8, 0);
	glTranslatef(0.55, 0.35, 1.0);
	glScaled(3, 3, 0.25);
	glutSolidCube(0.25); // building
	glPopMatrix();

	// roof
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0,1.35,0);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(1.5, 1, 16, 8);
	glPopMatrix();

	// chimney
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslated(1, 2, -0.5);
	glScaled(1, 3, 1);
	glutSolidCube(.25);
	glPopMatrix();

	// car
	// body
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslated(1, 0, 2.25);
	glScaled(2, 1, 1);
	glutSolidCube(.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.45,-0.25,2.5);
	glScaled(1, 1, 1);
	glutSolidTorus(.05, .1, 8, 8); // wheel
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.55, -0.25, 2.5);
	glScaled(1, 1, 1);
	glutSolidTorus(.05, .1, 8, 8); // wheel
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.45, -0.25, 2);
	glScaled(1, 1, 1);
	glutSolidTorus(.05, .1, 8, 8); // wheel
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.55, -0.25, 2);
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
	/* initialize GLUT, using any commandline parameters passed to the program*/
	glutInit(&argc, argv);

	/* setup the size, position, and display mode for new windows */
	glutInitWindowSize(500, 500);
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
	glShadeModel(GL_FLAT); // GL_FLAT is a rough shading 
	
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