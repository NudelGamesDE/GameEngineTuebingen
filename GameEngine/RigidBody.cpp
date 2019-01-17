#include "RigidBody.h"

RigidBody::RigidBody() {}

RigidBody::RigidBody(float weight, vec3 velocity)
{
	Weight = weight;
	Velocity = velocity;
}

void RigidBody::addForce(vec3 aForce)
{
	Velocity += aForce / Weight;
}

void RigidBody::addVelocity(vec3 aVelocity)
{
	Velocity += aVelocity;
}