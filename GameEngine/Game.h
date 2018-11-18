#ifndef _GAME_H
#define _GAME_H

#include <string>
#include <memory>
#include "Scene.h"
#include "FrameData.h"
using namespace std;

class Game
{
	shared_ptr<Scene> CurrentScene = make_shared<Scene>();
	bool stoped = false;
protected:
	void Stop();
	void SetScene(shared_ptr<Scene> aScene);
public:
	virtual void Start() = 0;
	virtual string GetWindowName() = 0;
	virtual void Update() = 0;
	bool isStoped();
	shared_ptr<Scene> GetScene();
	shared_ptr<FrameData> frameData = make_shared<FrameData>();
};

#else
class Game;
#endif