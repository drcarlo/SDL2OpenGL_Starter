#pragma once


#include "Utils.h"

#include <iostream>
#include <map>
#include <array>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H


struct Character {
	unsigned int TextureID;  // ID handle of the glyph texture
	std::array<int, 2> Size;       // Size of glyph
	std::array<int, 2> Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};

class FontRenderer
{
public:

	FontRenderer(int winWidth, int winHeight) : windowWidth(winWidth), windowHeight(winHeight) { }
	~FontRenderer() = default;
	void init();
	void RenderText(std::string text, float x, float y, float scale, glm::vec3 color, glm::vec3 rotation);
	
	

private:
	int windowWidth, windowHeight;
	unsigned int programId, projectionLocation, textLocation, textColourLocation, VAO, VBO, rotationLocation;

	void setupShaders();
	std::map<char, Character> charactersMap;
};