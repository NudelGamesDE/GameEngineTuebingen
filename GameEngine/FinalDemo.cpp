#include "FinalDemo.h"
#include <glm/gtc/noise.hpp>
#include "PerspectiveCamera.h"
#include <algorithm>
#include "ParticleSystem.h"

void FinalDemo::Start()
{
	auto scene = GetScene();


	terrain = make_shared<Terrain>();
	terrain->getRenderer()->transform.Scale = vec3(1, 0.2f, 1);
	terrain->getMaterial()->ColorTexture = make_shared<Texture>("../finalGround.png");
	terrain->SetMeshResolution(200);
	terrain->SetHeightResolution(64);
	terrain->SetHeightValues([](vec3 position) {return perlin(vec2(position.x, position.z) *10.0f); });
	scene->Renderers.push_back(terrain->getRenderer());

	camera = make_shared<PerspectiveCamera>();
	camera->FOV = 45.0f / 180.0f * float(M_PI);
	camera->Near = 0.1f;
	camera->Far = 1000;
	camera->transform.Position = vec3(0.5f, 0.4f, 0);
	camera->transform.Rotation = quat(vec3(0.9f, 0, 0));
	scene->camera = camera;


	vector<shared_ptr<Mesh>> capsuleObj;
	vector<shared_ptr<Material>> capsuleMtl;

	loadObj("../capsule.obj", capsuleObj, capsuleMtl, "../capsule.mtl");

	clickerMaterial = capsuleMtl[0];
	clickerMesh = capsuleObj[0];

	clickerMaterial->Shader = Shader::FlatTextured();
	clickerMaterial->DiffuseColor = vec3(1, 0.5f, 0.5f);
	//clickerMaterial->Shader = Shader::BlinnPhongTextured();
	clickerMaterial->ColorTexture = make_shared<Texture>("../GroundForest.jpg");

	BloodMaterial = make_shared<Material>();
	BloodMaterial->Shader = Shader::FlatTextured();
	BloodMaterial->ColorTexture = make_shared<Texture>("../blood.png");

	for (int i = 0; i < 4; i++) {
		auto renderer = make_shared<Renderer>();
		renderer->material = clickerMaterial;
		renderer->mesh = clickerMesh;
		renderer->transform.Scale = vec3(0.025f);
		renderer->transform.Position = vec3(0.5f, 0.05f, 0.5f);
		scene->Renderers.push_back(renderer);
		targets.push_back(renderer);
	}
	timer = 0;
}
string FinalDemo::GetWindowName()
{
	return "Kill Clicker";
}



float randFloat2(float aMin, float aMax)
{
	return (rand() % 10001) / 10000.0f*(aMax - aMin) + aMin;
}

ParticleSystem::ParticleData newParticle()
{
	ParticleSystem::ParticleData ret;
	ret.Lifetime = 0;
	ret.LocalPosition = vec3(0);
	ret.Scale = vec2(0.02f);
	ret.LocalVelocity = vec3(randFloat2(-1, 1), 4, randFloat2(-1, 1))*0.1f;
	return ret;
}

void changeParticle(float aDeltaTime, ParticleSystem::ParticleData& aParticle)
{
	aParticle.LocalVelocity.y -= aDeltaTime;
	aParticle.Lifetime += aDeltaTime;
	aParticle.LocalPosition += aParticle.LocalVelocity * aDeltaTime;
}

void FinalDemo::Update()
{
	timer += frameData->deltaTime;

	auto mouseposition = frameData->GetViewMousePosition();

	if (frameData->Mouse1Down && mouseposition)
	{
		auto worldRay = camera->GenerateRay(*mouseposition);
		auto raycast = GetScene()->Intersect(worldRay);

		if (raycast && raycast->RendererHit != terrain->getRenderer())
		{
			auto newSystem = make_shared<ParticleSystem>(GetScene(), newParticle, changeParticle);
			newSystem->Spawnfrequency = 20;
			newSystem->MaxLifetime = 2;
			newSystem->ParticleMaterial = BloodMaterial;
			newSystem->transform.Position = raycast->RendererHit->transform.Position;
			particles.push_back(newSystem);

			GetScene()->Renderers.erase(std::remove_if(GetScene()->Renderers.begin(), GetScene()->Renderers.end(), [raycast](shared_ptr<Renderer> aRenderer)
			{
				return aRenderer == raycast->RendererHit;
			}), GetScene()->Renderers.end());
		}
	}

	for (auto& particle : particles)
	{
		particle->Update(frameData->deltaTime, camera);
		particle->Spawnfrequency -= frameData->deltaTime * 4;
	}
	particles.erase(std::remove_if(particles.begin(), particles.end(), [](shared_ptr<ParticleSystem> aSystem)
	{
		if (aSystem->Spawnfrequency > -20)return false;
		aSystem->Clear();
		return true;
	}), particles.end());


	for (int i = 0; i < targets.size(); i++)
	{
		targets[i]->transform.Position.x = cos(timer*(0.5f + i)) / 4 + 0.5f;
		targets[i]->transform.Position.z = sin(timer*(0.8f + i * 0.6f)) / 4 + 0.5f;
	}

}