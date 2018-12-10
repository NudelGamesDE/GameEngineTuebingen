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

class SceneGraphNode {

public:
	SceneGraphNode(shared_ptr<Transform> aTransform, shared_ptr<Mesh> aMesh, shared_ptr<Material> aMaterial);
	shared_ptr<Transform> worldTransform;
	shared_ptr<Transform> localTransform;
	shared_ptr<Mesh> mesh;
	shared_ptr<Material> material;
	shared_ptr<SceneGraphNode> parent;
	shared_ptr<SceneGraphNode> self;
	vector<shared_ptr<SceneGraphNode>> children;

	void addChild(shared_ptr<SceneGraphNode> aNode);
	virtual void update(float aTimer);
	void addRenderers(shared_ptr<Scene> aScene);
};

#else
class SceneGraphNode;
#endif