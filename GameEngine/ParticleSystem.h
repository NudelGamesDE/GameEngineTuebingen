#ifndef _PARTICLESYSTEM_H
#define _PARTICLESYSTEM_H

#include <functional>
#include "Transform.h"
#include "Scene.h"

/**	\brief A Particle System class

This class Generates, changes and destroys Billboards in the specified way. The Billboards with allways be rotated towards the camera
*/
class ParticleSystem
{
public:
	struct ParticleData
	{
		vec3 LocalPosition;
		vec2 Scale;
		vec3 LocalVelocity;
		float Lifetime;
	};
private:
	struct Particle
	{
		ParticleData data;
		shared_ptr<Renderer> renderer;
	};
	shared_ptr<Scene> scene;
	function<ParticleData()> newParticle;
	function<void(float, ParticleData&)> modifyParticle;
	float SpawnTimer = 0.0f;
	vector<Particle> Particles;
public:
	ParticleSystem(shared_ptr<Scene> aScene,
		function<ParticleData()> aNewParticle,
		function<void(float, ParticleData&)> aModifyParticle);
	void Spawn();
	Transform transform;
	shared_ptr<Material> ParticleMaterial;
	int MaxParticles = 100;
	float MaxLifetime = 1.0f;
	float Spawnfrequency = 1.0f;
	void Update(float aDeltaTime, shared_ptr<Camera> aCamera);
	void Clear();
};

#else
class ParticleSystem;
#endif