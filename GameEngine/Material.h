#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <glm\vec4.hpp>
#include <glm\matrix.hpp>
#include "Texture.h"
#include "Shader.h"
#include "Light.h"
#include <memory>
using namespace glm;
using namespace std;

/**	\brief A material class

This class represents a material with its own shader, different kinds of textures (depending on the shader you use) and other lighting factors like ambient, specular and diffuse color.
Basically, everything that has to do with transmitting data to the shader happens here.
*/
class Material
{
public:
	Material();
	shared_ptr<Shader> Shader;
	shared_ptr<Texture> ColorTexture;
	shared_ptr<Texture> NormalTexture;
	shared_ptr<Texture> HeightTexture;
	shared_ptr<Texture> CubemapTexture;
	void Use(mat4* aModel, mat4* aView, mat4* aInverseView, mat4* aProjection, vector<shared_ptr<Light>> aLights);
	char *Name;
	vec3 AmbientColor;
	vec3 SpecularColor;
	vec3 DiffuseColor;
	unsigned short Illum;
	float Shininess;
	float Transparency;
};

#else
class Material;
#endif