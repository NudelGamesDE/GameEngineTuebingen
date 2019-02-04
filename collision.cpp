#include "collision.h"

/** \brief Checks for collision with bvh

\param coordinates a vec4 of coordinates
\param nope a bvh node
*/
vector<shared_ptr<Renderer>> collision::check_for_collision(vec4 coordinates, bvh::bvh_nope* nope)
{
	if ((nope->min_x < coordinates.x) && (coordinates.x < nope->max_x) &&
		(nope->min_y < coordinates.y) && (coordinates.y < nope->max_y) && 
		(nope->min_z < coordinates.z) && (coordinates.z < nope->max_z))
	{
		if (nope->left == NULL && nope->right == NULL)
		{
			return nope->objects;
		}
		return check_for_collision(coordinates, nope->left);
		return check_for_collision(coordinates, nope->right);
	}
	else
	{
		vector<shared_ptr<Renderer>> no_collision;
		return no_collision;
	}
}
