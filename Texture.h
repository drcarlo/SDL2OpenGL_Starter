#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string& f);
	virtual ~Texture() = default;

private:

	// Image properties
	std::string file;

	unsigned int textureId = -1;

};

