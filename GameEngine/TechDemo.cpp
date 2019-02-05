#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL_keycode.h>
#include "glm\gtc\quaternion.hpp"
#include "TechDemo.h"
#include "PerspectiveCamera.h"
#include "objLoader.h"
#include <iostream>
#include <glm/gtc/noise.hpp>
using namespace std;
using namespace glm;

shared_ptr<Mesh> GenerateTreeMesh()
{
	auto positions = vector<vec3>();
	auto uvs = vector<vec2>();
	auto normals = vector<vec3>();

	auto segments = 8;
	auto angle = (float)M_PI / segments;
	auto rotation = quat(cos(angle), 0, sin(angle), 0);
	auto rotationCon = conjugate(rotation);

	auto rotate = [rotation, rotationCon](vec3 aPoint)
	{
		auto ret = rotationCon * quat(0, aPoint.x, aPoint.y, aPoint.z) * rotation;
		return vec3(ret.x, ret.y, ret.z);
	};

	auto addSegment = [rotate, segments, &positions, &uvs, &normals](vec3 aTop, vec3 aSide)
	{
		for (auto i = 0; i < segments; i++)
		{
			auto nextSide = rotate(aSide);
			auto normal = normalize(cross(nextSide - aTop, aSide - aTop));
			positions.push_back(aTop);
			positions.push_back(aSide);
			positions.push_back(nextSide);
			uvs.push_back(vec2(0, 1));
			uvs.push_back(vec2(float(i) / segments, 0));
			uvs.push_back(vec2(float(i + 1) / segments, 0));
			normals.push_back(normal);
			normals.push_back(normal);
			normals.push_back(normal);
			aSide = nextSide;
		}
	};

	addSegment(vec3(0, 1, 0), vec3(0.25f, 0.75f, 0));
	addSegment(vec3(0, 1, 0), vec3(0.4f, 0.5f, 0));
	addSegment(vec3(0, 1, 0), vec3(0.5f, 0.25f, 0));
	addSegment(vec3(0, 1, 0), vec3(0.1f, 0, 0));

	return make_shared<Mesh>(positions, uvs, normals);
}

shared_ptr<Shader> GenerateTreeShader()
{
	return make_shared<Shader>(
		"out vec3 VNormal;"

		"void main()"
		"{"
		"	gl_Position = Projection * View * Model * vec4(position, 1.0);"

		"	VNormal = (Model * vec4(normal, 0.0)).xyz;"
		"}",


		"in vec3 VNormal;"

		"void main()"
		"{"
		"	vec3 toLight = normalize(vec3(0.5, 1.0, 0.0));"
		"	vec3 unitNormal = normalize(VNormal + vec3(0.0, 0.01, 0.0));"
		"	float brightness = dot(toLight, unitNormal);"
		"	ColorOut = vec4(DiffuseColor * max(brightness, 0.2), 1.0);"
		"}");
}

shared_ptr<Texture> GenerateWoodTexture()
{
	return make_shared<Texture>("../WoodFlooring.jpg");
}


void CalcBigTree(shared_ptr<SceneGraphNode> aBigTree, float& aTimer)
{
	aBigTree->localTransform.Position = vec3(-5, 0, cos(aTimer / 4) * 5 - 15);
	aBigTree->localTransform.Scale = vec3(sin(aTimer * 2), cos(aTimer * 2), sin(aTimer * 2)) * 2.0f + vec3(8);
	aBigTree->localTransform.Rotation = quat(cos(aTimer * 3), 0, sin(aTimer * 3), 0);
	aBigTree->update(aTimer);
}


float randFloat(float aMin, float aMax)
{
	return (rand() % 10001) / 10000.0f*(aMax - aMin) + aMin;
}

shared_ptr<Skybox> GenerateSkybox()
{
	const char* posx = "../posx.jpg";
	const char* negx = "../negx.jpg";
	const char* posy = "../posy.jpg";
	const char* negy = "../negy.jpg";
	const char* posz = "../posz.jpg";
	const char* negz = "../negz.jpg";
	return make_shared<Skybox>(posx, negx, posy, negy, posz, negz);
}

