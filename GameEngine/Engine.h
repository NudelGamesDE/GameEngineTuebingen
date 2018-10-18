#ifndef _ENGINE_H
#define _ENGINE_H

#include <GL\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "Game.h"

class Engine
{
	Game_ptr ManagedGame;
	SDL_Window* Window = nullptr;
	SDL_GLContext GLContext = nullptr;

	bool InitSDL();
	bool InitOpenGL();
	void Loop();
	void Render();

public:
	void Start(Game_ptr aGame);
};

#else
class Engine;
#endif