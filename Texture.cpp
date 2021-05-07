#include "Texture.h"



void Texture::initFromFile(const std::string& file)
{
	int width, height, channels;
	SDL_Surface* surface = IMG_Load(file.c_str());
	
	width = surface->w;
	height = surface->h;
	channels = surface->format->BytesPerPixel;

	GLCALL(glGenTextures(1, &textureId));
	GLCALL(glBindTexture(GL_TEXTURE_2D, textureId));
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)surface->pixels));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, NULL);

	SDL_FreeSurface(surface);
}

void Texture::init()
{
	unsigned char texturedata[] = { 255, 0, 0, 255 };
	GLCALL(glCreateTextures(GL_TEXTURE_2D, 1, &textureId));
	GLCALL(glBindTexture(GL_TEXTURE_2D, textureId));
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)&texturedata[0]));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, NULL);

}

Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}

