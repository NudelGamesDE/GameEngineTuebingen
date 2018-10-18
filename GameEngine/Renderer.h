#ifndef _RENDERER_H
#define _RENDERER_H

#include <memory>
#include <glm/matrix.hpp>
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
using namespace std;
using namespace glm;

class Renderer
{
public:
	Transform transform;
	Material_ptr material;
	Mesh_ptr mesh;
	void Draw(mat4 aViewMatrix);
};
using Renderer_ptr = shared_ptr<Renderer>;

#else
class Renderer;
#endif