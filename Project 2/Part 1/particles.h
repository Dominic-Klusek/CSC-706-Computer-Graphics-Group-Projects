#pragma once
#include "texture.h"

/*
*	Patricle code was taken from tutorial at http://www.swiftless.com/tutorials/opengl/particles.html, 
	and then modified to better suit our needs
*/

const int ParticleCount = 500;

typedef struct
{
	double Xpos;
	double Ypos;
	double Zpos;
	double Xmov;
	double Zmov;
	double direction;
	double acceleration;
	double scalez;
	bool visible;
}PARTICLES;

PARTICLES Particle[ParticleCount];

void glCreateParticles(void) {
	int i;
	for (i = 1; i < ParticleCount; i++)
	{
		Particle[i].Xpos = (((((((2 - 1 + 1) * rand() % 11) + 1) - 1 + 1) * rand() % 11) + 1)) - (((((((2 - 1 + 1) * rand() % 11) + 1) - 1 + 1) * rand() % 11) + 1));
		Particle[i].Ypos = (((((((2 - 1 + 1) * rand() % 11) + 1) - 1 + 1) * rand() % 11) + 1)) - (((((((2 - 1 + 1) * rand() % 11) + 1) - 1 + 1) * rand() % 11) + 1));
		Particle[i].Zpos = (((((((2 - 1 + 1) * rand() % 11) + 1) - 1 + 1) * rand() % 11) + 1)) - (((((((2 - 1 + 1) * rand() % 11) + 1) - 1 + 1) * rand() % 11) + 1));
		Particle[i].scalez = 0.25;
		Particle[i].acceleration = -0.1;
	}
}

void glUpdateParticles(void) {
	int i;
	glColor3f(1, 1, 1);
	for (i = 1; i < ParticleCount; i++)
	{

		Particle[i].Ypos = Particle[i].Ypos + Particle[i].acceleration;

		Particle[i].Xpos = Particle[i].Xpos + Particle[i].Xmov;
		Particle[i].Zpos = Particle[i].Zpos + Particle[i].Zmov;

		if (Particle[i].Ypos < -2)
		{
			Particle[i].Xpos = (((((((2 - 1 + 1) * rand() % 11) + 1) - 1 + 1) * rand() % 11) + 1)) - (((((((2 - 1 + 1) * rand() % 11) + 1) - 1 + 1) * rand() % 11) + 1));
			Particle[i].Ypos = 5;
			Particle[i].Zpos = (((((((2 - 1 + 1) * rand() % 11) + 1) - 1 + 1) * rand() % 11) + 1)) - (((((((2 - 1 + 1) * rand() % 11) + 1) - 1 + 1) * rand() % 11) + 1));
		}

	}
}

void glDrawParticles(void) {
	int i;
	for (i = 1; i < ParticleCount; i++)
	{
		glPushMatrix();
		glTranslatef(Particle[i].Xpos, Particle[i].Ypos, Particle[i].Zpos);

		glScalef(Particle[i].scalez, Particle[i].scalez, Particle[i].scalez);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

		glBlendFunc(GL_ONE, GL_ONE);

		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);
		glVertex3f(-0.02, -0.5, 0);
		glTexCoord2d(1, 0);
		glVertex3f(0.02, -0.5, 0);
		glTexCoord2d(1, 1);
		glVertex3f(0.02, 0.5, 0);
		glTexCoord2d(0, 1);
		glVertex3f(-0.02, 0.5, 0);
		glEnd();

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		glPopMatrix();
	}
}