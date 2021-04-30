#pragma once

#include "Model.h"
#include <gl/glew.h>
#include <iostream>
#include "Terrain.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/scalar_constants.hpp>
#include "Camera.h"
#include "Terrain.h"
#include "Utils.h"



class ModelRenderer
{
public:
	ModelRenderer(GE::Camera* c);
	virtual ~ModelRenderer() = default;
	void drawModel(Model* model);
	void setRotation(float x, float y, float z) { rotation = glm::vec3(x, y, z); }

private:
	float pi;
	GE::Camera* camera;
	unsigned int programId, vertexArrayObject;

	glm::vec3 rotation;
	int vertexPositionLocation, modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation, uvLocation, textureSamplerLocation;
	int lightColour, lightPosition, viewPosition;
	int normalMapLocation;
};