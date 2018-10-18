#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <glm\vec3.hpp>
#include <glm\matrix.hpp>
using namespace glm;

class Transform
{
public:
	vec3 Position;
	mat4 GetMatrix();
};

#else
class Transform;
#endif