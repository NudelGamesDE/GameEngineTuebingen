#include "PerspectiveCamera.h"

#include <cmath>
#include <glm\gtx\transform.hpp>
using namespace std;
using namespace glm;

mat4 PerspectiveCamera::GetViewMatrix()
{
	auto projection = perspectiveLH(FOV, 4 / 3.0f, Near, Far);

	return projection * inverse(transform.GetMatrix());
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