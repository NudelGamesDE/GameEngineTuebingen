#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/glm.hpp>
using namespace glm;

class RigidBody
{
public:
	RigidBody();
	RigidBody(float weight, vec3 velocity);
	float Weight;
	vec3 Velocity;
};
#else
class RigidBody;
#endif