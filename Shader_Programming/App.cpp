#include "App.h"

void Start();
void Update();

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

	cShaderManager::cShader vertexShader;
	vertexShader.fileName = "vert.glsl";

	cShaderManager::cShader tessControlShader;
	tessControlShader.fileName = "";
	//tessControlShader.fileName = "";

	cShaderManager::cShader tessEvalShader;
	//tessEvalShader.fileName = "";
	tessEvalShader.fileName = "";

	cShaderManager::cShader fragmentShader;
	fragmentShader.fileName = "frag.glsl";

	if (!m_shaderManager.createProgramFromFile("shader01", vertexShader, fragmentShader, tessControlShader, tessEvalShader, *pDefaultMaterial))
	{
		std::cout << "Error: Couldn't compile or link:" << std::endl;
		std::cout << m_shaderManager.getLastError();
		return false;
	}


	m_pCamera = new Camera(glm::vec3(0.0, 0.0f, 10.0f),
						   glm::vec3(0.0f, 0.0f, -1.0f),
						   glm::vec3(0.0f, 1.0f, 0.0f), 0.1f, 10000.0f);

	glEnable(GL_DEPTH_TEST);

	glfwSetCursorPosCallback(m_pWindow, SMousePositionCallback);
	
	Start();

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

		Update();
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
	cShaderManager::cShader vertexShader;
	vertexShader.fileName = vertexShaderFile;

	cShaderManager::cShader tessControlShader;
	tessControlShader.fileName = "";
	//tessControlShader.fileName = "";

	cShaderManager::cShader tessEvalShader;
	//tessEvalShader.fileName = "";
	tessEvalShader.fileName = "";

	cShaderManager::cShader fragmentShader;
	fragmentShader.fileName = fragmentShaderFile;

	std::string shaderName = vertexShaderFile + fragmentShaderFile;

	if (!m_shaderManager.createProgramFromFile(shaderName, vertexShader, fragmentShader, tessControlShader, tessEvalShader, material))
	{
		std::cout << "Error: Couldn't compile or link:" << std::endl;
		std::cout << m_shaderManager.getLastError();
		//return false;
	}
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
