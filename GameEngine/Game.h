#ifndef _GAME_H
#define _GAME_H

#include <string>
#include <memory>
#include "Scene.h"
using namespace std;

class Game
{
	Scene_ptr CurrentScene = Scene_ptr(new Scene());
	bool stoped = false;
protected:
	void Stop();
	void SetScene(Scene_ptr aScene);
public:
	virtual string GetWindowName() = 0;
	virtual void Update() = 0;
	bool isStoped();
	Scene_ptr GetScene();
};
using Game_ptr = shared_ptr<Game>;

#else
class Game;
#endif