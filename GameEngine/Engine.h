#ifndef _ENGINE_H
#define _ENGINE_H

#include <memory>
#include <ctime>
#include <unordered_set>
#include <GL\glew.h>
#include <SDL.h>
#include <SDL_keycode.h>
#include <SDL_opengl.h>
#include <glm\vec2.hpp>
#include "Game.h"
#include "FrameData.h"
using namespace std;
using namespace glm;

class Engine
{
	shared_ptr<Game> ManagedGame;
	SDL_Window* Window = nullptr;
	SDL_GLContext GLContext = nullptr;
	clock_t timer = clock();
	shared_ptr<unordered_set<SDL_Keycode>> KeysPressed = make_shared<unordered_set<SDL_Keycode>>();
	shared_ptr<vec2> MousePosition;

	bool InitSDL();
	bool InitOpenGL();
	void Loop();
	void Render();
	void HandleEvents(shared_ptr<FrameData> aFrameData);
	shared_ptr<FrameData> GenerateFrameData();

public:
	void Start(shared_ptr<Game> aGame);
};

#else
class Engine;
#endif