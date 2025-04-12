#include "Model.h"

Model::Model(std::string fileName, std::string friendlyName,Material& material)
{
	// Load the model from the file
	/*m_NumVertices = 4;
	m_Vertices = new Vertex[m_NumVertices];
	m_Vertices[0].Position = glm::vec3(-0.5f, -0.5f, 0.0f);
	m_Vertices[1].Position = glm::vec3(0.5f, -0.5f, 0.0f);
	m_Vertices[2].Position = glm::vec3(0.5, 0.5f, 0.0f);
	m_Vertices[3].Position = glm::vec3(-0.5f, 0.5f, 0.0f);

	m_Vertices[0].TexCoords = glm::vec2(0.0f, 0.0f);
	m_Vertices[1].TexCoords = glm::vec2(1.0f, 0.0f);
	m_Vertices[2].TexCoords = glm::vec2(1.0f, 1.0f);
	m_Vertices[3].TexCoords = glm::vec2(0.0f, 1.0f);

	m_NumIndices = 6;
	m_Indices = new unsigned int[m_NumIndices];
	m_Indices[0] = 0;
	m_Indices[1] = 1;
	m_Indices[2] = 3;
	m_Indices[3] = 1;
	m_Indices[4] = 2;
	m_Indices[5] = 3;*/

	Assimp::Importer importer;
	std::string filePath = "../assets/models/" + fileName;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_ValidateDataStructure | aiProcess_GenNormals | aiProcess_Triangulate
		| aiProcess_PopulateArmatureData | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);

	std::string errorString = importer.GetErrorString();
	if (!errorString.empty())
	{
		printf("Error loading model: %s\n", errorString.c_str());
	}

	if (!scene)
	{
		// Error loading the model
		// Handle the error as needed
		return;
	}

	m_NumVertices = scene->mMeshes[0]->mNumVertices;

	m_Vertices = new Vertex[m_NumVertices];



	for (unsigned int i = 0; i < m_NumVertices; i++)
	{
		m_Vertices[i].Position = glm::vec3(scene->mMeshes[0]->mVertices[i].x, scene->mMeshes[0]->mVertices[i].y, scene->mMeshes[0]->mVertices[i].z);
		
		if (scene->mMeshes[0]->HasVertexColors(0))
		{
			m_Vertices[i].Color = glm::vec3(scene->mMeshes[0]->mColors[0][i].r, scene->mMeshes[0]->mColors[0][i].g, scene->mMeshes[0]->mColors[0][i].b);
		}

		if (scene->mMeshes[0]->HasTextureCoords(0))
		{
			m_Vertices[i].TexCoords = glm::vec2(scene->mMeshes[0]->mTextureCoords[0][i].x, scene->mMeshes[0]->mTextureCoords[0][i].y);
		}

		if (scene->mMeshes[0]->HasNormals())
		{
			m_Vertices[i].Normal = glm::vec3(scene->mMeshes[0]->mNormals[i].x, scene->mMeshes[0]->mNormals[i].y, scene->mMeshes[0]->mNormals[i].z);
		}
		else
		{
			m_Vertices[i].Normal = glm::vec3(0.0f, 0.0f, 0.0f);
		}

	}

	m_NumIndices = scene->mMeshes[0]->mNumFaces * 3;

	m_Indices = new unsigned int[m_NumIndices];

	for (unsigned int i = 0; i < scene->mMeshes[0]->mNumFaces; i++)
	{
		m_Indices[i * 3] = scene->mMeshes[0]->mFaces[i].mIndices[0];
		m_Indices[i * 3 + 1] = scene->mMeshes[0]->mFaces[i].mIndices[1];
		m_Indices[i * 3 + 2] = scene->mMeshes[0]->mFaces[i].mIndices[2];
	}


	m_Material = &material;

	LoadVertexDataToGPU();

	m_Transform.Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Transform.Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Transform.Scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Model::~Model()
{
	delete[] m_Vertices;
	delete[] m_Indices;
}

void Model::UseMaterial()
{
	glUseProgram(m_Material->shaderID);

	int textureUnit = 0;
	// Iterate over each texture in the map
	for (auto& texPair : m_Material->textureBindings)
	{
		const std::string& uniformName = texPair.first;
		GLuint textureID = texPair.second;
		// Query the location of the sampler uniform in the shader
		GLint uniformLocation = glGetUniformLocation(m_Material->shaderID, uniformName.c_str());
		if (uniformLocation != -1)
		{
			glActiveTexture(GL_TEXTURE0 + textureUnit);
			glBindTexture(GL_TEXTURE_2D, textureID);
			// Assign the texture unit to the sampler uniform
			glUniform1i(uniformLocation, textureUnit);
			textureUnit++;
		}
	}

	m_Material->SetMat4("model", m_Transform.GetModelMatrix());

//	glBindTexture(GL_TEXTURE_2D, 0);
}

void Model::LoadVertexDataToGPU()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_NumVertices * sizeof(Vertex), m_Vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_NumIndices * sizeof(unsigned int), m_Indices, GL_STATIC_DRAW);

	// Set the vertex attributes
	m_Material->SetAttribute(0, 3, sizeof(Vertex), 0); // position
	m_Material->SetAttribute(1, 3, sizeof(Vertex), sizeof(glm::vec3)); // color
	m_Material->SetAttribute(2, 2, sizeof(Vertex), sizeof(glm::vec3) * 2); // texcoords
	m_Material->SetAttribute(3, 3, sizeof(Vertex), sizeof(glm::vec3) * 2 + sizeof(glm::vec2)); // normal

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}
