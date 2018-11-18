#include "Renderer.h"

Renderer::Renderer() {}

Renderer::Renderer(shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial, Transform aTransform)
{
	mesh = aMesh;
	material = aMaterial;
	transform = aTransform;
}

void Renderer::Draw(mat4* aView, mat4* aInverseView, mat4* aProjection)
{
	if (material && mesh)
	{
		auto model = transform.GetMatrix();
		material->Use(&model, aView, aInverseView, aProjection);
		mesh->Draw();
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
