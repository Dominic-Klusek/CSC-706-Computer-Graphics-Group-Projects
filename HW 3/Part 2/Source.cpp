#include <GL/glut.h>
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
	/*glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	GLfloat lightPosition[] = { 0.0f,0.0f, 10.0f, 0.0f };
	GLfloat lightIntensity[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat lightDirection[] = { 0.0, 0.0, -1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);*/

	glEnable(GL_LIGHT1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_position[] = { 0.0, 0.0, 100.0f, 1.0 };
	GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 135);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);

	glEnable(GL_LIGHT1);



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