#include "Camera.h"

#include <glm\gtx\transform.hpp>

mat4 Camera::GetViewMatrix()
{
	return Perspective * inverse(transform.GetMatrix());
}
