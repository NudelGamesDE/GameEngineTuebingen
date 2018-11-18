#ifndef _RENDERER_H
#define _RENDERER_H

#include <memory>
#include <glm/matrix.hpp>
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "RayHit.h"
#include "Ray.h"
using namespace std;
using namespace glm;

class Renderer
{
public:
	Renderer();
	Renderer(shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial, Transform aTransform);
	Transform transform;
	shared_ptr<Material> material;
	shared_ptr<Mesh> mesh;
	void Draw(mat4* aView, mat4* aInverseView, mat4* aProjection);
	shared_ptr<RayHit> Intersect(Ray& aRay);
};

#else
class Renderer;
#endif