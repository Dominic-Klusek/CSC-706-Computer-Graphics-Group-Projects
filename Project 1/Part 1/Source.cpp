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
float animationSpeedRatio = 1.0;
bool cameraRotation = false;
bool increase = true;
bool rightSide = true;

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

void drawSphere()
{
	glutSolidSphere(.1, 16, 16);
}

void drawHat() {

	//glRotatef(45, 0, 0, 1);
	// top of hat
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(0, 2, 0);
	glScalef(2.1, 0.1, 2.1);
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
		glPushMatrix(); // right arm
		glTranslatef(0.55f, 0.9f - bodyYOffset, 0.0);
		glRotatef(75, 0, 0, 1);
		glScalef(0.5f, 4.0f, 0.5f);
		drawSphere();
		glPopMatrix();

		glPushMatrix(); // right hand
		glColor3f(1, 1, 1);
		glTranslatef(1.05f, 0.8f - bodyYOffset, 0.0);
		glRotatef(rotationAngle, 0, 0, 1);
		drawSphere();
		glPopMatrix();
		rightSide = false;
	}
	else {
		glPushMatrix(); // right arm
		glTranslatef(0.40f, 0.7f - bodyYOffset, 0.0f);
		glRotatef(35, 0, 0, 1);
		glScalef(0.5f, 4.0f, 0.5f);
		drawSphere();
		glPopMatrix();

		glPushMatrix(); // right hand
		glColor3f(1, 1, 1);
		glTranslatef(0.69f, 0.28f - bodyYOffset, 0.0f);
		glRotatef(rotationAngle, 0, 0, 1);
		drawSphere();
		glPopMatrix();
		rightSide = true;
	}
	

	glColor3f(0, 1, 0);
	glPushMatrix(); // right thigh
	glTranslatef(0.2f + legXOffset, -0.4f, 0.0f);
	glRotatef(legRotationAngle, 0, 1, 1);
	glRotatef(15, 0, 0, 1);
	glScalef(0.5f, 3.0f, 0.5f);
	drawSphere();
	glPopMatrix();

	glColor3f(1, 0, 0);
	glPushMatrix(); // knee
	glRotatef(legRotationAngle / 2.0, 0, 1, 1);
	glTranslatef(0.3f + legXOffset, -0.75f, 0.0f);
	drawSphere();
	glPopMatrix();

	glColor3f(0, 1, 0);
	glPushMatrix(); // right shin
	glTranslatef(0.3f + legXOffset, -0.985f, 0.0f);
	//glRotatef(rotationAngle, 0, 1, 0);
	glRotatef(-legRotationAngle, 0, 1, 1);
	glRotatef(6, 0, 0, 1);
	glScalef(0.5f, 3.0f, 0.5f);
	drawSphere();
	glPopMatrix();

	
	glColor3f(1, 0, 0);
	glPushMatrix(); // right foot
	glTranslatef(0.33f+ footXOffset, -1.40f, 0.0f);
	glScalef(0.8, 1.0, 1.25);
	drawSphere(); 
	glPopMatrix();

	// reset color to white
	glColor3f(1, 1, 1);
} 

void drawRobot()
{
	/*
	* Add an item to hands to show that hands are spinning
	* Create a dance animation(really simple one; like bending knees, and swinging arms
	* Make hat eat the character by growing and then going down; while character is scaled down
	*/
	/////////// clear window ///////////
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/////////// future matrix manipulations should affect ///////////
	/////////// the modelview matrix ///////////
	glMatrixMode(GL_MODELVIEW);

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

	glPushMatrix();
	glRotatef(cameraRotationAngle, 0, 1, 0);

	//////////////////// head ///////////////////////
	glPushMatrix(); 
	glTranslatef(0.0f, 1.5f - bodyYOffset, 0.0f);
	glScalef(3.0f, 3.0f, 3.0f);
	drawSphere();
	glPopMatrix();

	//////////////////// hat ///////////////////////
	glPushMatrix();
	glTranslatef(0.0f, 0.0f - bodyYOffset, 0.0f);
	drawHat();
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

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

bool spin = false;
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

	if (cameraRotation)
		cameraRotationAngle += (2.5 * animationSpeedRatio);

	// call function again with delay
	if(spin)
		glutTimerFunc(30, timer, 0);

	// recall display function
	glutPostRedisplay();
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
	}
	else if (value == 2) {
		cameraRotation = false;
	}

}

void starColorMenu(int value) {
	if (value == 1) {

	}
	else if (value == 2) {

	}
	else if (value == 3) {

	}
	else if (value == 4) {

	}
	else if (value == 5) {

	}


}

void centerColorMenu(int value) {
	if (value == 1) {

	}
	else if (value == 2) {

	}
	else if (value == 3) {

	}
	else if (value == 4) {
	}
	else if (value == 5) {

	}

}

void styleMenu(int value) {
	if (value == 1) {

	}
	else if (value == 2) {

	}
	else if (value == 3) {

	}

}

void shadeMenu(int value) {
	if (value == 1) {
		glShadeModel(GL_FLAT);
	}
	else if (value == 2) {
		glShadeModel(GL_SMOOTH);
	}
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
	glutDisplayFunc(drawRobot);
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

	glutTimerFunc(0, timer, 0);

	// create menu
	int baseMenu = glutCreateMenu(mainMenu);  // the base menu
	int animSubMenu = glutCreateMenu(animMenu); // submenu for drawing different figures
	int shadeSubMenu = glutCreateMenu(shadeMenu); // submenu for color submenus
	int rotationSubMenu = glutCreateMenu(rotationMenu); // the submenu for choosing the background polygon color(if applicable)
	int starColorSubMenu = glutCreateMenu(starColorMenu); // the submenu for choosing the star color
	int centerColorSubMenu = glutCreateMenu(centerColorMenu); // the submenu for chooseing the middle polygon color
	int styleSubMenu = glutCreateMenu(styleMenu); // the submenu to choose drawing style

	// start menu
	glutSetMenu(baseMenu);
	glutAddMenuEntry("Clear Screen", 1);

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