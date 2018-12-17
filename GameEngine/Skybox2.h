#ifndef _SKYBOX2
#define _SKYBOX2

#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "Camera.h"
#include "objLoader.h"

class Skybox2 {
public:
	Skybox2(
		const char* posXFilename,
		const char* negXFilename,
		const char* posYFilename,
		const char* negYFilename,
		const char* posZFilename,
		const char* negZFilename);
	shared_ptr<Mesh> mesh;
	shared_ptr<Material> material;
	Transform transform;
	shared_ptr<Renderer> getRenderer();
	vector<const char*> filenames;
};

#else
class Skybox2;
#endif