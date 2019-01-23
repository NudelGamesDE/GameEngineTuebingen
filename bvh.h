#ifndef _BVH_H
#define _BVH_H

#include <iostream>
#include <limits>
#include <cmath>
#include "Scene.h"

using namespace std;
using namespace glm;

class bvh
{
public:
	struct bvh_nope
	{
		int max_x;
		int max_y;
		int max_z;
		int min_x;
		int min_y;
		int min_z;
		vector<shared_ptr<Renderer>> objects;
		bvh_nope *left;
		bvh_nope *right;
	};
	
	static bvh::bvh_nope* initialise_bvh(Scene the_scene);
	static bvh_nope* generate_bvh_tree(vector<shared_ptr<Renderer>> objects);
	static bvh_nope* generate_bvh_nope(int x, int y, int z, int nx, int ny, int nz, vector<shared_ptr<Renderer>> obj, bvh_nope *l, bvh_nope *r);
	static float difference(float x, float y);
};

#endif