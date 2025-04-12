#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	for (Model* model : m_models)
	{
		delete model;
	}
	m_models.clear();
}

void Renderer::RenderModel(Model* model)
{
	model->UseMaterial();
	GLuint modelVAO = model->GetVAO();
	glBindVertexArray(modelVAO);
	glDrawElements(GL_TRIANGLES, model->GetNumIndices(), GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, model->GetNumVertices());
}

void Renderer::Render()
{
	for (Model* model : m_models)
	{
		RenderModel(model);
	}
}

void Renderer::AddModel(Model* model)
{
	model->m_Transform.Position = glm::vec3(0.0f, 0.0f, -50.0f);
	model->m_Transform.Scale = glm::vec3(1.0f);
	model->m_Transform.Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	m_models.push_back(model);;
}
