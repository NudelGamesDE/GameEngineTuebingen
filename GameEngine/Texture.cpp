#include "Texture.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

/** \brief Constructor for a Texture instance

Basically this constructor generates and then binds the texture.
*/
Texture::Texture()
{
	glGenTextures(1, &CurrentGLID);
	glBindTexture(GL_TEXTURE_2D, CurrentGLID);
}

/** \brief Changes the texture format

This function binds the texture and allows to dynamically set texture parameters.
\param aBytes bytes
\param aWidth a width
\param aHeight a height
\param aBytesPerPixel bytes per pixel
*/
void Texture::Change2D(void* aBytes, int aWidth, int aHeight, int aBytesPerPixel)
{
	int mode;
	switch (aBytesPerPixel)
	{
	case 1: mode = GL_RED; break;
	case 2: mode = GL_RG; break;
	case 3: mode = GL_RGB; break;
	case 4: mode = GL_RGBA; break;
	default: return;
	}

	glBindTexture(GL_TEXTURE_2D, CurrentGLID);
	glTexImage2D(GL_TEXTURE_2D, 0, mode, aWidth, aHeight, 0, mode, GL_UNSIGNED_BYTE, aBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

/** \brief Overloaded constructor for a Texture instance

This constructor loads an image from a path and then calls Change2D with the desired parameters.
\param path a path to the image to be loaded
*/
Texture::Texture(const char* aPath) :Texture()
{
	auto _toUpload = shared_ptr<SDL_Surface>(IMG_Load(aPath), [](SDL_Surface* aSurface) {SDL_FreeSurface(aSurface); });
	Change2D(_toUpload->pixels, _toUpload->w, _toUpload->h, _toUpload->format->BytesPerPixel);
}

/** \brief Overloaded constructor for a Texture instance

This constructor generates a cubemap texture from six different textures.
\param filenames vector of paths to the different textures
*/
Texture::Texture(vector<const char*> filenames)
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

/** \brief Binds texture
*/
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

/** \brief Destroys texture
*/
Texture::~Texture()
{
	glDeleteTextures(1, &CurrentGLID);
}