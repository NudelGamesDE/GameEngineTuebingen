#include <GL\glew.h>
#include "Material.h"

void BindTexture(shared_ptr<Texture> aTexture, int& aTextureCount, string aName, shared_ptr<Shader> aShader)
{
	aShader->Uniform1i(aName, aTextureCount);
	glActiveTexture(GL_TEXTURE0 + aTextureCount);
	aTexture->Use();
	aTextureCount++;
}

Material::Material()
{
	DiffuseColor = vec3(1);
	SpecularColor = vec3(1);
}

void Material::Use(mat4* aModel, mat4* aView, mat4* aInverseView, mat4* aProjection, vector<shared_ptr<Light>> aLights)
{
	if (!Shader)return;
	Shader->Bind();

	Shader->Uniform3f("DiffuseColor", DiffuseColor);
	Shader->Uniform3f("SpecularColor", SpecularColor);
	Shader->Uniform3f("AmbientColor", AmbientColor);
	Shader->UniformMat4("Model", *aModel);
	Shader->UniformMat4("View", *aView);
	Shader->UniformMat4("InverseView", *aInverseView);
	Shader->UniformMat4("Projection", *aProjection);

	auto TextureCount = 0;
	if (ColorTexture)BindTexture(ColorTexture, TextureCount, "ColorTexture", Shader);
	if (NormalTexture)BindTexture(NormalTexture, TextureCount, "NormalTexture", Shader);
	if (HeightTexture)BindTexture(HeightTexture, TextureCount, "HeightTexture", Shader);
	if (CubemapTexture)BindTexture(CubemapTexture, TextureCount, "CubemapTexture", Shader);
	
	//this is how you transfer you light data, direction is director from the light
	vector<vec3> positions, colors, directions;
	vector<int> types;
	//positions.push_back(vec3());
	//colors.push_back(vec3(1));
	//directions.push_back(normalize(vec3(-0.5f,-1.0f,0)));//needs to be normalized
	//types.push_back(0);//0: directional, 1 point, 2 spotlight(not implemented)

	for (int i = 0; i < aLights.size(); i++) {
		positions.push_back(aLights[i]->Position);
		colors.push_back(aLights[i]->Color);
		directions.push_back(normalize(aLights[i]->Direction));//needs to be normalized
		types.push_back(aLights[i]->Type);//0: directional, 1 point, 2 spotlight(not implemented)
	}
	Shader->UniformLights(positions, colors, directions, types);
}