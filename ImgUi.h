#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ImgUi
{
public:
	ImgUi() : shaders(new Shader("resources/shaders/gui_vertex_shader.glsl", "resources/shaders/gui_fragment_shader.glsl")) {}

	bool init();
	void render();
	void cleanUp();

	void setTexture(unsigned int newTexture) { textureLocation = newTexture; }
private:
	unsigned int textureLocation = 0;
	unsigned int VAO, VBO;
	Shader* shaders;
};

