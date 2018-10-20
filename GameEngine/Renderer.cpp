#include "Renderer.h"

Renderer::Renderer() {}

Renderer::Renderer(shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial, Transform aTransform)
{
	mesh = aMesh;
	material = aMaterial;
	transform = aTransform;
}

void Renderer::Draw(mat4 aViewMatrix)
{
	if (material && mesh)
	{
		material->Use();
		auto test = transform.GetMatrix();
		mesh->Draw(aViewMatrix * transform.GetMatrix());
	}
}

shared_ptr<RayHit> Renderer::Intersect(Ray& aRay)
{
	if (!mesh)return nullptr;

	auto transformationMatrix = transform.GetMatrix();
	auto inverseTransformationMatrix = inverse(transformationMatrix);

	auto transformedRay = aRay;

	transformedRay.Origin = inverseTransformationMatrix * vec4(transformedRay.Origin, 1);
	transformedRay.Direction = inverseTransformationMatrix * vec4(transformedRay.Direction, 0);

	return mesh->Intersect(transformedRay);
}
