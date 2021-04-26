// CSC 706 HW 3 Part 1
// Robert Kigobe, Dominic Klusek, Novichenko Konstantin
// house.cpp
//#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
using namespace std;

float bodyYOffset = 0.0;
float footXOffset = 0.0;
float legXOffset = 0;
float legRotationAngle = 0;
float cameraRotationAngle = 0.0;
float rotationAngle = 0.0;

float swingRotationAngle = 0.0;
float swingLegRotationAngle = 0.0;
float armsClappingRotation = 105;

float animationSpeedRatio = 1.0;
bool cameraRotation = false;
bool increase = true;
bool rightSide = true;
bool spin = true;
bool swingIncrease = true;
bool clappingIncrease = true;

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
	for (int i = 0; i < 4; i++) {
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

void createSwingSet() {
	// frame
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glScalef(8.0, 0.4, 0.4);
	glutSolidCube(0.25);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glRotatef(65, 1, 0, 0);
	glScalef(0.4, 0.4, 10.0);
	glTranslatef(-2.2, 0, 0.125);
	glutSolidCube(0.25);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glRotatef(105, 1, 0, 0);
	glScalef(0.4, 0.4, 10.0);
	glTranslatef(-2.2, 0, 0.125);
	glutSolidCube(0.25);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glRotatef(65, 1, 0, 0);
	glScalef(0.4, 0.4, 10.0);
	glTranslatef(2.2, 0, 0.125);
	glutSolidCube(0.25);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glRotatef(105, 1, 0, 0);
	glScalef(0.4, 0.4, 10.0);
	glTranslatef(2.2, 0, 0.125);
	glutSolidCube(0.25);
	glPopMatrix();

	// seat
	glPushMatrix();
	glColor3f(0.25, 0.5, 0.5);
	glRotatef(swingRotationAngle, 1, 0, 0);
	glTranslatef(0, -1.8, 0);
	glScalef(2.5, 0.2, 1);
	glutSolidCube(0.25);
	glPopMatrix();

	// string
	glPushMatrix();
	glTranslatef(-0.30, 0.0, 0.0);
	glRotatef(swingRotationAngle, 1, 0, 0);
	glTranslatef(0, -1.8, 0);
	createCylinder(0.02, 1.8);
	glPopMatrix();

	// string
	glPushMatrix();
	glTranslatef(0.30, 0.0, 0.0);
	glRotatef(swingRotationAngle, 1, 0, 0);
	glTranslatef(0, -1.8, 0);
	createCylinder(0.02, 1.8);
	glPopMatrix();
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

	for (int i = 0; i < 20; i++) {
		glColor3f(0.5, 0.5, 0.5);
		glPushMatrix();
		glTranslatef(0.0, 0, transZ);
		glScalef(2.0, 0.1, 2.0);
		glutSolidCube(1.0);
		glPopMatrix();

		// draw flower every other sidewalk panel
		if (i % 2 == 0) {
			glPushMatrix();
			glTranslatef(-1.2, 0, transZ);
			glScalef(0.15, 0.15, 0.15);
			createFlower();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(1.2, 0, transZ);
			glScalef(0.15, 0.15, 0.15);
			createFlower();
			glPopMatrix();
		}

		transZ += 2.05;
	}
}

void reshape(int width, int height) {
	/* define the viewport transformation */
	glViewport(0, 0, width, height);
}

void drawSphere()
{
	glutSolidSphere(.1, 16, 16);
}

void drawTopHat() {
	//glRotatef(45, 0, 0, 1);
	// top of hat
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(0, 2.1, 0);
	glScalef(2.2, 0.1, 2.2);
	drawSphere();
	glPopMatrix();

	// main hat body
	glPushMatrix();
	glTranslatef(0, 1.7, 0);
	createCylinder(0.25, 0.4);
	glPopMatrix();

	// brim of hat
	glPushMatrix();
	glTranslatef(0, 1.7, 0);
	glScalef(3.5, 0.1, 3.5);
	drawSphere();
	glPopMatrix();

	// reset color to white
	glColor3f(1, 1, 1);

	// main hat body white stripe
	glPushMatrix();
	glTranslatef(0, 1.7, 0);
	createCylinder(0.26, 0.1);
	glPopMatrix();
}

void drawCane() {
	// cane main body
	glPushMatrix();
	glTranslatef(1.05f, 0, 0);
	createCylinder(0.02, 1.25);
	glPopMatrix();

	// cane handle
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(1.05f, 1.26, 0);
	glRotatef(35, 1, 0, 0);
	createCylinder(0.02, 0.1);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(1.05f, 1.34, 0.05);
	glRotatef(65, 1, 0, 0);
	createCylinder(0.02, 0.1);
	glPopMatrix();

	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(1.05f, 1.39, 0.15);
	glRotatef(95, 1, 0, 0);
	createCylinder(0.02, 0.1);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(1.05f, 1.37, 0.24);
	glRotatef(125, 1, 0, 0);
	createCylinder(0.02, 0.1);
	glPopMatrix();
}

void drawRightSideAppendages()
{
	if (rightSide) {
		glColor3f(0.25, 0.45, 0.64);
		glPushMatrix(); // right arm
		glTranslatef(0.55f, 0.9f - bodyYOffset, 0.0);
		glRotatef(75, 0, 0, 1);
		glScalef(0.5f, 4.0f, 0.5f);
		drawSphere();
		glPopMatrix();

		glPushMatrix(); // right hand
		glColor3f(1, 1, 1);
		glTranslatef(1.05f, 0.8f - bodyYOffset, 0.0);
		glRotatef(rotationAngle*2.0, 1, 0, 1);
		glScalef(0.8, 1.0, 1.25);
		drawSphere();
		glPopMatrix();
		rightSide = false;
	}
	else {
		glColor3f(0.25, 0.45, 0.64);
		glPushMatrix(); // right arm
		glTranslatef(0.40f, 0.7f - bodyYOffset, 0.0f);
		glRotatef(35, 0, 0, 1);
		glScalef(0.5f, 4.0f, 0.5f);
		drawSphere();
		glPopMatrix();

		glPushMatrix(); // right hand
		glColor3f(1, 1, 1);
		glTranslatef(0.69f, 0.28f - bodyYOffset, 0.0f);
		glRotatef(rotationAngle*2.0, 1, 0, 1);
		glScalef(0.8, 1.0, 1.25);
		drawSphere();
		glPopMatrix();
		rightSide = true;
	}
	
	glColor3f(0.3, 0.3, 0.3);
	glPushMatrix(); // right thigh
	glTranslatef(0.2f + legXOffset, -0.4f, 0.0f);
	glRotatef(legRotationAngle, 0, 1, 1);
	glRotatef(15, 0, 0, 1);
	glScalef(0.5f, 3.0f, 0.5f);
	drawSphere();
	glPopMatrix();

	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix(); // knee
	glRotatef(legRotationAngle / 2.0, 0, 1, 1);
	glTranslatef(0.3f + legXOffset, -0.75f, 0.0f);
	drawSphere();
	glPopMatrix();

	glColor3f(0.3, 0.3, 0.3);
	glPushMatrix(); // right shin
	glTranslatef(0.3f + legXOffset, -0.985f, 0.0f);
	//glRotatef(rotationAngle, 0, 1, 0);
	glRotatef(-legRotationAngle, 0, 1, 1);
	glRotatef(6, 0, 0, 1);
	glScalef(0.5f, 3.0f, 0.5f);
	drawSphere();
	glPopMatrix();

	
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix(); // right foot
	glTranslatef(0.33f+ footXOffset, -1.40f, 0.0f);
	glRotatef(rotationAngle*2.0, 0, 1, 0);
	glScalef(0.8, 1.0, 1.25);
	drawSphere(); 
	glPopMatrix();

	// reset color to white
	glColor3f(1, 1, 1);
} 

void drawDancingRobot()
{
	//////////////////// head ///////////////////////
	glPushMatrix(); 
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.0f, 1.5f - bodyYOffset, 0.0f);
	glScalef(3.0f, 3.0f, 3.0f);
	drawSphere();
	glPopMatrix();

	//////////////////// hat ///////////////////////
	glPushMatrix();
	glTranslatef(0.0f, 0.0f - bodyYOffset, 0.0f);
	drawTopHat();
	glPopMatrix();

	//////////////////// cane ///////////////////////
	glPushMatrix();
	glTranslatef(0.0f, 0.0f - bodyYOffset, 0.0f);
	glTranslatef(0, 0.80, 0);
	glRotatef(rotationAngle*2.0, 1, 0, 0);
	glTranslatef(0, -0.80, 0);
	drawCane();
	glPopMatrix();
	
	//////////////////// body ///////////////////////
	glPushMatrix();
	glColor3f(0.25, 0.45, 0.64);
	glTranslatef(0.0f, 0.5f - bodyYOffset, 0.0f);
	glScalef(2.5f, 7.0f, 2.5f);
	drawSphere();
	glPopMatrix();

	//////////////////// right side appendages ///////////////////////
	glPushMatrix();
	drawRightSideAppendages();
	glPopMatrix();

	//////////////////// left side appendages ///////////////////////
	// use reflection to draw the left side appendages
	//
	glPushMatrix();
	glScalef(-1.0, 1.0, 1.0);
	drawRightSideAppendages();
	glPopMatrix();
}

