#include "TechDemo.h"

Mesh_ptr GenerateTreeMesh()
{
	auto ret = Mesh_ptr(new Mesh());

	ret->Vertices.push_back(vec3(1.0f, -0.5f, 0.0f));
	ret->Vertices.push_back(vec3(0.0f, 1.0f, 0.0f));
	ret->Vertices.push_back(vec3(-1.0f, -0.5f, 0.0f));

	ret->Vertices.push_back(vec3(0.5f, -0.5f, 0.0f));
	ret->Vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
	ret->Vertices.push_back(vec3(-0.5f, -1.0f, 0.0f));

	ret->Vertices.push_back(vec3(-0.5f, -1.0f, 0.0f));
	ret->Vertices.push_back(vec3(0.5f, -1.0f, 0.0f));
	ret->Vertices.push_back(vec3(0.5f, -0.5f, 0.0f));

	return ret;
}

float randFloat(float aMin, float aMax)
{
	return (rand() % 10001) / 10000.0f*(aMax - aMin) + aMin;
}
TechDemo::TechDemo()
{
	auto scene = GetScene();
	if (scene)
	{
		auto mesh = GenerateTreeMesh();

		for (int i = 0; i < 1000; i++)
		{
			auto material = Material_ptr(new Material());
			material->Color.r = randFloat(0.0f, 0.5f);
			material->Color.g = randFloat(0.6f, 1.0f);
			material->Color.b = randFloat(0.0f, 0.3f);
			auto renderer = Renderer_ptr(new Renderer(mesh, material, Transform(vec3(randFloat(-25.0f, 25.0f), -2.0f, randFloat(5.0f, 100.0f)))));
			scene->Renderers.push_back(renderer);
		}

		auto camera = Camera_ptr(new Camera());
		camera->MakePerspective(45.0f / 180.0f * 3.14159f, 0.1f, 1000.0f);
		scene->camera = camera;
	}
}

string TechDemo::GetWindowName()
{
	return "Test Window";
}

void TechDemo::Update()
{
	frames--;
	if (frames < 0)
		Stop();
}