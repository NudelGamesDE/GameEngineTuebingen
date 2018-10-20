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
		auto intersection = Renderers[i]->Intersect(aRay);
		if (intersection)
		{
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