#pragma once
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

#define PI 3.14159

void drawSphere()
{
	glutSolidSphere(.1, 16, 16);
}

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
	gluCylinder(obj, trunkRadius, trunkRadius, trunkHeight, 20, 20);
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
	createCylinder(0.08, 0.7);
	glPopMatrix();
}

void createBush(float transX, float transZ) {
	/*
	* Function to create a tree
	* Made from simple solid Toruses, and a Cylinder
	*/
	// tree leaves
	float transY = 0.6; // have a variable to hold y translation
	float innerRadius = 0.14;
	float outerRadius = 0.28;
	glColor3f(0, 0.2, 0.0); // set color

	glPushMatrix();
	glTranslatef(transX, 0.15, transZ);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(0.04, 0.1, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(transX, 0.25, transZ);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(0.08, 0.15, 20, 20);
	glPopMatrix();

	// trunk
	glColor3f(0.2, 0.2, 0);
	glPushMatrix();
	glTranslatef(transX, 0, transZ);
	createCylinder(0.05, 0.2);
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
	for (int i = 0; i < 2; i++) {
		angle = i % 180 - 90;
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
	for (int i = 0; i < 6; i++) {
		glPushMatrix();
		glTranslatef(0, 2.25, 0);
		glRotatef(35, 1, 0, 0);
		glRotatef(angle, 0, 1, 0);
		glutSolidTeapot(0.5);
		glPopMatrix();
		angle += 60;
	}

}

void createFlowerBox() {
	// dirt 
	glColor3f(0.20, 0.03, 0.00);
	glPushMatrix();
	glScalef(1.0, 0.8, 4.0);
	glutSolidCube(0.25);
	glPopMatrix();

	// box
	glColor3f(0.3, 0.25, 0.00);
	glPushMatrix();
	glScalef(1.05, 0.75, 4.05);
	glutSolidCube(0.25);
	glPopMatrix();

	//rim
	glColor3f(0.3, 0.25, 0.00);
	glPushMatrix();
	glTranslatef(0, 0.1, 0.5);
	glScalef(1.1, 0.25, 0.25);
	glutSolidCube(0.25);
	glPopMatrix();

	glColor3f(0.3, 0.25, 0.00);
	glPushMatrix();
	glTranslatef(-0.1, 0.1, 0);
	glScalef(0.25, 0.25, 4.0);
	glutSolidCube(0.25);
	glPopMatrix();

	glColor3f(0.3, 0.25, 0.00);
	glPushMatrix();
	glTranslatef(0.1, 0.1, 0);
	glScalef(0.25, 0.25, 4.0);
	glutSolidCube(0.25);
	glPopMatrix();

	glColor3f(0.3, 0.25, 0.00);
	glPushMatrix();
	glTranslatef(0, 0.1, -0.5);
	glScalef(1.1, 0.25, 0.25);
	glutSolidCube(0.25);
	glPopMatrix();

	// flowers
	float transZ = 5.5;
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glScalef(0.07, 0.07, 0.07);
		glTranslatef(0.5, 2.0, transZ);
		createFlower();
		glPopMatrix();

		transZ -= 3.5;
	}

}

void createCar() {
	// body
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslated(0.9, -1.0, 2.05);
	glScaled(2, 1, 1);
	glutSolidCube(.5);
	glPopMatrix();

	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(1.35, -1.25, 2.35);
	glutSolidTorus(.05, .1, 8, 8); // wheel
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.45, -1.25, 2.35);
	glutSolidTorus(.05, .1, 8, 8); // wheel
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.35, -1.25, 1.75);
	glutSolidTorus(.05, .1, 8, 8); // wheel
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.45, -1.25, 1.75);
	glScaled(1, 1, 1);
	glutSolidTorus(.05, .1, 8, 8); // wheel
	glPopMatrix();
}

void createSideWalk() {
	float transX = 0.0;
	float transZ = 0.0;

	for (int i = 0; i < 11; i++) {
		glColor3f(0.5, 0.5, 0.5);
		glPushMatrix();
		glTranslatef(0.0, 0, transZ);
		glScalef(2.0, 0.1, 2.0);
		glutSolidCube(1.0);
		glPopMatrix();

		transZ += 2.05;
	}
}

void createSupportBars() {
	glPushMatrix();
	glRotatef(-20, 0, 1, 0);
	glTranslatef(0.7, 0.0, 0.0);
	createCylinder(0.05, 0.2);
	glPopMatrix();

	glPushMatrix();
	glRotatef(20, 0, 1, 0);
	glTranslatef(0.7, 0.0, 0.0);
	createCylinder(0.05, 0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.65, 0.18, -0.25);
	glRotatef(90, 1, 0, 0);
	createCylinder(0.05, 0.5);
	glPopMatrix();
}

void createSpinner() {
	// bottom plate
	glPushMatrix();
	glScalef(10.0, 0.01, 10.0);
	drawSphere();
	glPopMatrix();

	// support bars
	glPushMatrix();
	createSupportBars();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	createSupportBars();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	createSupportBars();
	glPopMatrix();

	glPushMatrix();
	glRotatef(270, 0, 1, 0);
	createSupportBars();
	glPopMatrix();

}

void createStreet() {
	// asphalt
	glColor3f(0.1, 0.1, 0.1);
	
	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glScalef(2.5, 0.1, 16.30);
	glutSolidCube(1.0);
	glPopMatrix();

	float trans = -5.0;
	glColor3f(1.0, 1.0, 1.0);
	// road markings
	for (int i = 0; i < 10; i++) {
		glPushMatrix();
		glTranslatef(trans, 0.01, trans);
		glRotatef(45, 0, 1, 0);
		glScalef(.1, 0.1, 1);
		glutSolidCube(1.0);
		glPopMatrix();
		trans += 1.5;
	}
}

void createStreetLamp() {
	glColor3f(0.05, 0.05, 0.05);

	// main body
	glPushMatrix();
	createCylinder(0.08, 4.0);
	glPopMatrix();

	// base
	float cubeSize = 0.5;
	float transY = 0.5;
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslatef(0.0, transY, 0.0);
		glScalef(1.0, 0.5, 1.0);
		glutSolidCube(cubeSize);
		glPopMatrix();
		transY -= 0.15;
		cubeSize += 0.1;
	}

	// light top
	glPushMatrix();
	glTranslatef(0.0, 4.2, 0.0);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(0.1, 0.4, 20, 20);
	glPopMatrix();
}

void reshape(int width, int height) {
	/* define the viewport transformation */
	glViewport(0, 0, width, height);
}