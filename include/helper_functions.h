#include <GL/glut.h>
#include "../include/imageloader.h"

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 image->width, image->height,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,

				 image->pixels);
	return textureId;
}

GLuint loadTx(string str) {
	const char* path = str.c_str();
	Image* image = loadBMP(path);
	GLuint tex = loadTexture(image);
	delete image;
	return tex;
}