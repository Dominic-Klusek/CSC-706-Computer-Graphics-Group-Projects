// CSC 706 Project 1 Part 2
// Robert Kigobe, Dominic Klusek, Novichenko Konstantin

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "drawingFunctions.h"
#include "particles.h"
using namespace std;

float currentCameraX = 5.0;
float currentCameraY = 5.0;
float currentCameraZ = 5.0;
float cameraRadius = 7.0;
float cameraAngle = 45;

void display() {
	/////////// clear window ///////////
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// enalbe mipmap coordinate generation
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	
	/////////// future matrix manipulations should affect ///////////

	/////////// draw scene ///////////
	// Nightime Light Parameters
	GLfloat light0_ambient[] = { 0.25, 0.55, 0.85, 1.0 };
	GLfloat light0_diffuse[] = { 0.0f, 0.15f, 0.30f, 1.0 };
	GLfloat light0_specular[] = { 0.60f, 0.8f, 1.0f, 1.0 };
	GLfloat light0_position[] = { 0.8f, 0.8f, 0.5f, 1.0 };
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, .35);
	
	/////////// Light Parameters ///////////
	/*GLfloat light0_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light0_diffuse[] = { 1, 1, 1, 1.0 };
	GLfloat light0_specular[] = { 1, 1, 1, 1.0 };
	GLfloat light0_position[] = { 0.8f, 5.0f, 0.5f, 1.0 };*/

	/////////// Set Light Parameters and enable light ///////////
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glEnable(GL_LIGHT0);

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

	/////////// set material ///////////
	GLfloat ambientLight[] = { 0.10588, 0.058824, 0.0113725 };
	GLfloat diffuseLight[] = { 0.427451, 0.470588, 0.541176 };
	GLfloat specularLight[] = { 0.3333, 0.3333, 0.521569 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientLight);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ambientLight);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ambientLight);

	// apply fog to scene
	GLfloat density = 0.05;
	GLfloat fogColor[4] = { 0.2, 0.2, 0.2, 1.0 };
	glEnable(GL_DEPTH_TEST); //enable the depth testing
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, density);
	glHint(GL_FOG_HINT, GL_NICEST);

	// Push identity matrix onto stack
	glPushMatrix();
	glPushMatrix();

	// load grass texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureArray[0]);

	/////////// ground ///////////
	glPushMatrix();
	glColor3f(0.13, 0.40, 0.00);
	glTranslatef(-1.5, -1.5, -1.5);
	glScalef(100, 0.25, 100);
	glutSolidCube(0.25);
	glPopMatrix();

	/////////// scenry ///////////
	// sidewalks
	glPushMatrix();
	glTranslatef(-3.0, -1.4, 0);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(45, 0, 1, 0);
	createSideWalk();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.0, -1.4, -3.0);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(45, 0, 1, 0);
	createSideWalk();
	glPopMatrix();

	// street
	glPushMatrix();
	glTranslatef(0, -1.45, 0);
	createStreet();
	glPopMatrix();

	// streetlamp 1
	glPushMatrix();
	glTranslatef(-1.85, -1.35, 0.8);
	glRotatef(45, 0, 1, 0);
	glScalef(0.5, 0.5, 0.5);
	createStreetLamp();
	glPopMatrix();

	// draw homes
	glPushMatrix();
	glTranslatef(-5.25, -0.4, 0);
	glRotatef(135, 0, 1, 0);
	createHome();
	glPopMatrix();

	// disable textures
	glDisable(GL_TEXTURE_2D);

	// draw car
	glPushMatrix();
	glTranslatef(carZ, -0.9, carZ+carOffset);
	glRotatef(carAngle, 0, 1, 0);
	createCyberTruck();
	glPopMatrix();

	//draw rain
	glDrawParticles();

	glPopMatrix();
	glPopMatrix();

	/* flush drawing routines to the window */
	glFlush();
}

void keyCallback(unsigned char key, int x, int y) {
	if (key == 'w') {
		//cout << "Up arrow pressed" << endl;
		currentCameraY += 0.5;
	}
	else if (key == 's') {
		//cout << "Down arrow pressed" << endl;
		currentCameraY -= 0.5;
	}
	else if (key == 'a') {
		//cout << "Left arrow pressed" << endl;
		cameraAngle -= 5;
		currentCameraX = sin((cameraAngle * PI) / 180) * cameraRadius;
		currentCameraZ = cos((cameraAngle * PI) / 180) * cameraRadius;
	}
	else if (key == 'd') {
		//cout << "Right arrow pressed" << endl;
		cameraAngle += 5;
		currentCameraX = sin((cameraAngle * PI) / 180) * cameraRadius;
		currentCameraZ = cos((cameraAngle * PI) / 180) * cameraRadius;
	}
	//cout << currentCameraX << " " << currentCameraY << " " << currentCameraZ << endl;

	// change camera position
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(currentCameraX, currentCameraY, currentCameraZ,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	// recall display function
	glutPostRedisplay();

}

void specialKeyFunction(int key, int x, int y) {
	if (key == GLUT_KEY_PAGE_UP) {
	cameraRadius -= 0.5;
	currentCameraX = sin((cameraAngle * PI) / 180) * cameraRadius;
	currentCameraZ = cos((cameraAngle * PI) / 180) * cameraRadius;
	}
	else if (key == GLUT_KEY_PAGE_DOWN) {
	cameraRadius += 0.5;
	currentCameraX = sin((cameraAngle * PI) / 180) * cameraRadius;
	currentCameraZ = cos((cameraAngle * PI) / 180) * cameraRadius;
	}
	//cout << currentCameraX << " " << currentCameraY << " " << currentCameraZ << endl;

	// change camera position
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(currentCameraX, currentCameraY, currentCameraZ,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	// recall display function
	glutPostRedisplay();
}

void timerFunc(int val) {
	glUpdateParticles();

	// move car
	carZ += carVelocity;

	if (carZ > 12.0) {
		carVelocity = -carVelocity;
		carOffset = -carOffset;
		carAngle = 180 + carAngle;
		carZ = 9.9;
	}
	else if (carZ < -12.0) {
		carVelocity = -carVelocity;
		carOffset = -carOffset;
		carAngle = 45;
		carZ = -9.9;
	}
	
	// create new callback
	glutTimerFunc(30, timerFunc, 0);

	// redisplay scene
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
	glutCreateWindow("Neighbourhood at Night");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	/* set up depth-buffering */
	glEnable(GL_DEPTH_TEST);

	/* turn on default lighting */
	glEnable(GL_LIGHTING);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);

	// Enable shading
	glShadeModel(GL_PHONG_WIN); // GL_FLAT is a rough shading 
	
	/* define the projection transformation */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 4, 20);

	/* define the viewing transformation */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// enable textures
	glEnable(GL_TEXTURE_2D);

	/* Create a */
	glutKeyboardFunc(keyCallback);
	glutSpecialFunc(specialKeyFunction);

	LoadAllTextures(); // load all textures

	// populate particles array
	glCreateParticles();

	glutTimerFunc(30, timerFunc, 0);

	/* tell GLUT to wait for events */
	glutMainLoop();

	FreeAllTextures(); // free all textures
	return 0;
}