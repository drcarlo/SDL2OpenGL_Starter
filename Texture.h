#pragma once

#include <GL/glew.h>
#include <string>
#include "Utils.h"

class Texture
{
public:
	Texture(const std::string& f);
	virtual ~Texture();


	unsigned int getTextureId() { return textureId; }
private:

	// Image properties
	std::string file;

	unsigned int textureId = 0;

};

