#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <glm\vec3.hpp>
#include <glm\matrix.hpp>
#include <glm\gtc\quaternion.hpp>
using namespace glm;

class Transform
{
public:
	Transform();
	Transform(vec3 aPosition);
	Transform(vec3 aPosition, float aScale);
	Transform(vec3 aPosition, vec3 aScale);
	vec3 Position;
	quat Rotation;
	vec3 Scale;
	mat4 GetMatrix();
};

#else
class Transform;
#endif