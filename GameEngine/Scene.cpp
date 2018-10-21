#include "Scene.h"

void Scene::Draw()
{
	if (!camera)return;
	auto viewMatrix = camera->GetViewMatrix();
	for (int i = 0; i < Renderers.size(); i++)
		Renderers[i]->Draw(viewMatrix);
}

shared_ptr<RayHit> Scene::Intersect(Ray& aRay)
{
	shared_ptr<RayHit> ret = nullptr;
	for (int i = 0; i < Renderers.size(); i++)
	{
		auto renderer = Renderers[i];
		auto intersection = renderer->Intersect(aRay);
		if (intersection)
		{
			intersection->RendererHit = renderer;
			if (ret)
			{
				if (ret->DirectionDistance > intersection->DirectionDistance)
					ret = intersection;
			}
			else
				ret = intersection;
		}
	}
	return ret;
}