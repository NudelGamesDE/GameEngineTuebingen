#ifndef _TECHDEMO_H
#define _TECHDEMO_H

#include <string>
#include "Game.h"
using namespace std;

class TechDemo :public Game
{
public:
	string GetWindowName();
	virtual void Update();
};

#else
class TechDemo;
#endif