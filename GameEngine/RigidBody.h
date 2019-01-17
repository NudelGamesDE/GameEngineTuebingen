#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/glm.hpp>
using namespace glm;

class RigidBody
{
public:
	RigidBody();
	RigidBody(float weight, vec3 velocity);
	float Weight = 1.0f;
	vec3 Velocity = vec3(0.0f);
	void addForce(vec3 aForce);
	void addVelocity(vec3 aVelocity);
};
#else
class RigidBody;
#endif