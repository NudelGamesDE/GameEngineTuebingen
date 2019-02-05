#include <GL\glew.h>
#include "Material.h"

/** \brief Binds a texture

\param aTexture a shared pointer to the texture to be used
\param aTexturCount an integer with the unique number of the texture
\param aName a string representing a uniform value in the shader
\param aShader a shader that has to get the uniform value
*/
void BindTexture(shared_ptr<Texture> aTexture, int& aTextureCount, string aName, shared_ptr<Shader> aShader)
{
	aShader->Uniform1i(aName, aTextureCount);
	glActiveTexture(GL_TEXTURE0 + aTextureCount);
	aTexture->Use();
	aTextureCount++;
}

/**	\brief Constructor for a Material instance
*/
Material::Material()
{
	DiffuseColor = vec3(1);
	SpecularColor = vec3(1);
}

/** \brief Use material

Using the material, meaning binding shaders and textures and sending important data and light information to the shader.
\param aModel a model matrix to use in shader
\param aView a view matrix to use in shader
\param aInverseView a inverse view matrix to use in shader
\param aProjection a projection matrix to use in shader
\param aLights a Light vector containing the lights that have to be considered in the shader
*/
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