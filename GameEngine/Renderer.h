#ifndef _RENDERER_H
#define _RENDERER_H

#include <memory>
#include <glm/matrix.hpp>
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "RayHit.h"
#include "Ray.h"
#include "Light.h"
#include "RigidBody.h"
using namespace std;
using namespace glm;

class Renderer
{
public:
	Renderer();
	Renderer(shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial, Transform aTransform);
	Renderer(shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial, Transform aLocalTransform, mat4 aWorldTransform);
	Renderer(shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial, Transform aTransform, shared_ptr<RigidBody> aRigidBody);
	Renderer(shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial, Transform aLocalTransform, mat4 aWorldTransform, shared_ptr<RigidBody> aRigidBody);
	Transform transform;
	mat4 secondTransform;
	shared_ptr<Material> material;
	shared_ptr<Mesh> mesh;
	shared_ptr<RigidBody> rigidBody;
	void Draw(mat4* aView, mat4* aInverseView, mat4* aProjection, vector<shared_ptr<Light>> aLights);
	shared_ptr<RayHit> Intersect(Ray& aRay);
};

#else
class Renderer;
#endif