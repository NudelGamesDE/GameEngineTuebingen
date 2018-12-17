#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL_opengl.h>
#include <memory>
#include <vector>
using namespace std;

class Texture
{
	GLuint CurrentGLID;
public:
	Texture();
	Texture(const char* aPath);
	Texture(vector<const char*> filenames);
	bool cubemap =  false;
	void Use();
	~Texture();
};

#else
class Texture;
#endif