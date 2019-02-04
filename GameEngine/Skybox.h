#ifndef _SKYBOX
#define _SKYBOX

#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "Camera.h"
#include "objLoader.h"

/** \brief A sky box class

This class represents a sky box. The sky box is a cube with textured inner sides located around the camera. This was done using a cubemap.
Since we have a textured cube, we need a mesh, a material and therefore a renderer. To keep the box locked around the camera the cube also needs a transform.
*/
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