#include "SceneGraphNode.h"
#include <iostream>

SceneGraphNode::SceneGraphNode(shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial, Transform aTransform) 
{
	localTransform = aTransform;
	mesh = aMesh;
	material = aMaterial;
	parent = nullptr;
	renderer = make_shared<Renderer>(mesh, material, localTransform);
}

void SceneGraphNode::addChild(shared_ptr<SceneGraphNode> aNode) 
{
	aNode->parent = this;
	children.push_back(aNode);
}

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
	
	/*
	if (parent == nullptr) {
		renderer->transform = localTransform;
	}
	else {
		renderer->transform = localTransform;
		renderer->secondTransform = parent->worldTransform;
	}
	*/

	for (int i = 0; i < children.size(); i++) {
		children[i]->update(aTimer);
	}
}

void SceneGraphNode::getRenderers(shared_ptr<Scene> aScene) 
{
	aScene->Renderers.push_back(renderer);

	for (int i = 0; i < children.size(); i++) {
		children[i]->getRenderers(aScene);
	}
}