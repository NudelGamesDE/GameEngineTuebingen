#ifndef _SKYBOX
#define _SKYBOX

#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "Camera.h"
#include "objLoader.h"

class Skybox {
public:
	Skybox(
		const char* posXFilename,
		const char* negXFilename,
		const char* posYFilename,
		const char* negYFilename,
		const char* posZFilename,
		const char* negZFilename);
	shared_ptr<Mesh> mesh;
	shared_ptr<Material> material;
	shared_ptr<Renderer> cachedRenderer;
	Transform transform;
	shared_ptr<Renderer> getRenderer();
	vector<const char*> filenames;
};

#else
class Skybox;
#endif