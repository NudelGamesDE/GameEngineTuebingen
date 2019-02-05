#include <iostream>
#include "Engine.h"
#include "TechDemo.h"
#include "FinalDemo.h"
using namespace std;

/**
This is the starting point of the whole program. Start the engine with a Game instance you made.
*/
int main(int argc, char** argv)
{
	//Engine().Start(make_shared<TechDemo>());
	Engine().Start(make_shared<FinalDemo>());
	return 1;
}