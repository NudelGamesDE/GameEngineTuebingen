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

/** \brief A renderer class

The renderer class is a container class containing a mesh, a material, a transform and eventually a second transform aalong with a rigid body. By calling the draw function of a renderer
the material used takes care of most shader operations while the mesh actually draws the vertices. A second transform mostly only is applied when the renderer is part of a scenegraph.
The rigid body only needs to be implemented in case the drawn object should be influencable by forces and velocity.
*/
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