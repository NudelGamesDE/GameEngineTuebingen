#ifndef _CAMERA_H
#define _CAMERA_H

#include <glm\matrix.hpp>
#include "Transform.h"
#include "Ray.h"
using namespace glm;

class Camera
{
	mat4 Projection;
public:
	Transform transform;
	virtual mat4 GetViewMatrix() = 0;

	virtual Ray GenerateRay(vec2 aPosition) = 0;
};

#else
class Camera;
#endif