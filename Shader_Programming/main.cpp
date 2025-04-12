
#include "App.h"
#include "Model.h"
#include "Renderer.h"

App app;

void g_Start()
{
	printf("Init\n");
	app.LoadTexture("Green_Texture.jpg");
	app.LoadTexture("TropicalSunnyDayBack2048.bmp");

	Material* lineMaterial = new Material();
	app.LoadMaterial("lineVert.glsl", "lineFrag.glsl", *lineMaterial);
	
	//Model *testModel = app.LoadModel("suzanne.obj", "suzanne.obj", *app.pDefaultMaterial);
	//
	//testModel->m_Transform.Position = glm::vec3(0.0f, 0.0f, -0.0f);
	//testModel->m_Transform.Scale = glm::vec3(1.1f);
	//testModel->m_Transform.Rotation = glm::vec3(0.0f, 0.0f, 0.0f);


}

void g_Update(double deltaTime)
{
}

void g_Shutdown()
{
	printf("Shutdown\n");
}

int main()
{
	
	if (app.Init())
	{
		app.Run();
	}

	app.Shutdown();

	return 0;
}