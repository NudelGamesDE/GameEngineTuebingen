#ifndef _MESH_H
#define _MESH_H

#include <memory>
#include <vector>
#include <glm\vec3.hpp>
using namespace std;
using namespace glm;

class Mesh
{
public:
	vector<vec3> Vertices;
	void Draw();
};
using Mesh_ptr = shared_ptr<Mesh>;

#else
class Mesh;
#endif