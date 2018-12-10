#include "SceneGraphNode.h"

SceneGraphNode::SceneGraphNode(shared_ptr<Transform> aTransform, shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial) {
	localTransform = aTransform;
	mesh = aMesh;
	material = aMaterial;
	self = make_shared<SceneGraphNode>(localTransform, mesh, material);
}

void SceneGraphNode::addChild(shared_ptr<SceneGraphNode> aNode) {
	aNode->parent = self;
	children.push_back(aNode);
}

void SceneGraphNode::update(float aTimer) {
	if (parent) {
		worldTransform = parent->worldTransform * localTransform; //hier ist das Problem!
	}
	else {
		worldTransform = localTransform;
	}

	for (int i = 0; i < children.size(); i++) {
		children[i]->update(aTimer);
	}
}

void SceneGraphNode::addRenderers(shared_ptr<Scene> aScene) {
	auto renderer = make_shared<Renderer>(mesh, material, worldTransform);
	aScene->Renderers.push_back(renderer);

	for (int i = 0; i < children.size(); i++) {
		children[i]->draw(aScene);
	}
}