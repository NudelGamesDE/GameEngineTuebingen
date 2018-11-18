#include "PerspectiveCamera.h"

#include <cmath>
#include <glm\gtx\transform.hpp>
using namespace std;
using namespace glm;

mat4 PerspectiveCamera::GetViewMatrix(bool* aIsInverse)
{
	*aIsInverse = true;
	return transform.GetMatrix();
}
mat4 PerspectiveCamera::GetProjectionMatrix()
{
	return perspectiveLH(FOV, 4 / 3.0f, Near, Far);
}
Ray PerspectiveCamera::GenerateRay(vec2 aPosition)
{
	auto ret = Ray();
	ret.Min = Near;
	ret.Max = Far;
	ret.Origin = transform.Position;

	auto transformMatrix = transform.GetMatrix();
	auto tanFOV = tanf(FOV * 0.5f);

	auto direction = vec3(aPosition.x * Ratio, aPosition.y, 0)*tanFOV + vec3(0, 0, 1);
	ret.Direction = transformMatrix * vec4(direction, 0);

	return ret;
}