#ifndef _MESH_H
#define _MESH_H

#include <memory>
#include <vector>
#include <glm\vec3.hpp>
#include <glm\matrix.hpp>
using namespace std;
using namespace glm;

class Mesh
{
public:
	vector<vec3> Vertices;
	void Draw(mat4 aModelViewMatrix);
};
using Mesh_ptr = shared_ptr<Mesh>;

#else
class Mesh;
#endif