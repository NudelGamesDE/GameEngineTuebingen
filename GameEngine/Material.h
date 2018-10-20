#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <glm\vec4.hpp>
using namespace glm;

class Material
{
public:
	vec4 Color = vec4(1.0, 1.0f, 1.0f, 1.0f);
	void Use();
};

#else
class Material;
#endif