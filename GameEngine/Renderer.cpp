#include "Renderer.h"

Renderer::Renderer() {}

Renderer::Renderer(shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial, Transform aTransform) :Renderer()
{
	mesh = aMesh;
	material = aMaterial;
	transform = aTransform;
	secondTransform = mat4(1.0f);
}

Renderer::Renderer(shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial, Transform aLocalTransform, mat4 aWorldTransform) :Renderer()
{
	mesh = aMesh;
	material = aMaterial;
	transform = aLocalTransform;
	secondTransform = aWorldTransform;
}


void Renderer::Draw(mat4* aView, mat4* aInverseView, mat4* aProjection, vector<shared_ptr<Light>> aLights)
{

	if (material && mesh)
	{
		auto model = secondTransform * transform.GetMatrix();

		material->Use(&model, aView, aInverseView, aProjection, aLights);
		mesh->Draw();
	}
}
	


shared_ptr<RayHit> Renderer::Intersect(Ray& aRay)
{
	if (!mesh)return nullptr;

	auto transformationMatrix = secondTransform * transform.GetMatrix();
	auto inverseTransformationMatrix = inverse(transformationMatrix);

	auto transformedRay = aRay;

	transformedRay.Origin = inverseTransformationMatrix * vec4(transformedRay.Origin, 1);
	transformedRay.Direction = inverseTransformationMatrix * vec4(transformedRay.Direction, 0);

	return mesh->Intersect(transformedRay);
}
