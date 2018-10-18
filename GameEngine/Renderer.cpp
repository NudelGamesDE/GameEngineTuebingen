#include "Renderer.h"

Renderer::Renderer() {}

Renderer::Renderer(Mesh_ptr aMesh, Material_ptr aMaterial, Transform aTransform)
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