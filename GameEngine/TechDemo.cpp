#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL_keycode.h>
#include "glm\gtc\quaternion.hpp"
#include "TechDemo.h"
#include "PerspectiveCamera.h"
using namespace std;
using namespace glm;

shared_ptr<Mesh> GenerateTreeMesh()
{
	auto positions = vector<vec3>();

	auto segments = 8;
	auto angle = (float)M_PI / segments;
	auto rotation = quat(cos(angle), 0, sin(angle), 0);
	auto rotationCon = conjugate(rotation);

	auto rotate = [rotation, rotationCon](vec3 aPoint)
	{
		auto ret = rotationCon * quat(0, aPoint.x, aPoint.y, aPoint.z) * rotation;
		return vec3(ret.x, ret.y, ret.z);
	};

	auto addSegment = [rotate, segments, &positions](vec3 aTop, vec3 aSide)
	{
		for (auto i = 0; i < segments; i++)
		{
			auto nextSide = rotate(aSide);
			positions.push_back(aTop);
			positions.push_back(aSide);
			positions.push_back(nextSide);
			aSide = nextSide;
		}
	};

	addSegment(vec3(0, 1, 0), vec3(0.25f, 0.75f, 0));
	addSegment(vec3(0, 1, 0), vec3(0.4f, 0.5f, 0));
	addSegment(vec3(0, 1, 0), vec3(0.5f, 0.25f, 0));
	addSegment(vec3(0, 1, 0), vec3(0.1f, 0, 0));

	return make_shared<Mesh>(positions, vector<vec2>(), vector<vec3>());
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

		for (int i = 0; i < 50; i++)
		{
			auto material = make_shared<Material>();
			material->Color.r = randFloat(0.0f, 0.5f);
			material->Color.g = randFloat(0.6f, 1.0f);
			material->Color.b = randFloat(0.0f, 0.3f);
			auto renderer = make_shared<Renderer>(mesh, material, Transform(vec3(randFloat(-25.0f, 25.0f), 0.0f, randFloat(-50.0f, 50.0f)), randFloat(0.75f, 1.25f)));
			scene->Renderers.push_back(renderer);
		}


		Camera = make_shared<PerspectiveCamera>();
		Camera->FOV = 45.0f / 180.0f * float(M_PI);
		Camera->Near = 0.01f;
		Camera->Far = 1000;
		Camera->transform.Position = vec3(0, 3, -100);
		scene->camera = Camera;
	}
}

string TechDemo::GetWindowName()
{
	return "Test Window";
}

#include <iostream>
void TechDemo::Update()
{
	const float speed = 15.0f;
	if (frameData->IsKeyPressed(SDLK_LEFT))
		Camera->transform.Position.x -= frameData->deltaTime * speed;
	if (frameData->IsKeyPressed(SDLK_RIGHT))
		Camera->transform.Position.x += frameData->deltaTime * speed;
	if (frameData->IsKeyPressed(SDLK_UP))
		Camera->transform.Position.z += frameData->deltaTime * speed;
	if (frameData->IsKeyPressed(SDLK_DOWN))
		Camera->transform.Position.z -= frameData->deltaTime * speed;

	auto mouseposition = frameData->GetViewMousePosition();

	if (mouseposition)
	{
		auto worldRay = Camera->GenerateRay(*mouseposition);
		auto raycast = GetScene()->Intersect(worldRay);

		if (raycast)
		{
			auto material = make_shared<Material>();
			material->Color.r = randFloat(0.5f, 1.0f);
			material->Color.g = randFloat(0.2f, 0.6f);
			material->Color.b = randFloat(0.0f, 0.3f);
			raycast->RendererHit->material = material;
		}
	}

	if (frameData->windowCloseEvent)
	{
		Stop();
	}
}