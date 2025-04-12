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
	void Render();
	void AddModel(Model* model);
private:
	std::vector<Model*> m_models;
};

