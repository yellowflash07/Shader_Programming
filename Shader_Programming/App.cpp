#include "App.h"

void g_Start();
void g_Update(double deltaTime);
void g_Shutdown();

double m_mouseX = 0.0;
double m_mouseY = 0.0;
void SMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	m_mouseX = xpos;
	m_mouseY = ypos;
}

App::App()
{
	pDefaultMaterial = new Material();
}

App::~App()
{
}

bool App::Init()
{
	if (!glfwInit())
		return false;	

	//create opengl context

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	m_pWindow = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);

	if (!m_pWindow)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_pWindow);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	m_shaderManager.setBasePath("../assets/shaders/");
	m_textureManager.SetBasePath("../assets/textures/");

	LoadMaterial("vert.glsl", "frag.glsl", *pDefaultMaterial);

	m_pCamera = new Camera(glm::vec3(0.0, 0.0f, 10.0f),
						   glm::vec3(0.0f, 0.0f, -1.0f),
						   glm::vec3(0.0f, 1.0f, 0.0f), 0.1f, 10000.0f);

	glEnable(GL_DEPTH_TEST);

	glfwSetCursorPosCallback(m_pWindow, SMousePositionCallback);
	
	m_pRenderer = new Renderer();
	//load the skybox
	m_pSkybox = new Skybox("","","","","","");
	m_pSkybox->m_pCamera = m_pCamera;
	g_Start();

	return true;
}

void App::Run()
{
	while(!glfwWindowShouldClose(m_pWindow))
	{
		BeginRender();
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		m_pSkybox->Render();
		m_pRenderer->Render();

		g_Update(deltaTime);

		m_pCamera->Update(m_pWindow, deltaTime);
		m_pCamera->ProcessMouseMovement(m_mouseX, m_mouseY);
		pDefaultMaterial->SetMat4("view", m_pCamera->matView);
		pDefaultMaterial->SetMat4("projection", m_pCamera->matProjection);
		EndRender();

		
		if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_pWindow, true);
	}

	glfwTerminate();

}

void App::Shutdown()
{
	delete m_pCamera;
	delete m_pRenderer;
	for (Material* material : m_materials)
	{
		delete material;
	}
	g_Shutdown();
}

Texture* App::LoadTexture(std::string textureName)
{
	return m_textureManager.Create2DTextureFromBMPFile(textureName, true);
}

Texture* App::GetTexture(std::string textureName)
{
	return m_textureManager.textureMap[textureName];
}

void App::LoadMaterial(std::string vertexShaderFile, std::string fragmentShaderFile, Material& material)
{
	Material* newMaterial = cShaderManager::getInstance()->CreateMaterial(vertexShaderFile, fragmentShaderFile);
	material = *newMaterial;
	m_materials.push_back(&material);
}

Model* App::LoadModel(std::string modelName, std::string friendlyName, Material& material)
{
	Model* model = new Model(modelName, friendlyName, material);
	m_pRenderer->AddModel(model);
	return model;
}


void App::BeginRender()
{
	float ratio;
	int width, height;

	glfwGetFramebufferSize(m_pWindow, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

void App::EndRender()
{	
	glfwSwapBuffers(m_pWindow);
	glfwPollEvents();
}
