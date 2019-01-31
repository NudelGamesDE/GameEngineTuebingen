#ifndef _SHADOWMAP_H
#define _SHADOWMAP_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include "Light.h"
#include "Shader.h"
#include <memory>
using namespace glm;
using namespace std;

class ShadowMap
{
	GLuint bufferID;
	GLuint textureID;
	vec3 lightInvDir;
	shared_ptr<Shader> shader;
public:
	ShadowMap(shared_ptr<Light> light);
	~ShadowMap();
	void initBuffer();
	void initTexture();
	void draw();
};
#else
class ShadowMap;
#endif
