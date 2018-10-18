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

TechDemo::TechDemo()
{
	auto scene = GetScene();
	if (scene)
	{
		auto mesh = GenerateTreeMesh();
		auto renderer = Renderer_ptr(new Renderer(mesh, Material_ptr(new Material()), Transform(vec3(0.0f, -2.0f, 10.0f))));
		scene->Renderers.push_back(renderer);

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