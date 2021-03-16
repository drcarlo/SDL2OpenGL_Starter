#include "Texture.h"

#include "Texture.h"


Texture::Texture(const std::string& f)
	: file(f)
{
	/*
	
	Here we should load an image from a file and create a Texture object :)
	
	*/

	unsigned char texturedata[] = { 120, 120, 120, 255 };
	GLCALL(glCreateTextures(GL_TEXTURE_2D, 1, &textureId));
	GLCALL(glBindTexture(GL_TEXTURE_2D, textureId));
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)&texturedata[0]));
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, NULL);

}

Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}

