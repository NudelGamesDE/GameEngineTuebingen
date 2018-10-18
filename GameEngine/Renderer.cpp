#include "Renderer.h"

void Renderer::Draw(mat4 aViewMatrix)
{
	if (material && mesh)
	{
		material->Use();
		mesh->Draw(aViewMatrix * transform.GetMatrix());
	}
}