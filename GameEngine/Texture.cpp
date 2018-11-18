#include "Texture.h"

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
using namespace std;

Texture::Texture(const char* aPath)
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

void Texture::Use()
{
	glBindTexture(GL_TEXTURE_2D, CurrentGLID);
}

Texture::~Texture()
{
	glDeleteTextures(1, &CurrentGLID);
}