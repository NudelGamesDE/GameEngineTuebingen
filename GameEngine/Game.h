#ifndef _GAME_H
#define _GAME_H

#include <string>
#include <memory>
using namespace std;

class Game
{
	bool stoped = false;
protected:
	void Stop();
public:
	virtual string GetWindowName() = 0;
	virtual void Update() = 0;
	bool isStoped();
};
using Game_ptr = shared_ptr<Game>;

#else
class Game;
#endif