shared_ptr<SceneGraphNode> GenerateSceneGraphRoot()
{
	auto mesh = GenerateTreeMesh();
	auto bigTreeMaterial = make_shared<Material>();
	bigTreeMaterial->Shader = Shader::BlinnPhongTextured();
	bigTreeMaterial->ColorTexture = make_shared<Texture>("../GroundForest.jpg");
	bigTreeMaterial->DiffuseColor = vec3(1);
	bigTreeMaterial->SpecularColor = vec3(1);
	bigTreeMaterial->AmbientColor = vec3(0.3f, 0.1f, 0.1f);
	return make_shared<SceneGraphNode>(mesh, bigTreeMaterial, Transform(vec4(0.0f), 10.0f));
}

shared_ptr<Terrain> GenerateTerrain()
{
	auto ret = make_shared<Terrain>();
	ret->getRenderer()->transform.Position = vec3(-50, -5, -50);
	ret->getRenderer()->transform.Scale = vec3(100, 20, 100);
	ret->getMaterial()->ColorTexture = make_shared<Texture>("../GroundForest.jpg");
	ret->SetMeshResolution(200);
	ret->SetHeightResolution(128);
	ret->SetHeightValues([](vec3 position) {return perlin(vec2(position.x, position.z) / 10.0f); });
	return ret;
}

vector<vec3> TreePositions;

ParticleSystem::ParticleData NewParticle()
{
	ParticleSystem::ParticleData ret;
	ret.Lifetime = 0;
	ret.LocalPosition = vec3(0);
	ret.Scale = vec2(1);
	ret.LocalVelocity = vec3(randFloat(-1, 1), randFloat(-1, 1), randFloat(-1, 1));
	return ret;
}

void ChangeParticle(float aDeltaTime, ParticleSystem::ParticleData& aParticle)
{
	aParticle.Lifetime += aDeltaTime;
	aParticle.LocalPosition += aParticle.LocalVelocity * aDeltaTime;
}

shared_ptr<ParticleSystem> GenerateParticleSystem(shared_ptr<Scene> aScene)
{
	auto ret = make_shared<ParticleSystem>(aScene, NewParticle, ChangeParticle);
	ret->MaxLifetime = 5;
	ret->Spawnfrequency = 10;
	ret->ParticleMaterial = make_shared<Material>();
	ret->ParticleMaterial->Shader = Shader::FlatTextured();
	ret->ParticleMaterial->ColorTexture = make_shared<Texture>("../testParticle.png");
	ret->transform.Position = vec3(0, 1, 3);
	return ret;
}

