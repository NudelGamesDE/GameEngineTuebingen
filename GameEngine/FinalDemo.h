#ifndef _FINALDEMO_H
#define _FINALDEMO_H
#include "Game.h"
#include "Terrain.h"
#include "PerspectiveCamera.h"
#include "ParticleSystem.h"


class FinalDemo :public Game
{
	shared_ptr<Terrain> terrain;
	shared_ptr<Material> clickerMaterial;
	shared_ptr<Mesh> clickerMesh;
	shared_ptr<PerspectiveCamera> camera;
	shared_ptr<Material> BloodMaterial;
	vector< shared_ptr<ParticleSystem>> particles;
	vector< shared_ptr<Renderer>> targets;
	float timer;
public:
	virtual void Start();
	string GetWindowName();
	virtual void Update();
};

#else
class FinalDemo;
#endif