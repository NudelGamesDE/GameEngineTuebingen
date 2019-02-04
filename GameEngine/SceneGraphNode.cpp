#include "SceneGraphNode.h"
#include <iostream>

/** \brief Constructor for a SceneGraphNode instance

The constructor is similar to a renderers constructor, which is logical since the node contains an own renderer.
\param aMesh a Mesh
\param aMatrerial a Material
\param aTransform a Transform
*/
SceneGraphNode::SceneGraphNode(shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial, Transform aTransform) 
{
	localTransform = aTransform;
	mesh = aMesh;
	material = aMaterial;
	parent = nullptr;
	renderer = make_shared<Renderer>(mesh, material, localTransform);
}

/** \brief Add child node

This function adds a child to this node by making this the child nodes parent and adding the child node to this node's children vector.
\param aNode a shared pointer to the node to add as a child
*/
void SceneGraphNode::addChild(shared_ptr<SceneGraphNode> aNode) 
{
	aNode->parent = this;
	children.push_back(aNode);
}

/** \brief Update node's transforms

This function updates its own transform matrices according to the parent's transforms and afterwards calls its childrens' update functions.
\param aTimer a timer that can be used when inheriting the function
*/
void SceneGraphNode::update(float aTimer) 
{
	
	if (parent == nullptr) {
		worldTransform = localTransform.GetMatrix();
		renderer->transform = localTransform;
	}
	else {
		worldTransform = parent->worldTransform * localTransform.GetMatrix();
		renderer->transform = localTransform;
		renderer->secondTransform = parent->worldTransform;
	}

	for (int i = 0; i < children.size(); i++) {
		children[i]->update(aTimer);
	}
}

/** \brief Add renderers to a scene

This function allows the node to push its own and its childrens' renderers into the scene's renderer vector.
\param aScene a scene whose renderer vector will be filled with the scene graph's renderers. 
*/
void SceneGraphNode::getRenderers(shared_ptr<Scene> aScene) 
{
	aScene->Renderers.push_back(renderer);

	for (int i = 0; i < children.size(); i++) {
		children[i]->getRenderers(aScene);
	}
}