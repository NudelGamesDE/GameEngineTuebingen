#ifndef _PARTICLESYSTEM_H
#define _PARTICLESYSTEM_H

#include <functional>
#include "Transform.h"
#include "Scene.h"

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
	shared_ptr<Scene> scene;
	function<ParticleData()> newParticle;
	function<void(float, ParticleData&)> modifyParticle;
public:


	ParticleSystem(shared_ptr<Scene> aScene,
		function<ParticleData()> aNewParticle,
		function<void(float, ParticleData&)> aModifyParticle);
	Transform transform;
	void Update(float aDeltaTime);
};

#else
class ParticleSystem;
#endif