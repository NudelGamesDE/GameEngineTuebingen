#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <glm\vec4.hpp>
#include "Texture.h"
#include <memory>
using namespace glm;
using namespace std;

class Material
{
public:
	shared_ptr<Texture> ColorTexture;
	shared_ptr<Texture> NormalTexture;
	vec4 Color = vec4(1.0, 1.0f, 1.0f, 1.0f);
	char *Name;
	vec3 AmbientColor;
	vec3 SpecularColor;
	vec3 DiffuseColor;
	unsigned short Illum;
	float Shininess;
	float Transparency;
	void Use();
};

#else
class Material;
#endif