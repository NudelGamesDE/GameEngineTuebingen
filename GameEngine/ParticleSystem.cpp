#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(shared_ptr<Scene> aScene,
	function<ParticleData()> aNewParticle,
	function<void(float, ParticleData&)> aModifyParticle)
{
	scene = aScene;
	newParticle = aNewParticle;
	modifyParticle = aModifyParticle;
}

void ParticleSystem::Update(float aDeltaTime)
{
	if (!scene)return;
}

