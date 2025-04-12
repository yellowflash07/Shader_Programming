
#include "App.h"
#include "Model.h"
#include "Renderer.h"

App app;
Model* testModel;
Renderer renderer;

void Start()
{
	printf("Init\n");
	app.LoadTexture("Green_Texture.jpg");
	app.LoadTexture("TropicalSunnyDayBack2048.bmp");

	Material* lineMaterial = new Material();
	app.LoadMaterial("lineVert.glsl", "lineFrag.glsl", *lineMaterial);

	testModel = new Model("plane_f.ply", "plane.ply", *lineMaterial);

	testModel->m_Transform.Position = glm::vec3(0.0f, 0.0f, -50.0f);
	testModel->m_Transform.Scale = glm::vec3(0.1f);
	testModel->m_Transform.Rotation = glm::vec3(0.0f, 0.0f, glm::radians(180.0f));


}

void Update()
{
	renderer.RenderModel(testModel);
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