#include <iostream>
#include "Engine.h"
#include "TechDemo.h"
#include "FinalDemo.h"
using namespace std;

/**
\mainpage Game Engine Architecture WS 2018/19

\authors Yannick Hempe, Paul Hoppe, Timo Mohrlock, Matthew Wesoloski
*/

/**
This is the starting point of the whole program. Start the engine with a Game instance you made.
*/
int main(int argc, char** argv)
{
	//Engine().Start(make_shared<TechDemo>());
	Engine().Start(make_shared<FinalDemo>());
	return 1;
}