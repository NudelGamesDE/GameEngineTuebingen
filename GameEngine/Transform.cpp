#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform()
{
	Scale = vec3(1.0f);
	Rotation = quat(1, 0, 0, 0);
}

Transform::Transform(vec3 aPosition) :Transform()
{
	Position = aPosition;
}

Transform::Transform(vec3 aPosition, float aScale) :Transform()
{
	Position = aPosition;
	Scale = vec3(aScale);
}

Transform::Transform(vec3 aPosition, vec3 aScale) :Transform()
{
	Position = aPosition;
	Scale = aScale;
}

mat4 Transform::GetMatrix()
{
	return translate(mat4(1), Position) * (mat4)Rotation * scale(mat4(1), Scale);
}
