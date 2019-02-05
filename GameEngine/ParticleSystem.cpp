#include "ParticleSystem.h"
#include <algorithm>

/** \brief Constructor for a ParticleSystem instance

\param aScene a scene to draw the particle system to
\param aNewParticle a new paricle
\param aModifyParticle a value to modify particles
*/
ParticleSystem::ParticleSystem(shared_ptr<Scene> aScene,
	function<ParticleData()> aNewParticle,
	function<void(float, ParticleData&)> aModifyParticle)
{
	scene = aScene;
	newParticle = aNewParticle;
	modifyParticle = aModifyParticle;
}

shared_ptr<Mesh> cachedMesh;

/** \brief Generates a square Mesh

\return a shared pointer to the mesh
*/
shared_ptr<Mesh> GenerateMesh()
{
	if (!cachedMesh) {
		vector<vec3> positions, normals;
		vector<vec2> coords;
		positions.push_back(vec3(-1, -1, 0)*0.5f);
		positions.push_back(vec3(1, -1, 0)*0.5f);
		positions.push_back(vec3(1, 1, 0)*0.5f);
		positions.push_back(vec3(-1, -1, 0)*0.5f);
		positions.push_back(vec3(1, 1, 0)*0.5f);
		positions.push_back(vec3(-1, 1, 0)*0.5f);
		for (int i = 0; i < 6; i++)
			normals.push_back(vec3(0, 0, -1));
		coords.push_back(vec2(0, 1));
		coords.push_back(vec2(1, 1));
		coords.push_back(vec2(1, 0));
		coords.push_back(vec2(0, 1));
		coords.push_back(vec2(1, 0));
		coords.push_back(vec2(0, 0));
		cachedMesh = make_shared<Mesh>(positions, coords, normals);
	}
	return cachedMesh;
}

#include<iostream>
/** \brief Spawn particles
*/
void ParticleSystem::Spawn()
{
	if (!scene)return;
	if (int(Particles.size()) >= MaxParticles)return;

	Particle particle;
	particle.data = newParticle();
	particle.renderer = make_shared<Renderer>();
	particle.renderer->mesh = GenerateMesh();
	scene->Renderers.push_back(particle.renderer);
	Particles.push_back(particle);
}

/** \brief Update particle System

\param aDeltaTime a timer for timing
\param aCamera a camera for getting matrices
*/
void ParticleSystem::Update(float aDeltaTime, shared_ptr<Camera> aCamera)
{
	if (!scene)return;


	SpawnTimer += aDeltaTime * Spawnfrequency;
	while (SpawnTimer >= 1.0f)
	{
		SpawnTimer--;
		Spawn();
	}

	auto transformMatrix = transform.GetMatrix();
	auto rotation = !aCamera ? quat(1, 0, 0, 0) : aCamera->transform.Rotation;
	for (auto particle = Particles.begin(); particle < Particles.end(); particle++)
	{
		auto data = particle->data;
		modifyParticle(aDeltaTime, data);
		particle->data = data;
		particle->renderer->transform.Position = transformMatrix * vec4(data.LocalPosition, 1);
		particle->renderer->transform.Scale = vec3(data.Scale, 1);
		particle->renderer->transform.Rotation = rotation;
		particle->renderer->material = ParticleMaterial;
	}

	Particles.erase(std::remove_if(Particles.begin(), Particles.end(), [this](Particle aParticle)
	{
		if (aParticle.data.Lifetime < MaxLifetime)return false;
		scene->Renderers.erase(std::remove_if(scene->Renderers.begin(), scene->Renderers.end(), [this, aParticle](shared_ptr<Renderer> aRenderer) {return aRenderer == aParticle.renderer; }), scene->Renderers.end());
		return true;
	}), Particles.end());
}

/** \brief Clear particle system
*/
void ParticleSystem::Clear()
{
	Particles.erase(std::remove_if(Particles.begin(), Particles.end(), [this](Particle aParticle)
	{
		scene->Renderers.erase(std::remove_if(scene->Renderers.begin(), scene->Renderers.end(), [this, aParticle](shared_ptr<Renderer> aRenderer) {return aRenderer == aParticle.renderer; }), scene->Renderers.end());
		return true;
	}), Particles.end());
}

