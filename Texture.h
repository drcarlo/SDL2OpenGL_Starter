#pragma once

#include "Utils.h"
//#include <SDL_image.h>
#include "externals/stb_image.h"
#include <GL/glew.h>
#include <string>


class Texture
{
public:
	Texture() {};
	virtual ~Texture();
	// Load texture
	void initFromFile(const std::string& file);
	// 1x1 gray texture
	void init();
	unsigned int getTextureId() { return textureId; }
private:

	// Image properties
	std::string file;

	unsigned int textureId = 0;

};

