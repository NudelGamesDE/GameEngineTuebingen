#include "PerspectiveCamera.h"

#include <cmath>
#include <glm\gtx\transform.hpp>
using namespace std;
using namespace glm;

/** \brief Returns the view matrix

\return the view matrix
*/
mat4 PerspectiveCamera::GetViewMatrix(bool* aIsInverse)
{
	*aIsInverse = true;
	return transform.GetMatrix();
}

/** \brief Returns the projection matrix

\return the projection matrix
*/
mat4 PerspectiveCamera::GetProjectionMatrix()
{
	return perspectiveLH(FOV, 4 / 3.0f, Near, Far);
}

/** \brief Generates a ray

This function returns a ray from the window coordinate into the 3D space.
\param aPosition vec2 with x and y coordinates of the screen
\return a Ray instance
*/
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