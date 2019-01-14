#ifndef _TECHDEMO_H
#define _TECHDEMO_H

#include <string>
#include <memory>
#include "Game.h"
#include "PerspectiveCamera.h"
#include "SceneGraphNode.h"
#include "Terrain.h"
using namespace std;

class TechDemo :public Game
{
	shared_ptr<Texture> WoodTexture;
	shared_ptr<PerspectiveCamera> Camera;
	shared_ptr<SceneGraphNode> BigTree;
	shared_ptr<Terrain> TestTerrain;
	float Timer;
public:
	virtual void Start();
	string GetWindowName();
	virtual void Update();
};

#else
class TechDemo;
#endif