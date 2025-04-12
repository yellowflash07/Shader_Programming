#pragma once

#include "GraphicsCommon.h"
#include <string>
#include "cBasicTextureManager.h"
#include "Model.h"
#include "cShaderManager.h"
#include "Camera.h"

class Skybox
{
public:
	Skybox(std::string posX_fileName, std::string negX_fileName,
		std::string posY_fileName, std::string negY_fileName,
		std::string posZ_fileName, std::string negZ_fileName);
	~Skybox();

	Camera* m_pCamera;
	void Render();
private:
	cBasicTextureManager* m_textureManager;
	Model* m_pModel;
	Material* m_pMaterial;
};

