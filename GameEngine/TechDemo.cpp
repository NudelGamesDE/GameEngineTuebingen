#define _USE_MATH_DEFINES
#include <cmath>
#include <thread>
#include <chrono>
#include "TechDemo.h"
#include "PerspectiveCamera.h"
using namespace std;

shared_ptr<Mesh> GenerateTreeMesh()
{
	auto ret = make_shared<Mesh>();

	ret->Vertices.push_back(vec3(1.0f, 0.5f, 0.0f));
	ret->Vertices.push_back(vec3(0.0f, 2.0f, 0.0f));
	ret->Vertices.push_back(vec3(-1.0f, 0.5f, 0.0f));

	ret->Vertices.push_back(vec3(0.5f, 0.5f, 0.0f));
	ret->Vertices.push_back(vec3(-0.5f, 0.5f, 0.0f));
	ret->Vertices.push_back(vec3(-0.5f, 0.0f, 0.0f));

	ret->Vertices.push_back(vec3(-0.5f, 0.0f, 0.0f));
	ret->Vertices.push_back(vec3(0.5f, 0.0f, 0.0f));
	ret->Vertices.push_back(vec3(0.5f, 0.5f, 0.0f));

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

		auto testRay = Ray();
		testRay.Origin = vec3(0, 1.5f, -1);

		for (int i = 0; i < 500; i++)
		{
			auto material = make_shared<Material>();
			material->Color.r = randFloat(0.0f, 0.5f);
			material->Color.g = randFloat(0.6f, 1.0f);
			material->Color.b = randFloat(0.0f, 0.3f);
			auto renderer = make_shared<Renderer>(mesh, material, Transform(vec3(randFloat(-25.0f, 25.0f), 0.0f, randFloat(-50.0f, 50.0f))));
			scene->Renderers.push_back(renderer);
		}

		auto intersection = scene->Intersect(testRay);

		auto camera = make_shared<PerspectiveCamera>();
		camera->FOV = 45.0f / 180.0f * float(M_PI);
		camera->Near = 0.01f;
		camera->Far = 1000;
		camera->transform.Position = vec3(0, 3, -60);
		scene->camera = camera;

		auto worldRay = camera->GenerateRay(vec2(0, 0));
		worldRay.Min = 0;
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
	{
		Stop();
		this_thread::sleep_for(chrono::seconds(5));
	}
}