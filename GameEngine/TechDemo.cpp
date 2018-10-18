#include "TechDemo.h"

TechDemo::TechDemo()
{
	auto scene = GetScene();
	if (scene)
	{
		auto mesh = Mesh_ptr(new Mesh());
		auto renderer = Renderer_ptr(new Renderer());
		renderer->Mesh = mesh;
		scene->Renderers.push_back(renderer);
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