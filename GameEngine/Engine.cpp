#include "Engine.h"



bool Engine::InitSDL()
{
	return true;
}

bool Engine::InitOpenGL()
{
	return true;
}

void Engine::Loop()
{
	while (true)
	{
		if (ManagedGame->isStoped())return;
		ManagedGame->Update();
		if (ManagedGame->isStoped())return;
		Render();
	}
}

void Engine::Render()
{

}


void Engine::Start(Game_ptr aGame)
{
	if (!aGame)return;
	ManagedGame = aGame;
	if (!InitSDL())return;
	if (!InitOpenGL())return;
	Loop();
}