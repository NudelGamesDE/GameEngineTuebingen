#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <memory>
#include <glm\vec4.hpp>
using namespace std;
using namespace glm;

class Material
{
public:
	vec4 Color = vec4(1.0, 1.0f, 1.0f, 1.0f);
	void Use();
};
using Material_ptr = shared_ptr<Material>;

#else
class Material;
#endif