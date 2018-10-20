#include "Game.h"

void Game::Stop()
{
	stoped = true;
}

void Game::SetScene(shared_ptr<Scene> aScene)
{
	CurrentScene = aScene;
}

bool Game::isStoped()
{
	return stoped;
}

shared_ptr<Scene> Game::GetScene()
{
	return CurrentScene;
}
