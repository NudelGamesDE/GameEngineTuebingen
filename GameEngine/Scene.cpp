#include "Scene.h"

void Scene::Draw()
{
	if (!camera)return;
	auto viewMatrix = camera->GetViewMatrix();
	for (int i = 0; i < Renderers.size(); i++)
		Renderers[i]->Draw(viewMatrix);
}