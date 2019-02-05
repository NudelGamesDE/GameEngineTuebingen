#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL_opengl.h>
#include <memory>
#include <vector>
using namespace std;

/** \brief A texture class

This class represents a texture. This includes regular textures as well as cubemaps.
*/
class Texture
{
	GLuint CurrentGLID;
public:
	Texture();
	Texture(const char* aPath);
	Texture(vector<const char*> filenames);
	void Change2D(void* aBytes, int aWidth, int aHeight, int aBytesPerPixel = 4);
	bool cubemap =  false;
	void Use();
	~Texture();
};

#else
class Texture;
#endif