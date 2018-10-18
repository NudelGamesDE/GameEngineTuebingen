#include "Transform.h"

#include <glm/gtx/transform.hpp>

Transform::Transform()
{
	Scale = vec3(1.0f);
}

Transform::Transform(vec3 aPosition)
{
	Position = aPosition;
	Scale = vec3(1.0f);
}

Transform::Transform(vec3 aPosition, float aScale)
{
	Position = aPosition;
	Scale = vec3(aScale);
}

Transform::Transform(vec3 aPosition, vec3 aScale)
{
	Position = aPosition;
	Scale = aScale;
}

mat4 Transform::GetMatrix()
{
	return translate(Position) * scale(Scale);
}
