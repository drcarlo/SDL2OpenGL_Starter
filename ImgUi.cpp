#include "ImgUi.h"

bool ImgUi::init()
{
	if (!shaders->init()) {
		std::cout << "Could not init UI shaders!" << std::endl;
		return false;
	}

	glm::vec2 uiSize = glm::vec2(300.0f, 300.0f);

	const float quad[]{
		0.0f, 0.0f,        0.0f, 0.0f, 0.0f,
		0.0f, uiSize.y,    0.0f, 0.0f, 1.0f,
		uiSize.x, uiSize.y,0.0f, 1.0f, 1.0f,
		uiSize.x, uiSize.y,0.0f, 1.0f, 1.0f,
		uiSize.x, 0.0f,    0.0f, 1.0f, 0.0f,
		0.0f, 0.0f,        0.0f, 0.0f, 0.0f
	};

	GLCALL(glGenVertexArrays(1, &VAO));
	GLCALL(glGenBuffers(1, &VBO));
	GLCALL(glBindVertexArray(VAO));

	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
		GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW));
		GLCALL(glEnableVertexAttribArray(0));
		GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr));
	
		GLCALL(glEnableVertexAttribArray(1));
		GLCALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3)));


	GLCALL(glBindVertexArray(NULL));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, NULL));

}

void ImgUi::render()
{
	shaders->bind();
	glBindVertexArray(VAO);
		
	glm::mat4 projection = glm::ortho<float>(0.0f, float(1280), float(1024), float(0));
	GLCALL(glUniformMatrix4fv(shaders->getLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection)));
	GLCALL(glUniform1i(shaders->getLocation("imageTexture"), 0));
	GLCALL(glActiveTexture(GL_TEXTURE0));
	GLCALL(glBindTexture(GL_TEXTURE_2D, textureLocation));

		GLCALL(glDrawArrays(GL_TRIANGLES, 0, 6));
	
	glBindTexture(GL_TEXTURE_2D, NULL);
	glBindVertexArray(NULL);
	shaders->unbind();
}

void ImgUi::cleanUp()
{
}
