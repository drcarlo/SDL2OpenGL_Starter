#pragma once

#include <gl/glew.h>
#include <iostream>
#include "Terrain.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/scalar_constants.hpp>
#include "Camera.h"
#include "Terrain.h"

class Model;

class ModelRenderer
{
public:
	ModelRenderer(GE::Camera* c);
	virtual ~ModelRenderer() = default;
	void drawModel(Model* model);


private:
	float pi;
	GE::Camera* camera;
	unsigned int programId, vertexArrayObject;

	int vertexPositionLocation, modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation, uvLocation, textureSamplerLocation;
};