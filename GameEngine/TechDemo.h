#ifndef _TECHDEMO_H
#define _TECHDEMO_H

#include <string>
#include "Game.h"
using namespace std;

class TechDemo :public Game
{
	int frames = 1000;
public:
	TechDemo();
	string GetWindowName();
	virtual void Update();
};

#else
class TechDemo;
#endif