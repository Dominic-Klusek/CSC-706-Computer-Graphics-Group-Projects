// CSC 706 Project 2
// Robert Kigobe, Dominic Klusek, Novichenko Konstantin

#pragma once
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "texture.h"
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
using namespace std;

#define PI 3.14159

float FPS = 30;
float carZ = -10, carOffset = 1.25, carVelocity = 0.08, carAngle = 45;
float currentCameraX = 5.0, currentCameraY = 5.0, currentCameraZ = 5.0;
float cameraRadius = 7.0, cameraAngle = 45;

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

void createTree() {
	/*
	* Function to create a tree
	* Made from simple solid Toruses, and a Cylinder
	*/
	// tree leaves
	glBindTexture(GL_TEXTURE_2D, textureArray[12]);
	glBlendFunc(GL_ZERO, GL_ONE);
	float transY = 0.6; // have a variable to hold y translation
	float innerRadius = 0.14;
	float outerRadius = 0.28;

	for (int i = 0; i < 6; i++) {
		glPushMatrix();
		glTranslatef(0, transY, 0);
		glRotatef(-90, 1, 0, 0);
		glutSolidTorus(innerRadius, outerRadius, 20, 20);
		glPopMatrix();

		transY = transY + 0.1;
		innerRadius = innerRadius / 1.2;
		outerRadius = outerRadius / 1.2;
	}

	glBindTexture(GL_TEXTURE_2D, textureArray[13]);

	// trunk
	glColor3f(0.2, 0.2, 0);
	glPushMatrix();
	glTranslatef(0, 0, 0);
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

void createSideWalk() {
	float transX = 0.0;
	float transZ = -21.0;

	// get texture, bind, and then automatically calculate texture coordinates
	glBindTexture(GL_TEXTURE_2D, textureArray[1]);

	// rotate sidewalk texture to make it more consitent with cameraAngle
	glPushMatrix();
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glRotatef(cameraAngle - 45, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	for (int i = 0; i < 26; i++) {
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
	
	// load asphalt texture
	glBindTexture(GL_TEXTURE_2D, textureArray[2]);

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glScalef(3.5, 0.1, 29.00);
	glutSolidCube(1.0);
	glPopMatrix();

	// load paint texture
	glBindTexture(GL_TEXTURE_2D, textureArray[3]);
	float trans = -7.5;
	glColor3f(1.0, 1.0, 1.0);

	// road markings
	for (int i = 0; i < 12; i++) {
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
	//glColor3f(0.05, 0.05, 0.05);

	// light for streetlamp 1
	float spotExponent = 0;
	float spotCutoff = 70.75;

	// bottom right light
	GLfloat light1_ambient[] = { 1, 1, 1, 1.0 };
	GLfloat light1_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0 };
	GLfloat light1_specular[] = { 0.5f, 0.5f, 0.5f, 0.5 };
	GLfloat light1_position[] = { -1.3, 4, 0.8, 1.0 };
	GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent);
	//glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.4);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, .55);

	glEnable(GL_LIGHT1);

	// get texture, bind, and then automatically calculate texture coordinates
	glBindTexture(GL_TEXTURE_2D, textureArray[4]);

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

	// get texture, bind, and then automatically calculate texture coordinates
	glBindTexture(GL_TEXTURE_2D, textureArray[5]);

	// white LED
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 4.1, 0.0);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(0.1, 0.4, 20, 20);
	glPopMatrix();
}

void createCyberTruckWheelArch() {
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glNormal3d(1, 1, 1);

	glVertex3f(0, 0.5, 0);
	glVertex3f(2, 0.5, 0);
	glVertex3f(2, 0, -1);
	glVertex3f(0, 0, -1);

	glEnd();

	glBegin(GL_POLYGON);
	glNormal3d(1, 1, 1);

	glVertex3f(0, 0.5, 0);
	glVertex3f(0, 0, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 0);

	glEnd();

	glBegin(GL_POLYGON);
	glNormal3d(1, 1, 1);

	glVertex3f(2, 0.5, 0);
	glVertex3f(2, 0, -1);
	glVertex3f(3, -1, -1);
	glVertex3f(3, -1, 0);

	glEnd();
	glPopMatrix();
}

void createCyberTruck() {
	glColor3f(0.5, 0.5, 0.5);
	// main body middle
	glPushMatrix();
	glScalef(1.0, 0.2, 2.0);
	glutSolidCube(1.0);
	glPopMatrix();
	
	// main body accents
	glPushMatrix();
	glTranslatef(0.5, -0.13, 0.0);
	glRotatef(-5, 0, 0, 1);
	glScalef(0.1, 0.45, 2.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, -0.13, 0.0);
	glRotatef(5, 0, 0, 1);
	glScalef(0.1, 0.45, 2.0);
	glutSolidCube(1.0);
	glPopMatrix();

	// car underside
	glPushMatrix();
	glTranslatef(0.0, -0.2, 0.0);
	glScalef(0.5, 0.3, 2.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.2, 0.8);
	glScalef(1.0, 0.3, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.2, -0.8);
	glScalef(1.0, 0.3, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.2, 0.0);
	glScalef(1.0, 0.3, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();
	
	glColor3f(0.1, 0.1, 0.1);

	// car windshield
	// using blend GL_ONE with itself gives a transluencent material
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glPushMatrix();
	glTranslatef(0.0, 0.27, 0.71);
	glRotatef(35, 1, 0, 0);
	glScalef(1.1, 0.05, 0.68);
	glutSolidCube(1.0);
	glPopMatrix();

	// car headlights
	glPushMatrix();
	glTranslatef(0.38, -0.23, 0.92);
	glScalef(0.2, 0.27, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.32, -0.23, 0.92);
	glScalef(0.2, 0.27, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();
	
	// no longer need transluecent material
	glDisable(GL_BLEND);

	float spotExponent = 0;
	float spotCutoff = 56.75;
	glPushMatrix();
	// give the car a light
	GLfloat light2_ambient[] = { 1, 1, 1, 1.0 };
	GLfloat light2_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0 };
	GLfloat light2_specular[] = { 0.5f, 0.5f, 0.5f, 0.5 };
	GLfloat light2_position[] = { 0.0, -0.23, 0.0, 1.0 };
	GLfloat spot_direction[] = { 0.0, 0.0, 0.5 };

	glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutoff);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, .35);

	glEnable(GL_LIGHT2);
	glPopMatrix();

	// car roof
	glPushMatrix();
	glTranslatef(0.0, 0.27, -0.27);
	glRotatef(-15, 1, 0, 0);
	glScalef(1.1, 0.05, 1.48);
	glutSolidCube(1.0);
	glPopMatrix();

	glColor3f(0.5, 0.5, 0.5);
	// side windows
	glPushMatrix();
	glBegin(GL_TRIANGLES);
		glVertex3f(0.555, 0.48, 0.45);
		glVertex3f(0.565, 0.09, 1.0);
		glVertex3f(0.565, 0.09, -1.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_TRIANGLES);
		glVertex3f(-0.555, 0.48, 0.45);
		glVertex3f(-0.565, 0.09, 1.0);
		glVertex3f(-0.565, 0.09, -1.0);
	glEnd();
	glPopMatrix();

	// car wheels
	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();
	glTranslatef(0.5, -0.3, 0.45);
	glRotatef(90, 0, 1, 0);
	glScalef(1.0, 1.0, 2.0);
	glutSolidTorus(0.05, 0.15, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, -0.3, -0.45);
	glRotatef(90, 0, 1, 0);
	glScalef(1.0, 1.0, 2.0);
	glutSolidTorus(0.05, 0.15, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, -0.3, 0.45);
	glRotatef(90, 0, 1, 0);
	glScalef(1.0, 1.0, 2.0);
	glutSolidTorus(0.05, 0.15, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, -0.3, -0.45);
	glRotatef(90, 0, 1, 0);
	glScalef(1.0, 1.0, 2.0);
	glutSolidTorus(0.05, 0.15, 20, 20);
	glPopMatrix();

	// wheel "rims"
	glPushMatrix();
	glTranslatef(0.5, -0.3, 0.45);
	glRotatef(90, 0, 1, 0);
	glScalef(0.15, 0.15, 0.15);
	glutSolidOctahedron();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, -0.3, -0.45);
	glRotatef(90, 0, 1, 0);
	glScalef(0.15, 0.15, 0.15);
	glutSolidOctahedron();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, -0.3, 0.45);
	glRotatef(90, 0, 1, 0);
	glScalef(0.15, 0.15, 0.15);
	glutSolidOctahedron();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, -0.3, -0.45);
	glRotatef(90, 0, 1, 0);
	glScalef(0.15, 0.15, 0.15);
	glutSolidOctahedron();
	glPopMatrix();

	// wheel arch accents
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(0.5, -0.09, 0.32);
	glScalef(0.17, 0.17, 0.14);
	glRotatef(-90, 0, 1, 0);
	createCyberTruckWheelArch();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, -0.09, -0.6);
	glScalef(0.17, 0.17, 0.14);
	glRotatef(-90, 0, 1, 0);
	createCyberTruckWheelArch();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, -0.09, 0.6);
	glScalef(0.17, 0.17, 0.14);
	glRotatef(90, 0, 1, 0);
	createCyberTruckWheelArch();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, -0.09, -0.32);
	glScalef(0.17, 0.17, 0.14);
	glRotatef(90, 0, 1, 0);
	createCyberTruckWheelArch();
	glPopMatrix();

	/*char stringArray[50];
	sprintf_s(stringArray, "%s: %f", "Hello", 15.5);
	
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, (const unsigned char*) stringArray);*/

}

