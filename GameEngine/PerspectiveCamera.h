#ifndef _PERSPECTIVECAMERA_H
#define _PERSPECTIVECAMERA_H

#include "Camera.h"

/** \brief A perspective camera class

This class implements a perspective camera, getting its name from the perspective projection matrix (another one would be the orthogonal projection matrix).
This class inherits its traits from the Camera class.
*/
class PerspectiveCamera :public Camera
{
	float Ratio = 4 / 3.0f;
public:
	float FOV;
	float Near;
	float Far;
	virtual mat4 GetViewMatrix(bool* aIsInverse);
	virtual mat4 GetProjectionMatrix();
	Ray GenerateRay(vec2 aPosition);
};

#else
class PerspectiveCamera;
#endif