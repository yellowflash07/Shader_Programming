#include "Skybox.h"

Skybox::Skybox(std::string posX_fileName, std::string negX_fileName, std::string posY_fileName, std::string negY_fileName, std::string posZ_fileName, std::string negZ_fileName)
{
	std::string skyBoxError = "";
	m_textureManager = new cBasicTextureManager();
	m_textureManager->SetBasePath("../assets/textures/skybox/");
	if (!m_textureManager->CreateCubeTextureFromBMPFiles("sky",
		"TropicalSunnyDayLeft2048.bmp",
		"TropicalSunnyDayRight2048.bmp",
		"TropicalSunnyDayDown2048.bmp",
		"TropicalSunnyDayUp2048.bmp",
		"TropicalSunnyDayFront2048.bmp",
		"TropicalSunnyDayBack2048.bmp",
		true, skyBoxError))
	{
				std::cout << "Skybox error: " << skyBoxError << std::endl;
	}

	m_pMaterial = cShaderManager::getInstance()->CreateMaterial("skyboxVert.glsl", "skyboxFrag.glsl");

	m_pModel = new Model("skybox.ply", "skybox", *m_pMaterial);
//	m_pModel->m_Transform.Scale = glm::vec3(100.0f);
}

Skybox::~Skybox()
{
	delete m_pModel;
	delete m_pMaterial;
	delete m_textureManager;
}

void Skybox::Render()
{
	glUseProgram(m_pMaterial->shaderID);
//	glDepthMask(GL_FALSE);
	m_pMaterial->SetMat4("view", m_pCamera->matView);
	m_pMaterial->SetMat4("projection", m_pCamera->matProjection);

	GLuint modelVAO = m_pModel->GetVAO();
	glBindVertexArray(modelVAO);
	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndices(), GL_UNSIGNED_INT, 0);

	GLint textureUnit30 = 30;
	GLuint skyBoxID = m_textureManager->getTextureIDFromName("sky");
	glActiveTexture(GL_TEXTURE0 + textureUnit30);
	// NOTE: Binding is NOT to GL_TEXTURE_2D
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxID);
	GLint skyBoxSampler_UL = glGetUniformLocation(m_pMaterial->shaderID, "cubeMap");
	glUniform1i(skyBoxSampler_UL, textureUnit30);

	//glDepthMask(GL_TRUE);

}			   
