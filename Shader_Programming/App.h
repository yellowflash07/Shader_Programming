#pragma once

#include "GraphicsCommon.h"
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include "cShaderManager.h"
#include "cBasicTextureManager.h"
#include "Camera.h"
#include "Renderer.h"

class App
{
public:
	App();
	~App();

	bool Init();
	void Run();
	void Shutdown();

	Texture* LoadTexture(std::string textureName);
	Texture* GetTexture(std::string textureName);
	Material* pDefaultMaterial;

	void LoadMaterial(std::string vertexShader, std::string fragmentShader, Material& material);
	Model* LoadModel(std::string modelName, std::string friendlyName, Material& material);
	//static double m_mouseX;
	//static double m_mouseY;

private:
	GLFWwindow* m_pWindow;
	void BeginRender();
	void EndRender();
	GLint m_shaderProgram;
	cShaderManager m_shaderManager;
	cBasicTextureManager m_textureManager;
	Camera* m_pCamera;
	Renderer* m_pRenderer;

	double currentTime = 0.0f;
	double lastTime = 0.0f;
	double deltaTime = 0.0f;
};

