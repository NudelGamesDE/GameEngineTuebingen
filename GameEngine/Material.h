#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <glm\vec4.hpp>
#include <glm\matrix.hpp>
#include "Texture.h"
#include "Shader.h"
#include <memory>
using namespace glm;
using namespace std;

class Material
{
public:
	shared_ptr<Shader> Shader;
	shared_ptr<Texture> ColorTexture;
	shared_ptr<Texture> NormalTexture;
	void Use(mat4* aModel, mat4* aView, mat4* aInverseView, mat4* aProjection);
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