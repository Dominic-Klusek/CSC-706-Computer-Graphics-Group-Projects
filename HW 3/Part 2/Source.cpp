#include <GL/glut.h>
#include<iostream>
#include <math.h>
#define W 600
#define H 600
void displaySolid(void)
{

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glOrtho(-W, W, -H, H, -W, W);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(0, 0, 10, 0, 0, 0, 0.0, 1.0, 0.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	float spotExponent = 1.0;
	float spotCutoff = 90;

	GLfloat light1_ambient[] = { 0.0, 0.35, 0.7, 1.0 };
	GLfloat light1_diffuse[] = { 0.5f, 0.5f, 0.5f, 0.5 };
	GLfloat light1_specular[] = { 0.5f, 0.5f, 0.5f, 0.5 };
	GLfloat light1_position[] = { 500.0, -550.0, 300.0f, 1.0 };
	GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent);

	glEnable(GL_LIGHT1);

	GLfloat light2_ambient[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat light2_diffuse[] = { 0.5f, 0.5f, 0.5f, 0.5 };
	GLfloat light2_specular[] = { 0.5f, 0.5f, 0.5f, 0.5 };
	GLfloat light2_position[] = { 500.0, 550.0, 300.0f, 1.0 };

	glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutoff);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent);

	glEnable(GL_LIGHT2);

	GLfloat light3_ambient[] = { 0.75, 0.0, 0.9, 1.0 };
	GLfloat light3_diffuse[] = { 0.5f, 0.5f, 0.5f, 0.5 };
	GLfloat light3_specular[] = { 0.5f, 0.5f, 0.5f, 0.5 };
	GLfloat light3_position[] = { -500.0, 550.0, 300.0f, 1.0 };

	glLightfv(GL_LIGHT3, GL_AMBIENT, light3_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light3_specular);
	glLightfv(GL_LIGHT3, GL_POSITION, light3_position);

	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, spotCutoff);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, spotExponent);

	glEnable(GL_LIGHT3);

	GLfloat light4_ambient[] = { 0.15, 0.9, 0.0, 1.0 };
	GLfloat light4_diffuse[] = { 0.5f, 0.5f, 0.5f, 0.5 };
	GLfloat light4_specular[] = { 0.5f, 0.5f, 0.5f, 0.5 };
	GLfloat light4_position[] = { -500.0, -550.0, 300.0f, 1.0 };

	glLightfv(GL_LIGHT4, GL_AMBIENT, light4_ambient);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, light4_diffuse);
	glLightfv(GL_LIGHT4, GL_SPECULAR, light4_specular);
	glLightfv(GL_LIGHT4, GL_POSITION, light4_position);

	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, spotCutoff);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, spotExponent);

	glEnable(GL_LIGHT4);



	GLfloat mat_ambient[] = { 0.5f, 0.5f, 0.6f, 1.0f };
	GLfloat mat_diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 90.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


	int teapotSize = 45;
	int x = -W + teapotSize * 2;
	int y = -H + teapotSize;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			glPushMatrix();
			glTranslatef(x, y, 0);
			glutSolidTeapot(teapotSize);
			glPopMatrix();
			x += teapotSize * 3.75;
			std::cout << x << std::endl;
		}
		x = -W + teapotSize * 2;
		y += teapotSize * 3.5;
	}

	glFlush();

	glutSwapBuffers();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(W, H);

	glutInitWindowPosition(100, 100);

	glutCreateWindow("My Teapot");

	glutDisplayFunc(displaySolid);

	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

	glViewport(0, 0, W, H);

	glutMainLoop();
	return 1;
}