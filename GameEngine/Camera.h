#ifndef _CAMERA_H
#define _CAMERA_H

#include <memory>
#include <glm\matrix.hpp>
#include "Transform.h"
using namespace std;
using namespace glm;

class Camera
{
	mat4 Projection;
public:
	Transform transform;
	void MakePerspective(float aFOV, float aNear, float aFar);
	mat4 GetViewMatrix();
};
using Camera_ptr = shared_ptr<Camera>;

#else
class Camera;
#endif