#ifndef _COLLISION_H
#define _COLLISION_H

#include "bvh.h"

using namespace std;
using namespace glm;

/** \brief A collision class

This class represents a collision.
*/

class collision
{
public:
	vector<shared_ptr<Renderer>> check_for_collision(vec4 coordinates, bvh::bvh_nope* nope);

};

#endif
