#pragma once

#include <GL/glew.h>
#include <string>
#include <SDL_image.h>

class Texture
{
public:
	Texture(const std::string& f);
	virtual ~Texture() = default;
	GLuint getTextureLocation() { return textureId; }
private:

	// Image properties
	std::string file;

	unsigned int textureId = -1;

};

