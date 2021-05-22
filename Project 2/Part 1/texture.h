// CSC 706 Project 2
// Robert Kigobe, Dominic Klusek, Novichenko Konstantin

#pragma once
#include <GL/glew.h>
#include <GL/glut.h>
#include<SOIL/SOIL.h>
#include<fstream>

int LoadGLTextures(GLuint *texture, const char* filename)   // Load Bitmaps And Convert To Textures
{
	/*
	* Code for function taken from tutorial at http://www.swiftless.com/tutorials/glsl/8_bump_mapping.html,
	*  and then modified to utilize SOIL library
	*/

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

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	//Here we are setting the parameter to repeat the texture  instead of clamping the texture
		//to the edge of our shape. 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	return true; // Return Success
}

void FreeTexture(GLuint texture)
{
	/*
	* Code for function taken from tutorial at http://www.swiftless.com/tutorials/glsl/8_bump_mapping.html
	*/
	glDeleteTextures(1, &texture);
}

GLuint textureArray[14];

void LoadAllTextures() {
	GLuint tempTexture;
	LoadGLTextures(&tempTexture, "textures/grass_1_2048x2048.jpg");
	textureArray[0] = tempTexture;
	LoadGLTextures(&tempTexture, "textures/wet-sidewalk-texture.jpg");
	textureArray[1] = tempTexture;
	LoadGLTextures(&tempTexture, "textures/asphalt_texture.jpg");
	textureArray[2] = tempTexture;
	LoadGLTextures(&tempTexture, "textures/paint_texture_recolored.jpg");
	textureArray[3] = tempTexture;
	LoadGLTextures(&tempTexture, "textures/scratched-and-scraped-metal-texture-6.jpg");
	textureArray[4] = tempTexture;
	LoadGLTextures(&tempTexture, "textures/frosted_glass.jpg");
	textureArray[5] = tempTexture;
	LoadGLTextures(&tempTexture, "textures/tiled_roof_texture.jpg");
	textureArray[6] = tempTexture;
	LoadGLTextures(&tempTexture, "textures/stucco-texture-1491937.jpg");
	textureArray[7] = tempTexture;
	LoadGLTextures(&tempTexture, "textures/wood_texture.jpg");
	textureArray[8] = tempTexture;
	LoadGLTextures(&tempTexture, "textures/brick_texture.jpg");
	textureArray[9] = tempTexture;
	LoadGLTextures(&tempTexture, "textures/particle.bmp");
	textureArray[10] = tempTexture;
	LoadGLTextures(&tempTexture, "textures/particle_mask.bmp");
	textureArray[11] = tempTexture;
	LoadGLTextures(&tempTexture, "textures/leaf_texture.jpg");
	textureArray[12] = tempTexture;
	LoadGLTextures(&tempTexture, "textures/wood-log-texture.jpg");
	textureArray[13] = tempTexture;
}

void FreeAllTextures() {
	for (int i = 0; i < 14;  i++) {
		FreeTexture(textureArray[i]);
	}
}