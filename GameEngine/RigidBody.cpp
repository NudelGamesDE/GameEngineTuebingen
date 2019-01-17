#include "RigidBody.h"

RigidBody::RigidBody() {}

RigidBody::RigidBody(float weight, vec3 velocity)
{
	Weight = weight;
	Velocity = velocity;
}