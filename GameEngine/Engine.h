#ifndef _ENGINE_H
#define _ENGINE_H

#include<memory>
#include<ctime>
#include <GL\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "Game.h"
#include "FrameData.h"
using namespace std;

class Engine
{
	shared_ptr<Game> ManagedGame;
	SDL_Window* Window = nullptr;
	SDL_GLContext GLContext = nullptr;
	clock_t timer = clock();

	bool InitSDL();
	bool InitOpenGL();
	void Loop();
	void Render();
	shared_ptr<FrameData> GenerateFrameData();

public:
	void Start(shared_ptr<Game> aGame);
};

#else
class Engine;
#endif