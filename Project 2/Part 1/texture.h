#pragma once
#include <GL/glew.h>
#include <GL/glut.h>
#include<SOIL/SOIL.h>
#include<fstream>

int LoadGLTextures(GLuint *texture, const char* filename)   // Load Bitmaps And Convert To Textures
{
	/* load an image file directly as a new OpenGL texture */
	texture[0] = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
	);
	if (texture[0] == 0)
		return false;


	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //set texture environment parameters  

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//Here we are setting the parameter to repeat the texture  instead of clamping the texture
		//to the edge of our shape. 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return true; // Return Success
}

void FreeTexture(GLuint texture)
{
	/*
	* Code for function taken from tutorial at http://www.swiftless.com/tutorials/glsl/8_bump_mapping.html
	*/
	glDeleteTextures(1, &texture);
}