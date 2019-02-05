#ifndef _SCENE_GRAPH_NODE_H
#define _SCENE_GRAPH_NODE_H

#include <vector>
#include <glm/matrix.hpp>
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Scene.h"
#include "Renderer.h"
using namespace std;
using namespace glm;

/** \brief A scene graph node class

This class implements a scene graph node. By multiplying a parent's transformation matrix to a node's own, the node is affected by the parent.
Every node has its own renderer which can later be passed to the scene.
*/
class SceneGraphNode {
public:
	SceneGraphNode(shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial, Transform aTransform);
	mat4 worldTransform;
	Transform localTransform;
	shared_ptr<Mesh> mesh;
	shared_ptr<Material> material;
	SceneGraphNode* parent;
	vector<shared_ptr<SceneGraphNode>> children;
	shared_ptr<Renderer> renderer;

	void addChild(shared_ptr<SceneGraphNode> aNode);
	virtual void update(float aTimer);
	void getRenderers(shared_ptr<Scene> aScene);
};

#else
class SceneGraphNode;
#endif