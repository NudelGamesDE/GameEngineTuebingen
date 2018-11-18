#include "Scene.h"

void Scene::Draw()
{
	if (!camera)return;
	bool isInverse;
	auto viewMatrix = camera->GetViewMatrix(&isInverse);
	auto inverseViewMatrix = viewMatrix;
	if (isInverse)
		viewMatrix = inverse(inverseViewMatrix);
	else
		inverseViewMatrix = inverse(viewMatrix);
	auto projection = camera->GetProjectionMatrix();

	for (int i = 0; i < Renderers.size(); i++)
		Renderers[i]->Draw(&viewMatrix, &inverseViewMatrix, &projection);
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