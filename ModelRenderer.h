#pragma once

#include <gl/glew.h>
#include <iostream>
#include "Terrain.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/scalar_constants.hpp>
#include "Camera.h"
#include "Model.h"
#include "Texture.h"




class ModelRenderer
{
public:
	ModelRenderer(GE::Camera* c);
	virtual ~ModelRenderer() = default;
	void drawModel(Model* model);
	void setTexture(Texture* tex) { texture = tex; }

private:
	float pi;
	Texture* texture;
	GE::Camera* camera;
	unsigned int programId, vertexArrayObject;

	int vertexPositionLocation, transformMatrixLocation, viewMatrixLocation, projectionMatrixLocation, uvLocation, textureSamplerLocation;
};