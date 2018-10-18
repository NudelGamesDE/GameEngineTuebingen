#include "Transform.h"

#include <glm/gtx/transform.hpp>

mat4 Transform::GetMatrix()
{
	return translate(Position);
}
