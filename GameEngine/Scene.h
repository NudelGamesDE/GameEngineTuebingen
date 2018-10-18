#ifndef _SCENE_H
#define _SCENE_H

#include <memory>
#include <vector>
#include "Renderer.h"
#include "Camera.h"
using namespace std;

class Scene
{
public:
	Camera_ptr camera = Camera_ptr(new Camera());
	vector<Renderer_ptr> Renderers;
	void Draw();
};
using Scene_ptr = shared_ptr<Scene>;

#else
class SCene;
#endif