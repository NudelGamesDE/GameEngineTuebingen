#include "Camera.h"

#include <glm\gtx\transform.hpp>

void Camera::MakePerspective(float aFOV, float aNear, float aFar)
{
	Projection = perspectiveLH(aFOV, 4.0f / 3.0f, aNear, aFar);
}

mat4 Camera::GetViewMatrix()
{
	return Projection * inverse(transform.GetMatrix());
}