void drawClappingChildAppendages()
{
	glColor3f(0.00, 0.67, 1.0);
	glPushMatrix(); // right arm
	glTranslatef(0.33f, 1.0f, 0.0);
	glRotatef(-armsClappingRotation, 0, 1, 0);
	glTranslatef(0.33, 0, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(0.4f, 4.0f, 0.4f);
	drawSphere();
	glPopMatrix();

	glPushMatrix(); // right hand
	glColor3f(1, 1, 1);
	glTranslatef(0.33, 1.0, 0);
	glRotatef(-armsClappingRotation, 0, 1, 0);
	glTranslatef(0.73, 0.0, 0);
	glScalef(1.0, 1.0, 1.0);
	drawSphere();
	glPopMatrix();

	glColor3f(0.3, 0.3, 0.3);
	glPushMatrix(); // right thigh
	glRotatef(45, 0, 1, 0);
	glTranslatef(0.15, 0.2f, 0.4f);
	glScalef(0.4f, 0.4f, 3.0f);
	drawSphere();
	glPopMatrix();

	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix(); // knee
	glTranslatef(0.65f, 0.2f, 0.45f);
	drawSphere();
	glPopMatrix();

	glColor3f(0.3, 0.3, 0.3);
	glPushMatrix(); // right shin
	glTranslatef(0, 0, 0.8);
	glRotatef(120, 0, 1, 0);
	glTranslatef(0.0, 0.2f, 0.4f);
	glScalef(0.4f, 0.4f, 3.0f);
	drawSphere();
	glPopMatrix();

	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix(); // right foot
	glTranslatef(0.15f, 0.2f, 0.72);
	glRotatef(45, 0, 1, 0);
	glScalef(0.8, 1.0, 1.25);
	drawSphere();
	glPopMatrix();

	// reset color to white
	glColor3f(1, 1, 1);
}

void drawClappingChildRobot()
{
	//////////////////// head ///////////////////////
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.0f, 1.1f, 0.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	drawSphere();
	glPopMatrix();

	//////////////////// hat ///////////////////////
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(0.0f, 1.1, 0.0f);
	glutWireSphere(0.30, 8, 8);
	glPopMatrix();

	//////////////////// body ///////////////////////
	glPushMatrix();
	glColor3f(0.00, 0.67, 1.0);
	glTranslatef(0.0f, 0.5f, 0.0f);
	glScalef(2.5f, 4.0f, 2.5f);
	drawSphere();
	glPopMatrix();

	//////////////////// right side appendages ///////////////////////
	glPushMatrix();
	glScalef(0.7, 0.7, 0.7);
	drawClappingChildAppendages();
	glPopMatrix();

	//////////////////// left side appendages ///////////////////////
	// use reflection to draw the left side appendages
	//
	glPushMatrix();
	glScalef(-1.0, 1.0, 1.0);
	glScalef(0.7, 0.7, 0.7);
	drawClappingChildAppendages();
	glPopMatrix();
}

void drawSwingingChildAppendages()
{
	glColor3f(0.00, 0.67, 1.0);
	glPushMatrix(); // right arm
	glTranslatef(0.40, 1.0, 0.0);
	glRotatef(-65, 1, 0, 0);
	glRotatef(35, 0, 1, 0);
	glScalef(2.0f, 0.4f, 0.4f);
	drawSphere();
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix(); // right elbow
	glTranslatef(0.60, 0.90, 0.0);
	glScalef(0.6f, 0.6f, 0.6f);
	drawSphere();
	glPopMatrix();

	glColor3f(0.00, 0.67, 1.0);
	glPushMatrix(); // right arm
	glTranslatef(0.75, 1.0, 0.0);
	glRotatef(-75, 1, 0, 0);
	glRotatef(-35, 0, 1, 0);
	glScalef(2.0f, 0.4f, 0.4f);
	drawSphere();
	glPopMatrix();

	glPushMatrix(); // right hand
	glColor3f(1, 1, 1);
	glTranslatef(0.85, 1.05, 0.05);
	glScalef(1.0, 1.0, 1.0);
	drawSphere();
	glPopMatrix();

	glColor3f(0.3, 0.3, 0.3);
	glPushMatrix(); // right thigh
	glTranslatef(0.15, 0.2f, 0.4f);
	glScalef(0.4f, 0.4f, 3.0f);
	drawSphere();
	glPopMatrix();

	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix(); // knee
	glTranslatef(0.15f, 0.2f, 0.65f);
	drawSphere();
	glPopMatrix();

	glColor3f(0.3, 0.3, 0.3);
	glPushMatrix(); // right shin
	glTranslatef(0.15, 0.15, 0.65f);
	glRotatef(swingLegRotationAngle, 1, 0, 0);
	glTranslatef(0.0, -0.15, 0.0f);
	glScalef(0.4f, 3.0f, 0.4f);
	drawSphere();
	glPopMatrix();

	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix(); // right foot
	glTranslatef(0.0f, 0.0f, 0.65f);
	glRotatef(swingLegRotationAngle, 1, 0, 0);
	glTranslatef(0.15f, -0.3f, 0.0);
	glRotatef(-swingLegRotationAngle, 1, 0, 0);
	glScalef(0.8, 1.0, 1.25);
	drawSphere();
	glPopMatrix();

	// reset color to white
	glColor3f(1, 1, 1);
}

void drawSwingingChildRobot()
{
	//////////////////// head ///////////////////////
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.0f, 1.1f, 0.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	drawSphere();
	glPopMatrix();

	//////////////////// body ///////////////////////
	glPushMatrix();
	glColor3f(0.00, 0.67, 1.0);
	glTranslatef(0.0f, 0.5f, 0.0f);
	glScalef(2.5f, 4.0f, 2.5f);
	drawSphere();
	glPopMatrix();

	//////////////////// right side appendages ///////////////////////
	glPushMatrix();
	glScalef(0.7, 0.7, 0.7);
	drawSwingingChildAppendages();
	glPopMatrix();

	//////////////////// left side appendages ///////////////////////
	// use reflection to draw the left side appendages
	//
	glPushMatrix();
	glScalef(-1.0, 1.0, 1.0);
	glScalef(0.7, 0.7, 0.7);
	drawSwingingChildAppendages();
	glPopMatrix();
}

void display() {
	/////////// clear window ///////////
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/////////// future matrix manipulations should affect ///////////
	/////////// the modelview matrix ///////////
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	/////////// draw scene ///////////
	//glRotatef(-35, 1, 1, 0);
	//glRotatef(90, 0, 1, 1);

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
	glTranslatef(-3.0, 0.0, 0.0);
	glScalef(2.0, 2.0, 2.0);
	createTree(0, 0);
	glPopMatrix();

	// tree 2
	glPushMatrix();
	glTranslatef(-1.5, 0.0, -3.0);
	glScalef(2.0, 2.0, 2.0);
	createTree(0, 0);
	glPopMatrix();

	// tree 3
	glPushMatrix();
	glTranslatef(-3.0, 0.0, -2.0);
	glScalef(2.0, 2.0, 2.0);
	createTree(0, 0);
	glPopMatrix();

	// sidewalk
	glPushMatrix();
	glTranslatef(0.0, -1.5, -5.0);
	glScalef(0.5, 1.0, 0.5);
	createSideWalk();
	glPopMatrix();

	/////////// swingset ///////////
	glPushMatrix();
	glTranslatef(2.0, 1.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	createSwingSet();
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
	glTranslatef(-1.0, -0.80, -1.0);
	glScalef(0.5, 0.5, 0.5);
	drawClappingChildRobot();
	glPopMatrix();

	// draw dancing adult
	glPushMatrix();
	glTranslatef(-1.0, -0.80, 1.0);
	glScalef(0.5, 0.5, 0.5);
	drawDancingRobot();
	glPopMatrix();

	glPopMatrix();

	/* flush drawing routines to the window */
	glFlush();
}

void timer(int val) {
	// increment rotation angle
	rotationAngle += 1;

	// cycle between the character  "dancing" up and down
	// of increase increment the offsets and angles
	// else decrease offsets amd amg;es
	if (increase) {
		bodyYOffset += (0.02 * animationSpeedRatio);
		footXOffset += (0.005 * animationSpeedRatio);
		legXOffset += (0.01 * animationSpeedRatio);
		legRotationAngle += (1.25 * animationSpeedRatio);
		if (bodyYOffset >= 0.2)
			increase = false;
	}
	else {
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
		glutTimerFunc(70, timer, 0);
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
	gluPerspective(30, 1, 4, 20);

	/* define the viewing transformation */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glutTimerFunc(0, timer, 0);

	/* tell GLUT to wait for events */
	glutMainLoop();
	return 0;
}