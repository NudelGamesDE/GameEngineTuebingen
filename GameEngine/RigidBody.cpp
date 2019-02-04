#include "RigidBody.h"

/** \brief Constructor for a RigidBody instance
*/
RigidBody::RigidBody() {}

/** \brief Overloaded constructor for a RigidBody instance

\param weight a weight for the body
\param velocity a velocity for the body
*/
RigidBody::RigidBody(float weight, vec3 velocity)
{
	Weight = weight;
	Velocity = velocity;
}

/** \brief Adds a force to the rigid body

\param aForce a vec3 representing the forces direction and power
*/
void RigidBody::addForce(vec3 aForce)
{
	Velocity += aForce / Weight;
}

/** \brief Adds a velocity to the rigid body

\param aVelocity a vec3 representing a velocity and its direction
*/
void RigidBody::addVelocity(vec3 aVelocity)
{
	Velocity += aVelocity;
}