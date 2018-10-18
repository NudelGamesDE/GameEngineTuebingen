#include "Scene.h"

void Scene::Draw()
{
	for (int i = 0; i < Renderers.size(); i++)
		Renderers[i]->Draw();
}