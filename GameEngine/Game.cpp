#include "Game.h"

void Game::Stop()
{
	stoped = true;
}

void Game::SetScene(Scene_ptr aScene)
{
	CurrentScene = aScene;
}

bool Game::isStoped()
{
	return stoped;
}

Scene_ptr Game::GetScene()
{
	return CurrentScene;
}
