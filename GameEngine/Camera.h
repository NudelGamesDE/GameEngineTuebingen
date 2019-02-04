#ifndef _CAMERA_H
#define _CAMERA_H

#include <glm\matrix.hpp>
#include "Transform.h"
#include "Ray.h"
using namespace glm;

/** \brief A camera class

The Camera class is a container for the projection matrix and the camera position.
Also, the camera generates the ray for raycasting.
*/
class Camera
{
	mat4 Projection;
public:
	Transform transform;
	virtual mat4 GetViewMatrix(bool* aIsInverse) = 0;
	virtual mat4 GetProjectionMatrix() = 0;

	virtual Ray GenerateRay(vec2 aPosition) = 0;
};

#else
class Camera;
#endif