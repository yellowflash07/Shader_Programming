#pragma once

#include "GraphicsCommon.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "cShaderManager.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
};

struct Transform
{
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	glm::mat4 GetModelMatrix()
	{
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), Position);
		glm::mat4 rotation = glm::mat4(glm::quat(Rotation));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), Scale);

		model = translation * rotation * scale;

		return model;
	}
};

class Model
{
public:
	Model(std::string fileName, std::string friendlyName, Material& material);
	~Model();
	void UseMaterial();
	GLuint GetVAO() { return m_VAO; }
	unsigned int GetNumVertices() { return m_NumVertices; }
	unsigned int GetNumIndices() { return m_NumIndices; }

	Transform m_Transform;
private:
	Vertex* m_Vertices;
	unsigned int* m_Indices;
	unsigned int m_NumVertices;
	unsigned int m_NumIndices;

	GLuint m_VBO; // stores the vertex data
	GLuint m_VAO; // stores the vertex attribute configuration
	GLuint m_EBO; // stores the indices

	Material* m_Material;

	void LoadVertexDataToGPU();

	//void Load
};

