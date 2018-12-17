#ifndef _SCENE_H
#define _SCENE_H

#include <memory>
#include <vector>
#include "Renderer.h"
#include "Camera.h"
#include "Ray.h"
#include "RayHit.h"
#include "Light.h"
#include "Skybox.h"
using namespace std;

class Scene
{
public:
	shared_ptr<Camera> camera;
	vector<shared_ptr<Renderer>> Renderers;
	vector<shared_ptr<Light>> Lights;
	shared_ptr<Skybox> Skybox;
	void Draw();
	shared_ptr<RayHit> Intersect(Ray& aRay);
};

#else
class SCene;
#endif