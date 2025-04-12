#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::RenderModel(Model* model)
{
	model->UseMaterial();
	GLuint modelVAO = model->GetVAO();
	glBindVertexArray(modelVAO);
	glDrawElements(GL_TRIANGLES, model->GetNumIndices(), GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, model->GetNumVertices());
}
