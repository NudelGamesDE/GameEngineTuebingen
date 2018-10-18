#ifndef _MESH_H
#define _MESH_H

#include <memory>
using namespace std;

class Mesh
{
public:
	void Draw();
};
using Mesh_ptr = shared_ptr<Mesh>;

#else
class Mesh;
#endif