#ifndef _MESH_H
#define _MESH_H

#include <memory>
#include <vector>
#include <glm\vec3.hpp>
#include <glm\matrix.hpp>
#include "Ray.h"
#include "RayHit.h"
using namespace std;
using namespace glm;

class Mesh
{
public:
	vector<vec3> Vertices;
	void Draw(mat4 aModelViewMatrix);
	shared_ptr<RayHit> Intersect(Ray& aRay);
};

#else
class Mesh;
#endif