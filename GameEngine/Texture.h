#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL_opengl.h>

class Texture
{
	GLuint CurrentGLID;
public:
	Texture(const char* aPath);
	void Use();
	~Texture();
};

#else
class Texture;
#endif