void TechDemo::Start()
{
	WoodTexture = GenerateWoodTexture();
	auto scene = GetScene();
	if (scene)
	{
		auto mesh = GenerateTreeMesh();
		auto shader = GenerateTreeShader();

		scene->Skybox = GenerateSkybox();

		BigTree = GenerateSceneGraphRoot();
		TestTerrain = GenerateTerrain();
		scene->Renderers.push_back(TestTerrain->getRenderer());

		auto light = make_shared<Light>(vec3(), vec3(1), vec3(-0.5f, -1.0f, 0), 0);
		scene->Lights.push_back(light);

		for (int i = 0; i < 200; i++)
		{
			auto material = make_shared<Material>();
			material->Shader = shader;
			material->DiffuseColor.r = randFloat(0.0f, 0.5f);
			material->DiffuseColor.g = randFloat(0.6f, 1.0f);
			material->DiffuseColor.b = randFloat(0.0f, 0.3f);
			auto renderer = make_shared<Renderer>(mesh, material, Transform(vec3(randFloat(-25.0f, 25.0f), 0.0f, randFloat(-50.0f, 50.0f)), randFloat(0.75f, 1.25f)));
			TreePositions.push_back(renderer->transform.Position);
			scene->Renderers.push_back(renderer);
		}

		vector<shared_ptr<Mesh>> capsuleObj;
		vector<shared_ptr<Material>> capsuleMtl;

		loadObj("../capsule.obj", capsuleObj, capsuleMtl, "../capsule.mtl");

		rig = make_shared<RigidBody>();

		for (int i = 0; i < capsuleObj.size(); i++) {
			capsuleMtl[i]->Shader = Shader::BlinnPhongTextured();
			capsuleMtl[i]->ColorTexture = make_shared<Texture>("../GroundForest.jpg");
			auto node = make_shared<SceneGraphNode>(capsuleObj[i], capsuleMtl[i], Transform(vec3(0.5, 3, 0)));
			node->renderer->rigidBody = rig;
			BigTree->addChild(node);
		}

		Camera = make_shared<PerspectiveCamera>();
		Camera->FOV = 45.0f / 180.0f * float(M_PI);
		Camera->Near = 0.1f;
		Camera->Far = 1000;
		Camera->transform.Position = vec3(0, 3, -100);
		scene->camera = Camera;

		BigTree->getRenderers(scene);

		Particles = GenerateParticleSystem(scene);
	}
	Timer = 0.0f;
	CalcBigTree(BigTree, Timer);
	the_woot = make_shared<bvh::bvh_nope*>(bvh::initialise_bvh(*scene));
}

string TechDemo::GetWindowName()
{
	return "Test Window";
}

#include <iostream>
void TechDemo::Update()
{
	const float speed = 15.0f;
	const float rotationSpeed = 0.5f;
	if (frameData->IsKeyPressed(SDLK_LEFT) || frameData->IsKeyPressed(SDLK_a))
		Camera->transform.Position.x -= frameData->deltaTime * speed;
	if (frameData->IsKeyPressed(SDLK_RIGHT) || frameData->IsKeyPressed(SDLK_d))
		Camera->transform.Position.x += frameData->deltaTime * speed;
	if (frameData->IsKeyPressed(SDLK_UP) || frameData->IsKeyPressed(SDLK_w))
		Camera->transform.Position.z += frameData->deltaTime * speed;
	if (frameData->IsKeyPressed(SDLK_DOWN) || frameData->IsKeyPressed(SDLK_s))
		Camera->transform.Position.z -= frameData->deltaTime * speed;
	if (frameData->IsKeyPressed(SDLK_q))
		Camera->transform.Rotation *= quat(vec3(0, -frameData->deltaTime * rotationSpeed, 0));
	if (frameData->IsKeyPressed(SDLK_e))
		Camera->transform.Rotation *= quat(vec3(0, frameData->deltaTime * rotationSpeed, 0));

	if (frameData->IsKeyDown(SDLK_t))
	{
		TestTerrain->ChangeHeightValues([](vec3 position, float previous)
		{
			float radius = 2;
			auto minDistance = radius;

			for (auto& tree : TreePositions)
			{
				auto delta = position - tree;
				delta.y = 0;
				minDistance = min(minDistance, length(delta));
			}
			minDistance /= radius;

			return previous * minDistance + 0.25f * (1 - minDistance);
		});
	}

	auto mouseposition = frameData->GetViewMousePosition();

	if (mouseposition)
	{
		auto worldRay = Camera->GenerateRay(*mouseposition);
		auto raycast = GetScene()->Intersect(worldRay);

		if (raycast)
		{
			auto material = make_shared<Material>();
			material->DiffuseColor.r = randFloat(0.7f, 1);
			material->DiffuseColor.g = randFloat(0.7f, 1);
			material->DiffuseColor.b = randFloat(0.7f, 1);
			material->ColorTexture = WoodTexture;
			material->Shader = Shader::FlatTextured();
			raycast->RendererHit->material = material;
		}
	}

	if (frameData->windowCloseEvent)
	{
		Stop();
	}
	Timer += frameData->deltaTime;
	CalcBigTree(BigTree, Timer);
	rig->addForce(force);

	Particles->Update(frameData->deltaTime, Camera);
}