#ifndef _RENDERER_H
#define _RENDERER_H

#include <memory>
#include "Mesh.h"
using namespace std;

class Renderer
{
public:
	Mesh_ptr Mesh;
	void Draw();
};
using Renderer_ptr = shared_ptr<Renderer>;

#else
class Renderer;
#endif