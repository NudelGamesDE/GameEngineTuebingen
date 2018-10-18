#ifndef _ENGINE_H
#define _ENGINE_H

#include "Game.h"

class Engine
{
	bool InitSDL();
	bool InitOpenGL();
	void Loop();
	void Render();
	Game_ptr ManagedGame;

public:
	void Start(Game_ptr aGame);
};

#else
class Engine;
#endif