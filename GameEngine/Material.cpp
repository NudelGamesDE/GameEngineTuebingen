#include <GL\glew.h>
#include "Material.h"


void Material::Use(mat4* aModel, mat4* aView, mat4* aInverseView, mat4* aProjection)
{
	if (!Shader)return;
	Shader->Bind();

	Shader->Uniform4f("Color", Color);
	Shader->UniformMat4("Model", *aModel);
	Shader->UniformMat4("View", *aView);
	Shader->UniformMat4("InverseView", *aInverseView);
	Shader->UniformMat4("Projection", *aProjection);
}