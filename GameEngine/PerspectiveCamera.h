#ifndef _PERSPECTIVECAMERA_H
#define _PERSPECTIVECAMERA_H

#include "Camera.h"

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