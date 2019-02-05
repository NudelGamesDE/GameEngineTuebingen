#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/glm.hpp>
using namespace glm;

/** \brief A rigid body class

This class implements a rigid body with its own weight and velocity. A force can be added to the body as well as a velocity.
*/
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