#include "Game.h"

/** \brief Stop game

Stops the game by setting stoped to true.
*/
void Game::Stop()
{
	stoped = true;
}

/** \brief Setter for scene

This functions sets the scene for a game.
\param aScene a shared pointer to a scene
*/
void Game::SetScene(shared_ptr<Scene> aScene)
{
	CurrentScene = aScene;
}

/** \brief Game stopped?

Checks if game is stoped.
\return stoped an indicator if game is stoped
*/
bool Game::isStoped()
{
	return stoped;
}

/** \brief Getter for current scene

This function returns the current scene.
\return CurrentScene the current scene
*/
shared_ptr<Scene> Game::GetScene()
{
	return CurrentScene;
}
