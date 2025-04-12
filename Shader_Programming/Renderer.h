#pragma once

#include "GraphicsCommon.h"
#include <glm/glm.hpp>
#include "Model.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void RenderModel(Model* model);
	void SetViewMatrix(glm::mat4 viewMatrix);
	void SetProjectionMatrix(glm::mat4 projectionMatrix);
};