void createHome() {
	glBindTexture(GL_TEXTURE_2D, textureArray[8]);

	/////////// door ///////////
	glPushMatrix();
	glColor3f(0.66, 0.76, 0.83);
	glTranslatef(-0.35, -0.35, 1.0);
	glScalef(3, 5, 0.25);
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

	glBindTexture(GL_TEXTURE_2D, textureArray[7]);
	/////////// house ///////////
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(2); // building
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, textureArray[6]);
	// roof
	glPushMatrix();
	glColor3f(0.56, 0.63, 0.7);
	glTranslated(0, 1.0, 0);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(1.5, 1, 16, 8);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, textureArray[9]);
	// chimney
	glPushMatrix();
	glColor3f(0.28, 0.32, 0.35);
	glTranslated(1, 1.5, -0.5);
	glScaled(1, 3, 1);
	glutSolidCube(.25);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	/////////// door handle ///////////
	glPushMatrix();
	glTranslatef(-0.10, -0.3, 1.1);
	glutSolidSphere(0.05, 128, 128);
	glPopMatrix();

	// window
	glPushMatrix();
	glColor3f(0.6, 0.8, 1);
	glTranslatef(0.55, 0.35, 0.97);
	glScaled(3, 3, 0.25);
	glutSolidCube(0.25);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}

void reshape(int width, int height) {
	/* define the viewport transformation */
	glViewport(0, 0, width, height);
}