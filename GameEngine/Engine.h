#ifndef _ENGINE_H
#define _ENGINE_H

#include<memory>
#include <GL\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "Game.h"
using namespace std;

class Engine
{
	shared_ptr<Game> ManagedGame;
	SDL_Window* Window = nullptr;
	SDL_GLContext GLContext = nullptr;

	bool InitSDL();
	bool InitOpenGL();
	void Loop();
	void Render();

public:
	void Start(shared_ptr<Game> aGame);
};

#else
class Engine;
#endif