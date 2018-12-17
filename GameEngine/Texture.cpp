#include "Texture.h"

#include <SDL.h>
#include <SDL_image.h>
using namespace std;

Texture::Texture() {}

Texture::Texture(const char* aPath) :Texture()
{
	auto _toUpload = shared_ptr<SDL_Surface>(IMG_Load(aPath), [](SDL_Surface* aSurface) {SDL_FreeSurface(aSurface); });

	glGenTextures(1, &CurrentGLID);
	glBindTexture(GL_TEXTURE_2D, CurrentGLID);

	int Mode = GL_RGB;

	if (_toUpload->format->BytesPerPixel == 4) {
		Mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, Mode, _toUpload->w, _toUpload->h, 0, Mode, GL_UNSIGNED_BYTE, _toUpload->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(vector<const char*> filenames) :Texture()
{
	
	GLenum types[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
						GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
						GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

	cubemap = true;

	glGenTextures(1, &CurrentGLID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, CurrentGLID);

	for (unsigned int i = 0; i < filenames.size(); i++) 
	{
		auto _toUpload = shared_ptr<SDL_Surface>(IMG_Load(filenames[i]), [](SDL_Surface* aSurface) {SDL_FreeSurface(aSurface); });

		if (_toUpload == NULL) 
		{
			printf("Unable to load %s\n", filenames[i]);
			fflush(stdout);
		}

		int Mode = GL_RGB;

		if (_toUpload->format->BytesPerPixel == 4) 
		{
			Mode = GL_RGBA;
		}

		glTexImage2D(types[i], 0, Mode, _toUpload->w, _toUpload->h, 0, Mode, GL_UNSIGNED_BYTE, _toUpload->pixels);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Texture::Use()
{
	if (cubemap) 
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, CurrentGLID);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, CurrentGLID);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &CurrentGLID);
}