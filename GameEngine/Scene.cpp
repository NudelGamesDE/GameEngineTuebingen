#include "Scene.h"

/** \brief Draw scene

This function draws the scene with all its treats. It extracts the needed matrices from the camera and passes them to the renderers while calling their draw functions.
*/
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

	if (Skybox) {
		Skybox->transform = Transform();
		Skybox->getRenderer()->Draw(&viewMatrix, &inverseViewMatrix, &projection, Lights);
	}

	for (int i = 0; i < Renderers.size(); i++)
		Renderers[i]->Draw(&viewMatrix, &inverseViewMatrix, &projection, Lights);
}

/** \brief Checks for intersection

This function checks for an intersection of a ray and all renderer's meshes by calling their Intersect functions.
\param aRay an incoming ray
\return a RayHit
*/
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