#include "Renderer.h"

/** \brief Constructor for a Renderer instance
*/
Renderer::Renderer() {}

/** \brief overloaded constructor for a Renderer instance

This constructor already sets the mesh, materíal and transform. Those are the basic things you ned to draw an object.
\param aMesh a Mesh
\param aMaterial a Material
\param aTransform a Transform
*/
Renderer::Renderer(shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial, Transform aTransform) :Renderer()
{
	mesh = aMesh;
	material = aMaterial;
	transform = aTransform;
	secondTransform = mat4(1.0f);
}

/** \brief overloaded constructor for a Renderer instance

This constructor additionally sets a second transform.
\param aMesh a Mesh
\param aMaterial a Material
\param aTransform a Transform
\param aWorldTransform a mat4 representing a second transform
*/
Renderer::Renderer(shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial, Transform aLocalTransform, mat4 aWorldTransform) :Renderer()
{
	mesh = aMesh;
	material = aMaterial;
	transform = aLocalTransform;
	secondTransform = aWorldTransform;
}

/** \brief overloaded Constructor for a Renderer instance

This constructor additionally sets a rigid body.
\param aMesh a Mesh
\param aMaterial a Material
\param aTransform a Transform
\param aRigidBody a RigidBody
*/
Renderer::Renderer(shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial, Transform aTransform, shared_ptr<RigidBody> aRigidBody) :Renderer()
{
	mesh = aMesh;
	material = aMaterial;
	transform = aTransform;
	secondTransform = mat4(1.0f);
	rigidBody = aRigidBody;
}

/** \brief overloaded Constructor for a Renderer instance

This constructor additionally sets a second transform  and a rigid body.
\param aMesh a Mesh
\param aMaterial a Material
\param aTransform a Transform
\param aWorldTransform a mat4 representing a second transform
\param aRigidBody a RigidBody
*/
Renderer::Renderer(shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial, Transform aLocalTransform, mat4 aWorldTransform, shared_ptr<RigidBody> aRigidBody) :Renderer()
{
	mesh = aMesh;
	material = aMaterial;
	transform = aLocalTransform;
	secondTransform = aWorldTransform;
	rigidBody = aRigidBody;
}

/** \brief Draw renderer

This function draws the Mesh with the corresponding Material. It calls Material's Use function to set up the shader correctly and then Mesh's draw function to draw the vertices.
If a RigidBody exists, its traits are applied to the transform.
\param aView a view matrix
\param aInverseView an inverse view matrix
\param aProjection a projection matrix
\param a´Lights a vector containing all lights to be considered by the shader
*/
void Renderer::Draw(mat4* aView, mat4* aInverseView, mat4* aProjection, vector<shared_ptr<Light>> aLights)
{

	if (material && mesh)
	{
		if (rigidBody)
		{
			transform.Position += rigidBody->Velocity;
		}

		auto model = secondTransform * transform.GetMatrix();

		material->Use(&model, aView, aInverseView, aProjection, aLights);
		mesh->Draw();
	}
}
	
/** \brief Checks for intersection

This function transforms an incoming ray and calls Mesh's Intersect function.
\param aRay an incoming ray
\return a shared pointer to a RayHit
*/
shared_ptr<RayHit> Renderer::Intersect(Ray& aRay)
{
	if (!mesh)return nullptr;

	auto transformationMatrix = secondTransform * transform.GetMatrix();
	auto inverseTransformationMatrix = inverse(transformationMatrix);

	auto transformedRay = aRay;

	transformedRay.Origin = inverseTransformationMatrix * vec4(transformedRay.Origin, 1);
	transformedRay.Direction = inverseTransformationMatrix * vec4(transformedRay.Direction, 0);

	return mesh->Intersect(transformedRay);
}